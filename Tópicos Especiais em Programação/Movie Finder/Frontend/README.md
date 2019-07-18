<img src="https://moviefinder-univali.firebaseapp.com/images/icons/icon-72x72.png" alt="Movie Finder Logo" width="50"/>

**PROJETO MOVIE FINDER**

>***Acadêmicos:*** Allan Baron, Israel Efraim e José Carlos.

**Visão geral**

>Sistema web para busca de filmes e localização de cinemas que apresentam dados filmes. O sistema será capaz de apresentar um catálogo de filmes disponíveis em diversos complexos de redes de cinemas. Ademais, será possível que os usuários realizem avaliações e críticas dos filmes.

**Detalhamento/funcionalidades**

- Catálogo de filmes
  - Em cartaz
  - Em breve
- Detalhamento sobre filmes
  - Mídia (fotos, trailer)
  - Categoria (gênero)
  - Faixa indicativa de idade
  - Duração
  - Data de lançamento
  - Sinopse
  - Diretor
  - Atores
  - Cinemas e horários disponíveis
  - Situação (cartaz | breve)
  - Áudio (dublado | legendado | original)
- Interação para usuário
  - Cadastro
    - Nome
    - E-mail
    - Senha
    - Avatar
  - Avaliação em filmes
    - Contador de qualidade na forma de estrelas (5 estrelas)
  - Comentário em filmes
- Plataforma para cinemas
  - Cadastro
    - CNPJ
    - Nome do complexo
    - Localização
    - Responsáveis
    - Telefone
    - E-mail
    - Preço das modalidades dos ingressos
    - Usuário / Senha
  - Cadastro de disponibilidade de filmes e horários

**Atores**

- Gestor do sistema
  - Alimenta o sistema com os lançamentos e respectivos dados referentes a este. Aprova o cadastro dos complexos de rede de cinema.
- Agente do Cinema
  - Solicita o cadastro do seu complexo de rede de cinema e insere a disponibilidade e horários de filmes.
- Usuário comum
  - Pesquisa, avalia e comenta sobre os filmes registrados. Este ator é responsável por realizar o cadastro de seu perfil.

**Inspiração/concorrente**

- AdoroCinema
- Trivago
- Buscapé
- Booking.com
- CineGracher

----

**Iniciando o Projeto**

No diretório do projeto, você pode executar:

**`npm start`**

>Executa o aplicativo no modo de desenvolvimento. <br>
Abra [http://localhost:3000](http://localhost:3000) para visualizá-lo no navegador.

**`npm run build`**

>Cria o aplicativo para produção na pasta `build` .
