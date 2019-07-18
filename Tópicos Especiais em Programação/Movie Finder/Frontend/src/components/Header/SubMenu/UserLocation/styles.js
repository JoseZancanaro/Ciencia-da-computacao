import styled from 'styled-components';

import { ColorDarkGrey, ColorPrimary } from '../../../../styles';

export const Location = styled.a`
  color: ${ColorDarkGrey} !important;
  text-decoration: none !important;

  &:hover {
    svg {
      color: ${ColorPrimary};
    }
  }

  svg {
    font-size: 15px;
    margin-right: 8px;
    padding-bottom: 4px;
  }
`;
