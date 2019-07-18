import React, { Component } from 'react';

import SectionBase from '../SectionBase';

import api from '../../services/api';

class SectionCommingSoon extends Component {
  state = {
    movies: [],
  };

  async componentDidMount() {
    const response = await api.get('movies');

    this.setState({ movies: response.data.filter(movie => movie.status === 'comming-soon') });
  }

  render() {
    const { movies } = this.state;
    const dir = [{ id: 0, title: 'Home', url: '/' }, { id: 1, title: 'Filmes' }];

    return <SectionBase title="Em Breve" dir={dir} movies={movies} />;
  }
}

export default SectionCommingSoon;
