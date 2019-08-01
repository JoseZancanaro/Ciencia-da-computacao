const mongoose = require("mongoose");

const TheaterManager = new mongoose.Schema(
  {
    userInfo: {
      type: mongoose.Schema.Types.ObjectId,
      ref: "User"
    },
    theaterComplex: {
      type: String,
      required: true
    }
  },
  {
    timestamps: true
  }
);

module.exports = mongoose.model("TheaterManager", TheaterManager);
