module.exports = (mongoose) => {
    const Sensor = new mongoose.Schema({
        zip: {
            type: mongoose.Schema.Types.String,
            required: true
        },
        order: {
            type: mongoose.Schema.Types.Number,
            required: true
        },
        lat: {
            type: mongoose.Schema.Types.Number,
            required: true
        },
        lng: {
            type: mongoose.Schema.Types.Number,
            required: true
        },
        readings: [
            {
              type: mongoose.Schema.Types.ObjectId, ref: "Reading"
            }
          ]
    }, {
        timestamps: true
    })

    return mongoose.model('Sensor', Sensor)
}