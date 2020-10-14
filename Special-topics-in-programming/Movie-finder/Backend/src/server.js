const routes = require('./routes')
const express = require('express')
const mongoose = require('mongoose')

const app = express()

mongoose.connect('mongodb+srv://us-moviefinder:us-moviefinder@moviefinder-yigwc.mongodb.net/moviefinder?retryWrites=true&w=majority', {
  useNewUrlParser: true,
})

app.use(express.json())
app.use(express.urlencoded({ extended: true }))

app.use(routes)

app.listen(3333)