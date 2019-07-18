import React from 'react';
import PropTypes from 'prop-types';

import MoviePosterCollection from '../MoviePosterCollection';

const MoviePosterGrid = ({ movies }) => (
  <div className="uk-flex-center uk-child-width-1-5@s" uk-grid="">
    <MoviePosterCollection movies={movies} />
  </div>
);

MoviePosterGrid.propTypes = {
  movies: PropTypes.arrayOf(
    PropTypes.shape({
      id: PropTypes.number.isRequired,
      title: PropTypes.string.isRequired,
      poster: PropTypes.string.isRequired,
      status: PropTypes.string.isRequired,
    }),
  ).isRequired,
};

export default MoviePosterGrid;
