const RegularUser = require("../../model/User").RegularUser;
const User = require("../../model/User").User;
const Image = require("../../model/Image");

class RegularUserController {
  async signup(req, res) {
    const avatar = await Image.create({ path: req.file.key });

    const userInfo = await User.create({
      name: req.body.name,
      email: req.body.email,
      password: req.body.password,
      avatar,
      type: "regular"
    });

    const user = await RegularUser.create({ userInfo });

    return res.json(user);
  }
}

module.exports = new RegularUserController();
