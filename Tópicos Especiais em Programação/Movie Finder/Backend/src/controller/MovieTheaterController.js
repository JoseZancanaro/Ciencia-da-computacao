const MovieTheater = require("../model/MovieTheater");
const TheaterComplex = require("../model/TheaterComplex");

class MovieTheaterController {
  async store(req, res) {
    const complex = await TheaterComplex.findById(req.params.id);

    const theater = await MovieTheater.create(req.body);

    complex.theaters.push(theater);

    await complex.save();

    return res.json(theater);
  }
}

module.exports = new MovieTheaterController();
