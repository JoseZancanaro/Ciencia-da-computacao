import React from 'react';
import { Link } from 'react-router-dom';
import { pages } from '../../../services/app-info';

import Search from './Search';
import Login from './Login';

import Logo from '../../../assets/images/logo.svg';
import { MenuContainer } from './styles';

const Menu = () => {
  const { pathname: currentUrl } = window.location;

  return (
    <MenuContainer>
      <div uk-sticky="show-on-up: true; animation: uk-animation-slide-top; bottom: #bottom">
        <div className="uk-container">
          <nav className="uk-navbar-container uk-navbar-transparent" uk-navbar="">
            <div className="uk-navbar-left">
              <img src={Logo} alt="Movie Finder" />
              <ul className="uk-navbar-nav">
                {pages
                  .filter(item => item.type === 'menu')
                  .map(item => (
                    <li key={item.id} className={currentUrl === item.url ? 'uk-active' : ''}>
                      <Link to={item.url}>{item.title}</Link>
                    </li>
                  ))}
              </ul>
            </div>
            <div className="uk-navbar-right">
              <ul className="uk-navbar-nav uk-text-center">
                <li>
                  <Search />
                </li>
                <li>
                  <Login />
                </li>
              </ul>
            </div>
          </nav>
        </div>
      </div>
    </MenuContainer>
  );
};

export default Menu;
