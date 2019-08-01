const mongoose = require("mongoose");

const MovieTheater = new mongoose.Schema(
  {
    cnpj: {
      type: String,
      required: true
    },
    location: {
      type: String,
      required: true
    },
    contactPhone: {
      type: String,
      required: true
    },
    email: {
      type: String,
      required: true
    },
    tickets: [{ type: mongoose.Schema.Types.ObjectId, ref: "TicketType" }]
  },
  {}
);

module.exports = mongoose.model("MovieTheater", MovieTheater);
