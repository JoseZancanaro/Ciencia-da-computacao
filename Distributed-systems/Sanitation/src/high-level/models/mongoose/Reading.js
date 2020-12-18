module.exports = (mongoose) => {
    const Reading = new mongoose.Schema({
        missing: {
            type: mongoose.Schema.Types.Boolean,
            required: true
        },
        healthy: {
            type: mongoose.Schema.Types.Boolean,
            required: true
        },
        bad_section: {
            type: mongoose.Schema.Types.Boolean,
            required: true
        },
        source_of_failure: {
            type: mongoose.Schema.Types.String,
            default: ''
        },
        flow: {
            type: mongoose.Schema.Types.Number,
            required: true
        },
        height: {
            type: mongoose.Schema.Types.Number,
            required: true
        },
        pressure: {
            type: mongoose.Schema.Types.Number,
            required: true
        },
        warning: {
            type: mongoose.Schema.Types.String,
            default: ''
        },
    }, {
        timestamps: true
    })

    return mongoose.model('Reading', Reading)
}