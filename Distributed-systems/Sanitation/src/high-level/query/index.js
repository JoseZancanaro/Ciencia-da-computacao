require('dotenv').config()

const cors = require('cors')
const express = require('express')
const mongoose = require('mongoose')
const Sensor = require('../models/mongoose/Sensor')(mongoose)
const Reading = require('../models/mongoose/Reading')(mongoose)

const app = express()
app.use(cors())

mongoose.connect(`mongodb+srv://ds-admin:${process.env.PW}@sanitation-ds.tvbje.mongodb.net/sanitation-ds?retryWrites=true&w=majority`, {
    useNewUrlParser: true,
    useUnifiedTopology: true
})

app.use(express.json())

app.get('/watch/sensor', async (req, res) => {
    try {
        const sensors = await Sensor.find().populate({
            path: 'readings',
            options: {
                sort: { createdAt: -1 },
                limit: 1
            }
        })

        return res.json(sensors)
    }
    catch (e) {
        console.log('E', e)
        console.log('GET on route=/watch/sensor failed.')

        return res.sendStatus(500)
    }
})

app.get('/watch/sensor/:id', async (req, res) => {
    try {
        const sensors = await Sensor.findById(req.params.id).populate({
            path: 'readings',
            options: { sort: { createdAt: -1 } }
        })

        return res.json(sensors)
    }
    catch (e) {
        console.log(`GET on id=${id} failed.`)

        return res.sendStatus(404)
    }
})

app.listen(3301)