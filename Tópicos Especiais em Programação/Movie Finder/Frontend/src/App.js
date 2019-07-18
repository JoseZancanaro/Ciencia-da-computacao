import React, { Component, Fragment } from "react";
import { Helmet } from "react-helmet";

import Routes from "./routes";
import { title, description } from "./services/app-info";

import { GlobalStyle, Offline } from "./styles";

export default class App extends Component {
  state = {
    online: navigator.onLine
  };

  loading = () => {
    window.onload = function() {
      const progressBar = document.getElementById("ipl-progress-indicator");

      if (progressBar) {
        // fade out
        progressBar.classList.add("available");
        document.body.style.overflow = "visible";
        setTimeout(() => {
          // remove from DOM
          progressBar.outerHTML = "";
        }, 800);
      }
    };
  };

  componentDidMount() {
    this.loading();

    window.addEventListener("online", this.handleNetworkChange);
    window.addEventListener("offline", this.handleNetworkChange);
  }

  componentWillUnmount() {
    window.removeEventListener("online", this.handleNetworkChange);
    window.removeEventListener("offline", this.handleNetworkChange);
  }

  handleNetworkChange = () => {
    this.setState({ online: navigator.onLine });
  };

  render() {
    const { online } = this.state;

    return (
      <Fragment>
        <Helmet>
          <title>{title}</title>
          <meta name="description" content={description} />
        </Helmet>

        <Routes />

        {!online && <Offline>Você está offline</Offline>}
        <GlobalStyle />
      </Fragment>
    );
  }
}
