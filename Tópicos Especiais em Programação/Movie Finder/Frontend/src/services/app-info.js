export const title = 'Movie Finder';
export const description = 'Encontre o cinema mais perto de você pelo menor preço.';

export const pages = [
  {
    id: 0,
    title: 'Home',
    url: '/',
    type: 'menu',
  },
  {
    id: 1,
    title: 'Em Cartaz',
    optionalTitle: 'Filmes em Cartaz',
    url: '/filmes/em-cartaz',
    movieStatus: 'released',
    type: 'menu',
  },
  {
    id: 2,
    title: 'Em Breve',
    optionalTitle: 'Filmes em Breve',
    url: '/filmes/em-breve',
    movieStatus: 'comming-soon',
    type: 'menu',
  },
  {
    id: 3,
    title: 'Página 404',
    optionalTitle: 'Página não encontrada',
    type: '404',
  },
  {
    id: 4,
    title: 'Cadastre-se',
    url: '/cadastro',
    type: 'sign-up',
  },
];
