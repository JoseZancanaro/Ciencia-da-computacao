const mongoose = require("mongoose");

const TheaterComplex = new mongoose.Schema(
  {
    name: {
      type: String,
      required: true
    },
    contactPhone: {
      type: String,
      required: true
    },
    owner: {
      type: mongoose.Schema.Types.ObjectId,
      ref: "TheaterManager"
    },
    theaters: [
      {
        type: mongoose.Schema.Types.ObjectId,
        ref: "MovieTheater"
      }
    ]
  },
  {}
);

module.exports = mongoose.model("TheaterComplex", TheaterComplex);
