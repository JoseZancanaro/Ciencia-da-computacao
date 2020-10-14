import React, { Fragment } from 'react';
import PropTypes from 'prop-types';
import { Link } from 'react-router-dom';

import { BreadcrumbsContainer } from './styles';

const Breadcrumbs = (props) => {
  const { dir, title } = props;

  return (
    <BreadcrumbsContainer>
      <div className="uk-container">
        <nav typeof="BreadcrumbList" vocab="http://schema.org/">
          {dir.map((item, r) => (item.url ? (
            <Fragment key={item.id}>
              <span property="itemListElement" typeof="ListItem">
                <Link to={item.url} property="item" typeof="WebPage" itemProp="url">
                  <span property="name">{item.title}</span>
                </Link>
              </span>

              <span>{dir.lenght !== r ? ' / ' : ''}</span>
            </Fragment>
          ) : (
            <span key={item.id} property="itemListElement" typeof="ListItem">
              <span property="name">{item.title}</span>
            </span>
          )))}
        </nav>

        <h1>{title}</h1>
      </div>
    </BreadcrumbsContainer>
  );
};

Breadcrumbs.propTypes = {
  dir: PropTypes.arrayOf(PropTypes.object.isRequired).isRequired,
  title: PropTypes.string.isRequired,
};

export default Breadcrumbs;
