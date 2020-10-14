import React from 'react';

import {
  FaFacebookSquare, FaInstagram, FaTwitter, FaYoutube,
} from 'react-icons/fa';

import { Icons } from './styles';

const SocialIcons = () => (
  <Icons>
    <a href="#facebook">
      <FaFacebookSquare className="icon-facebook" />
    </a>
    <a href="#instagram">
      <FaInstagram className="icon-instagram" />
    </a>
    <a href="#twitter">
      <FaTwitter className="icon-twitter" />
    </a>
    <a href="#youtube">
      <FaYoutube className="icon-youtube" />
    </a>
  </Icons>
);

export default SocialIcons;
