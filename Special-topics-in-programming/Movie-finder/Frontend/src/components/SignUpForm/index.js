import React, { Fragment } from "react";

import { SignUpFormContainer } from "./styles";

const SignUpForm = () => (
  <SignUpFormContainer className="uk-flex uk-flex-center uk-section">
    <form>
      <div class="js-upload uk-flex uk-flex-center" uk-form-custom="">
        <input type="file" />
        <button class="uk-button uk-button-default" type="button" tabindex="-1">
          Avatar
        </button>
      </div>

      <div className="uk-margin">
        <input
          className="uk-input uk-form-width-large"
          type="text"
          placeholder="Nome completo"
        />
      </div>
      <div className="uk-margin">
        <input
          className="uk-input uk-form-width-large"
          type="text"
          placeholder="E-mail"
        />
      </div>
      <div className="uk-margin">
        <input
          className="uk-input uk-form-width-large"
          type="text"
          placeholder="Senha"
        />
      </div>
      <div className="uk-margin">
        <input
          className="uk-input uk-form-width-large"
          type="text"
          placeholder="Confirme sua senha"
        />
      </div>
    </form>
  </SignUpFormContainer>
);

export default SignUpForm;
