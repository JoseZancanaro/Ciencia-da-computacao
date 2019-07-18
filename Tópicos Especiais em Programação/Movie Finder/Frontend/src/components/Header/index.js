import React, { Component, Fragment } from 'react';
import { Helmet } from 'react-helmet';

import { title, pages } from '../../services/app-info';
import SubMenu from './SubMenu';
import Menu from './Menu';

export default class Header extends Component {
  state = { metaTitle: '' };

  componentDidMount() {
    const { pathname: currentUrl } = window.location;

    let currentPage = pages.find(item => item.url === currentUrl);

    if (!currentPage) currentPage = pages.find(item => item.type === '404');

    this.setState({
      metaTitle: currentPage.optionalTitle ? currentPage.optionalTitle : currentPage.title,
    });
  }

  render() {
    const { metaTitle } = this.state;

    return (
      <Fragment>
        <Helmet>
          <title>{`${metaTitle} | ${title}`}</title>
        </Helmet>

        <header>
          <SubMenu />
          <Menu />
        </header>
      </Fragment>
    );
  }
}
