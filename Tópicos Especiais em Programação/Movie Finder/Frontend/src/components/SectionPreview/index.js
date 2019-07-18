import React from 'react';
import { Link } from 'react-router-dom';
import PropTypes from 'prop-types';

import { SectionPreviewContainer } from './styles';

import MoviePosterGrid from '../MoviePosterGrid';

const SectionPreview = ({ title, url, movies }) => (
  <SectionPreviewContainer>
    <h2 className="uk-margin-medium-bottom">{title}</h2>
    <MoviePosterGrid movies={movies} />
    <div>
      <Link to={url} className="uk-button uk-button-default">
        Ver mais
      </Link>
    </div>
  </SectionPreviewContainer>
);

SectionPreview.propTypes = {
  title: PropTypes.string.isRequired,
  url: PropTypes.string.isRequired,
  movies: PropTypes.arrayOf(
    PropTypes.shape({
      id: PropTypes.number.isRequired,
      title: PropTypes.string.isRequired,
      poster: PropTypes.string.isRequired,
      status: PropTypes.string.isRequired,
    }),
  ).isRequired,
};

export default SectionPreview;
