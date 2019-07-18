import React from 'react';

import { FaMapMarkerAlt } from 'react-icons/fa';

import { Location } from './styles';

const UserLocation = () => (
  <Location href="#localization">
    <FaMapMarkerAlt />
    <span>Encontre o cinema mais perto</span>
  </Location>
);

export default UserLocation;
