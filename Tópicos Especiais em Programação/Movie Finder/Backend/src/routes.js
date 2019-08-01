const path = require("path");
const express = require("express");
const multer = require("multer");
const multerConfig = require("./config/multer");

const routes = express.Router();

const MovieController = require("./controller/MovieController");
const UserController = require("./controller/UserController");
const MovieTheaterController = require("./controller/MovieTheaterController");
const TicketTypeController = require("./controller/TicketTypeController");

/* IMAGE RESOURCE ROUTE */
routes.use("/images", express.static(path.resolve(__dirname, "..", "storage")));

/* MOVIE ROUTES */

routes.post(
  "/movies",
  multer(multerConfig).fields([
    { name: "poster", maxCount: 1 },
    { name: "gallery" }
  ]),
  MovieController.store
);

routes.get("/movies", MovieController.show);

routes.get("/movies/:slug", MovieController.single);

/* USER ROUTES */

routes.post(
  "/users/regular/signup",
  multer(multerConfig).single("avatar"),
  UserController.RegularUser.signup
);

routes.post(
  "/users/theater/signup",
  multer(multerConfig).single("avatar"),
  UserController.TheaterManager.signup
);

/* THEATER COMPLEX ROUTES */

routes.post("/theater-complexes/:id/theaters", MovieTheaterController.store);

routes.post(
  "/theater-complexes/:id/theaters/:theaterid/ticket",
  TicketTypeController.store
);

module.exports = routes;
