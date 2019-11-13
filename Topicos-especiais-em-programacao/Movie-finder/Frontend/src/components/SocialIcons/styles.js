import styled from 'styled-components';

import { ColorDarkGrey } from '../../styles';

export const Icons = styled.div`
  a {
    color: ${ColorDarkGrey};
    margin-right: 15px;
    padding-bottom: 2px;

    svg {
      font-size: 20px;
    }

    &:hover {
      .icon-facebook {
        color: #3b5998;
      }
      .icon-instagram {
        color: #c13584;
      }
      .icon-twitter {
        color: #00a3e0;
      }
      .icon-youtube {
        color: #e60000;
      }
    }
  }
`;
