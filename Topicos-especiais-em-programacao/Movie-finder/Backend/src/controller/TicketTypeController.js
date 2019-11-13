const TicketType = require("../model/TicketType");
const MovieTheater = require("../model/MovieTheater");

class TicketTypeController {
  async store(req, res) {
    const theater = await MovieTheater.findById(req.params.theaterid);

    const ticket = await TicketType.create(req.body);

    theater.tickets.push(theater);

    await theater.save();

    return res.json(ticket);
  }
}

module.exports = new TicketTypeController();
