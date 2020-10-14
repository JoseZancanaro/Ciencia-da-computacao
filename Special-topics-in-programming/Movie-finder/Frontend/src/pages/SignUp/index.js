import React from "react";

import Base from "../Base";

import { Breadcrumbs, SignUpForm } from "../../components";

const SignUp = () => {
  const dir = [
    { id: 0, title: "Home", url: "/" },
    { id: 1, title: "Cadastro" }
  ];
  return (
    <Base
      page={() => (
        <>
          <Breadcrumbs dir={dir} title="Cadastre-se" />
          <div className="uk-container">
            <SignUpForm />
          </div>
        </>
      )}
    />
  );
};

export default SignUp;
