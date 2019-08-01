const mongoose = require("mongoose");

const AvailabilityEntry = mongoose.Schema({
  dateTime = {
    type: mongoose.Schema.Types.Date, required: true
  },
  tickets = [
    { type: mongoose.Schema.Types.ObjectId, ref: "TicketType" }
  ]
});

module.exports = mongoose.model("AvailabilityEntry", AvailabilityEntry);
