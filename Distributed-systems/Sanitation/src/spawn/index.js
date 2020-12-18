const axios = require('axios')
const { exec } = require('child_process')

const ENDPOINT = 'http://localhost:3301/watch/sensor'
const BIN = process.argv[2]

spawn()
async function spawn() {
    const sensors = await axios.get(ENDPOINT)

    for (const sensor of sensors.data) {
        const { _id } = sensor
        if (Math.random() < 0.05) {
            console.log(`SENSOR[${_id}] not spawned`)
        }
        else {
            console.log(`SENSOR[${_id}] spawned`)

            exec(`${BIN} ${_id}`)
        }
    }
}