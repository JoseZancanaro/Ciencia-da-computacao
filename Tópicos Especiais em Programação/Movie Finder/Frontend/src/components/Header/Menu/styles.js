import styled from 'styled-components';
import { ColorDarkGrey } from '../../../styles';

export const MenuContainer = styled.section`
  @import url('https://fonts.googleapis.com/css?family=Roboto&display=swap');

  .uk-sticky.uk-sticky-fixed {
    background: white;
    box-shadow: 0 0 10px #00000073;
  }

  .uk-navbar-left {
    li {
      width: 120px;

      a {
        font-size: 18px;
        font-weight: bold;
        text-transform: none;
        color: ${ColorDarkGrey} !important;
      }

      &.uk-active {
        border-bottom: solid 3px #890000;
      }
    }
  }

  .uk-navbar-right {
    li {
      font-family: 'Roboto', sans-serif;
      font-size: 18px;
      font-weight: bold;
      color: ${ColorDarkGrey};
      width: 120px;

      svg {
        margin-top: -5px;
      }
    }

    span {
      margin-left: 8px;
    }
  }
`;
