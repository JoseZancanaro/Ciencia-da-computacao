import React from 'react';
import PropTypes from 'prop-types';

import Base from '../Base';
import NoMatchImage from '../../assets/images/404.png';

import { Breadcrumbs } from '../../components';
import { NoMatchPageContainer } from './styles';

const NoMatchPage = (props) => {
  const { match } = props;

  const dir = [{ id: 0, title: 'Home', url: '/' }, { id: 1, title: 'Página 404' }];

  return (
    <Base
      currentUrlPage={match.url}
      page={() => (
        <div>
          <Breadcrumbs title="Página não encontrada" dir={dir} />
          <NoMatchPageContainer className="uk-container">
            <img src={NoMatchImage} alt="Para o bem do universo, esta página foi destruída." />
          </NoMatchPageContainer>
        </div>
      )}
    />
  );
};

NoMatchPage.propTypes = {
  match: PropTypes.shape({
    url: PropTypes.string.isRequired,
  }).isRequired,
};

export default NoMatchPage;
