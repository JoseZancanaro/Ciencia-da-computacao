import React, { Component } from 'react';

import SectionBase from '../SectionBase';

import api from '../../services/api';

class SectionReleased extends Component {
  state = {
    movies: [],
  };

  async componentDidMount() {
    const response = await api.get('movies');

    this.setState({ movies: response.data.filter(movie => movie.status === 'released') });
  }

  render() {
    const { movies } = this.state;
    const dir = [{ id: 0, title: 'Home', url: '/' }, { id: 1, title: 'Filmes' }];

    return <SectionBase title="Em Cartaz" dir={dir} movies={movies} />;
  }
}

export default SectionReleased;
