import styled from 'styled-components';

import { ColorPrimary } from '../../styles';

export const SectionPreviewContainer = styled.section`
  padding: 70px 0 70px 0;

  h2 {
    text-align: center;
  }

  div {
    display: flex;
    justify-content: center;
    align-items: center;

    a {
      margin-top: 20px;

      font-size: 20px;
      text-transform: none;

      color: ${ColorPrimary} !important;
      border: 3px solid ${ColorPrimary} !important;

      &:hover {
        opacity: 0.9;
      }
    }
  }
`;
