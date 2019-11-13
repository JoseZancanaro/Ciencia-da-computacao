import React from 'react';
import { title } from '../../services/app-info';

import SocialIcons from '../SocialIcons';

import { FooterContainer } from './styles';

const Footer = () => {
  const year = new Date().getFullYear();

  return (
    <FooterContainer>
      <SocialIcons />
      <div>{`Copyright © ${year} - ${title} | Todos os direitos reservados.`}</div>
    </FooterContainer>
  );
};

export default Footer;
