import React from 'react';

import SocialIcons from '../../SocialIcons';
import UserLocation from './UserLocation';

import { SubMenuContainer, SectionLeft, SectionRight } from './styles';

const SubMenu = () => (
  <SubMenuContainer>
    <div className="uk-container uk-flex">
      <SectionLeft>
        <SocialIcons />
      </SectionLeft>

      <SectionRight>
        <UserLocation />
      </SectionRight>
    </div>
  </SubMenuContainer>
);

export default SubMenu;
