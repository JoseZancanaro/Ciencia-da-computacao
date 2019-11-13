const mongoose = require("mongoose");

const TicketType = mongoose.Schema(
  {
    value: {
      type: Number,
      required: true
    },
    audio: {
      type: String,
      required: true
    },
    description: {
      type: String,
      default: ""
    }
  },
  {}
);

module.exports = mongoose.model("TicketType", TicketType);
