const mongoose = require("mongoose");

const Image = new mongoose.Schema(
  {
    path: {
      type: String,
      required: true
    }
  },
  {
    toObject: { virtuals: true },
    toJSON: { virtuals: true }
  }
);

Image.virtual("url").get(function() {
  const path = process.env.PORT || "http://localhost/3333";
  return `${path}/images/${encodeURIComponent(this.path)}`;
});

module.exports = mongoose.model("Image", Image);
