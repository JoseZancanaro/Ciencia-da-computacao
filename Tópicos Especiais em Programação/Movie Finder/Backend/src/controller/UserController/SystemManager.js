const SystemManager = require("../../model/User").SystemManager;
const User = require("../../model/User").User;
const Image = require("../../model/Image");

class SystemManagerController {
  async signup(req, res) {
    const avatar = await Image.create({ path: req.file.key });

    const userInfo = await User.create({
      name: req.body.name,
      email: req.body.email,
      password: req.body.password,
      avatar,
      type: "system-manager"
    });

    const user = await SystemManager.create({ userInfo });

    return res.json(user);
  }
}

module.exports = new SystemManagerController();
