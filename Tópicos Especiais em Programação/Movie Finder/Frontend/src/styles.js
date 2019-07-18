import styled, { createGlobalStyle } from "styled-components";

export const FontPrimary = "Open Sans";
export const ColorPrimary = "#890000";
export const ColorLightGrey = "#ececec";
export const ColorDarkGrey = "#5a5a5a";

export const GlobalStyle = createGlobalStyle`
  /* Uikit */
  @import url('https://cdnjs.cloudflare.com/ajax/libs/uikit/3.1.4/css/uikit.min.css');

  /* Fonts */
  @import url('https://fonts.googleapis.com/css?family=Open+Sans');

  * {
    box-sizing: border-box;
  }

  html {
    font-family: "${FontPrimary}";
    font-size: 14px;
    font-weight: 400;
    line-height: 1.5em;

    @media (min-width: 960px) {
      font-size: 16px;
    }
  }
`;

export const Offline = styled.div`
  position: fixed;
  bottom: 0;
  left: 0;
  height: 40px;
  width: 100%;
  background: #c15959;
  color: #fff;
  display: flex;
  justify-content: center;
  align-items: center;
  font-weight: 600;
`;
