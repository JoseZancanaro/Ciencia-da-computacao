import styled from 'styled-components';
import { ColorLightGrey, ColorDarkGrey } from '../../styles';

export const FooterContainer = styled.footer`
  background: ${ColorLightGrey};
  color: ${ColorDarkGrey};
  font-size: 15px;
  padding: 24px;

  div:first-child {
    margin-bottom: 15px;
  }

  div {
    display: flax;
    justify-content: center;
  }
`;
