const Movie = require("../model/Movie");
const Image = require("../model/Image");

const slugify = require("slugify");

class MovieController {
  async store(req, res) {
    const content = req.body;
    content.slug = slugify(req.body.title, {
      replacement: "-",
      remove: /[^a-zA-Z0-9\s]/g,
      lower: true
    }).toString();

    content.poster = await Image.create({
      path: req.files.poster[0].key
    });
    content.gallery = await Image.create(
      req.files.gallery.map(picture => ({ path: picture.key }))
    );

    const movie = await Movie.create(content);

    return res.json(movie);
  }

  async show(req, res) {
    const movies = await Movie.find({})
      .populate({ path: "poster" })
      .select("id title slug poster status")
      .exec();
    return res.json(movies);
  }

  async single(req, res) {
    const movie = await Movie.findOne({ slug: req.params.slug })
      .populate([{ path: "poster" }, { path: "gallery" }])
      .exec();

    return res.json(movie);
  }
}

module.exports = new MovieController();
