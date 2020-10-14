import styled from 'styled-components';
import { ColorPrimary, ColorLightGrey, ColorDarkGrey } from '../../styles';

export const BreadcrumbsContainer = styled.section`
  background: ${ColorLightGrey};
  padding: 30px;

  a,
  span {
    font-size: 16px;
    font-weight: bolder;
    color: ${ColorDarkGrey};
    text-decoration: none;
  }

  h1 {
    font-size: 36px;
    margin-top: 5px;
    color: ${ColorPrimary};
  }
`;
