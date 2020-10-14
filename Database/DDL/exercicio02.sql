-- Criação de tabelas:
CREATE TABLE cargo (
    id integer NOT NULL,
    nome varchar(255) NOT NULL,
    salario_hora decimal(10,2) NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE colaborador (
    id integer NOT NULL,
    id_cargo integer NOT NULL,
    nome varchar(255) NOT NULL,
    ano_contratacao integer NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE projeto (
    id integer NOT NULL,
    nome varchar(50) NOT NULL,
    data_inicio timestamp NOT NULL,
    id_colaborador_gerente integer NULL,
    PRIMARY KEY (id)
);

CREATE TABLE tarefa (
    id integer NOT NULL, 
    id_colaborador_responsavel integer NOT NULL,
    id_projeto integer NOT NULL,
    descricao text NOT NULL,
    duracao_hora decimal(10,2) NOT NULL,
    concluida boolean NOT NULL,
    PRIMARY KEY (id)
);

-- Relacionamento entre tabelas:
ALTER TABLE colaborador ADD FOREIGN KEY (id_cargo) REFERENCES cargo (id);
ALTER TABLE projeto ADD FOREIGN KEY (id_colaborador_gerente) REFERENCES colaborador (id);
ALTER TABLE tarefa ADD FOREIGN KEY (id_colaborador_responsavel) REFERENCES colaborador (id);
ALTER TABLE tarefa ADD FOREIGN KEY (id_projeto) REFERENCES projeto (id);