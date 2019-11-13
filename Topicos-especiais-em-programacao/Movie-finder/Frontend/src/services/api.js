import axios from 'axios';

const api = axios.create({
  baseURL: 'https://api-moviefinder-univali.herokuapp.com/',
});

export default api;
