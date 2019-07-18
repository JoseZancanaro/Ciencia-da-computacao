import React, { Component } from 'react';
import api from '../../services/api';

import { SlideshowContainer } from './styles';

export default class Slideshow extends Component {
  state = { slides: [] };

  async componentDidMount() {
    const response = await api.get('slideshow');

    this.setState({ slides: response.data });
  }

  render() {
    const { slides } = this.state;

    return (
      <SlideshowContainer>
        <div
          className="uk-position-relative uk-visible-toggle uk-light uk-margin-bottom"
          tabIndex="-1"
          uk-slideshow="ratio: 7:2; animation: push"
        >
          <ul className="uk-slideshow-items">
            {slides.map(slide => (
              <li key={slide.id}>
                {/* <Link to={slide.url}> */}
                <img src={slide.img} alt={slide.title} uk-cover="" />
                {/* </Link> */}
              </li>
            ))}
          </ul>

          <a
            className="uk-position-center-left uk-position-small uk-hidden-hover"
            href="das"
            uk-slidenav-previous=""
            uk-slideshow-item="previous"
          />
          <a
            className="uk-position-center-right uk-position-small uk-hidden-hover"
            href="#sadsa"
            uk-slidenav-next=""
            uk-slideshow-item="next"
          />
        </div>
      </SlideshowContainer>
    );
  }
}
