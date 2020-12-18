require('dotenv').config()

const zmq = require('zeromq')
const mongoose = require('mongoose')
const Sensor = require('../../models/mongoose/Sensor')(mongoose)
const Reading = require('../../models/mongoose/Reading')(mongoose)

mongoose.connect(`mongodb+srv://ds-admin:${process.env.PW}@sanitation-ds.tvbje.mongodb.net/sanitation-ds?retryWrites=true&w=majority`, {
    useNewUrlParser: true,
    useUnifiedTopology: true
})

const chunkSize = 10
const pool = []

const collect = new zmq.Subscriber()
collect.subscribe('')
collect.connect('tcp://localhost:5560')

const dispatch = new zmq.Push()

setupDispatch()
receive()
const id = setInterval(multiplex, 20000)

async function receive() {
    console.log('Receiving')

    for await (const msg of collect) {
        pool.push({ ...JSON.parse(msg.toString()), timestamp: Date.now() })
    }
}

async function setupDispatch() {
    await dispatch.bind('tcp://*:7000')
    console.log('Ready to dispatch jobs')
}

async function multiplex() {
    console.log('Multiplexing')

    sensors = await Sensor.find()

    const jobs = createJobs(sensors)

    pool.length = 0

    for (const job of jobs) {
        await dispatch.send(job)
    }
}

function createJobs(sensors) {
    const cache = {}

    for (const sensor of sensors) {
        const { id, zip } = sensor

        if (zip in cache) {
            cache[zip] = [ ...cache[zip], id ]
        }
        else {
            cache[zip] = [ id ]
        }
    }

    const chunks = createChunks(Object.values(cache), chunkSize)
    const messages = sortBy(pool, 'timestamp')

    const jobs = chunks.map(chunk => {
        return JSON.stringify(chunk.map(id => {
            const idx = messages.findIndex((msg) => msg.id === id)

            if (idx >= 0) {
                return { ...messages[idx], missing: false }
            }
            else {
                return { id, healthy: 0, flow: 0, height: 0, pressure: 0, missing: true }
            }
        }))
    })

    return jobs
}

function createChunks(buffer, size) {
    let elements = buffer.flat()
    let chunkCount = Math.ceil(elements.length / size)

    return [...Array(chunkCount).keys()].map(() => {
        const chunk = elements.slice(0, size)
        elements = elements.slice(size)

        return chunk
    })
}

function sortBy(queue, property) {
    return [...queue].sort((a, b) => a[property] - b[property])
}