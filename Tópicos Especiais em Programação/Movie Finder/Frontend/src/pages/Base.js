import React, { Fragment } from 'react';
import PropTypes from 'prop-types';

import { Header, Footer } from '../components';

const Base = (props) => {
  const { page } = props;

  return (
    <Fragment>
      <Header />

      <section uk-height-viewport="expand: true">{page()}</section>

      <Footer />
    </Fragment>
  );
};

Base.propTypes = {
  page: PropTypes.func.isRequired,
};

export default Base;
