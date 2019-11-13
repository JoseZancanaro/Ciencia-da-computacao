import React from 'react';
import { FaUser } from 'react-icons/fa';
import { Link } from 'react-router-dom';
import { pages } from '../../../../services/app-info';

const Login = () => (
  <>
    <FaUser />
    <span>
      <Link to={pages.find(item => item.type === 'sign-up').url}>Login</Link>
    </span>
  </>
);

export default Login;
