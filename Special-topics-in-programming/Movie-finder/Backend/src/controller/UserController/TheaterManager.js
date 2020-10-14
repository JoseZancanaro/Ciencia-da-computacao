const TheaterManager = require("../../model/User").TheaterManager;
const TheaterComplex = require("../../model/TheaterComplex");
const User = require("../../model/User").User;
const Image = require("../../model/Image");

class TheaterManagerController {
  async signup(req, res) {
    const avatar = await Image.create({ path: req.file.key });

    const userInfo = await User.create({
      name: req.body.name,
      email: req.body.email,
      password: req.body.password,
      avatar,
      type: "theater-manager"
    });

    const user = await TheaterManager.create({
      userInfo,
      theaterComplex: req.body.theaterComplex
    });

    const theaterComplex = await TheaterComplex.create({
      name: req.body.name,
      contactPhone: req.body.contactPhone,
      owner: user
    });

    return res.json(theaterComplex);
  }
}

module.exports = new TheaterManagerController();
