require('dotenv').config()

const zmq = require('zeromq')
const mongoose = require('mongoose')
const Sensor = require('../../models/mongoose/Sensor')(mongoose)
const Reading = require('../../models/mongoose/Reading')(mongoose)

mongoose.connect(`mongodb+srv://ds-admin:${process.env.PW}@sanitation-ds.tvbje.mongodb.net/sanitation-ds?retryWrites=true&w=majority`, {
    useNewUrlParser: true,
    useUnifiedTopology: true
})

const worker = new zmq.Pull()

setupWorker()

async function setupWorker() {
    await worker.connect('tcp://localhost:7000')

    console.log('Connected')

    for await (const msg of worker) {
        makeAnalysis(JSON.parse(msg.toString()))
    }
}

async function makeAnalysis(chunk) {
    for (const reading of chunk) {
        try {
            const sensor = await Sensor.findById(reading.id)

            const analysis = await Reading.create(label(reading))

            sensor.readings.push(analysis)
            await sensor.save()
        }
        catch (ignore) {}
    }
}

const FAILURES = 
    ['No data received', 'No flow in section', 'Unhealthy sensor', 'Pressure too damn high', 'Data is inconsistent']

const [NO_DATA, NO_FLOW, SENSOR_FAILURE, HIGH_PRESSURE, INCONSISTENT_READING] = FAILURES

function label(reading) {
    if (reading.missing) {
        return {
            ...reading,
            bad_section: true,
            source_of_failure: NO_DATA
        }
    }
    else {
        if (Math.random() < 0.05) {
            return {
                ...reading,
                bad_section: true,
                source_of_failure: FAILURES[Math.floor(Math.random() * (FAILURES.length - 1 + 1) + 1)]
            }
        }
        else {
            return {
                ...reading,
                bad_section: false
            }
        }
    }
}