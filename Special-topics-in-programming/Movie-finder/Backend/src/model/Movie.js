const mongoose = require("mongoose");

const Movie = new mongoose.Schema(
  {
    title: {
      type: String,
      required: true
    },
    slug: {
      type: String,
      required: true
    },
    trailer: {
      type: String,
      required: true
    },
    duration: {
      type: Number,
      required: true
    },
    minimumAge: {
      type: Number,
      required: true
    },
    sinopse: {
      type: String,
      required: true
    },
    release: {
      type: Date,
      default: Date.now
    },
    actors: {
      type: String,
      default: ""
    },
    directors: {
      type: String,
      default: ""
    },
    poster: {
      type: mongoose.Schema.Types.ObjectId,
      ref: "Image"
    },
    gallery: [{ type: mongoose.Schema.Types.ObjectId, ref: "Image" }]
  },
  {
    toObject: { virtuals: true },
    toJSON: { virtuals: true }
  }
);

Movie.virtual("id").get(function() {
  return this._id;
});

Movie.virtual("status").get(function() {
  if (this.release <= Date.now()) {
    return "released";
  }
  return "comming-soon";
});

module.exports = mongoose.model("Movie", Movie);
