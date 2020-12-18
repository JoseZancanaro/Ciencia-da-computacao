require('dotenv').config()

const express = require('express')
const mongoose = require('mongoose')
const Sensor = require('../models/mongoose/Sensor')(mongoose)

const app = express()

mongoose.connect(`mongodb+srv://ds-admin:${process.env.PW}@sanitation-ds.tvbje.mongodb.net/sanitation-ds?retryWrites=true&w=majority`, {
    useNewUrlParser: true,
    useUnifiedTopology: true
})

app.use(express.json())

app.post('/directory/sensor', async (req, res) => {
    try {
        const sensor = await Sensor.create(req.body)

        return res.json(sensor)
    }
    catch (e) {
        console.log(`POST on body=${JSON.stringify(req.body)} failed.`)

        return res.sendStatus(400)
    }
})

app.get('/directory/sensor/:id', async (req, res) => {
    try {
        const sensor = await Sensor.findById(req.params.id)

        return res.json(sensor)
    }
    catch (e) {
        console.log(`GET on id=${id} failed.`)

        return res.sendStatus(400)
    }
})

app.delete('/directory/sensor/:id', async (req, res) => {
    const { id } = req.params

    try { 
        await Sensor.findByIdAndDelete(id)

        return res.sendStatus(200)
    }
    catch (e) {
        console.log(`DELETE on id=${id} failed.`)

        return res.sendStatus(404)
    }
})

app.listen(3300)