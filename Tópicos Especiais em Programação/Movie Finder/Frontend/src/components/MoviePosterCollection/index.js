import React from 'react';
import PropTypes from 'prop-types';
import MoviePoster from '../MoviePoster';

const MoviePosterCollection = ({ movies }) => (
  <>
    {movies.map(movie => (
      <MoviePoster key={movie.id} posterUrl={movie.poster} posterTitle={movie.title} />
    ))}
  </>
);

MoviePosterCollection.propTypes = {
  movies: PropTypes.arrayOf(
    PropTypes.shape({
      id: PropTypes.number.isRequired,
      title: PropTypes.string.isRequired,
      poster: PropTypes.string.isRequired,
      status: PropTypes.string.isRequired,
    }),
  ).isRequired,
};

export default MoviePosterCollection;
