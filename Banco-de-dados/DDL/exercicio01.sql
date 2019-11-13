-- Criação de tabelas:
CREATE TABLE categoria (
    id integer NOT NULL,
    descricao varchar(255) NULL,
    PRIMARY KEY (id)
);

CREATE TABLE marca (
    id integer NOT NULL,
    nome varchar(255) NULL,
    PRIMARY KEY (id)
);

CREATE TABLE unidade (
    id integer NOT NULL,
    descricao varchar(255) NULL,
    PRIMARY KEY (id)
);

CREATE TABLE produto (
    id integer NOT NULL,
    descricao varchar(255) NULL,
    preco_custo decimal(10,2) NULL,
    preco_venda decimal(10,2) NULL,
    qtd_estoque integer NULL,
    qtd_estoque_minimo integer NULL,
    id_categoria integer NULL,
    id_marca integer NULL,
    id_unidade integer NULL,
    PRIMARY KEY (id)
);

-- Relacionamento entre tabelas:
ALTER TABLE produto ADD FOREIGN KEY (id_categoria) REFERENCES categoria (id);
ALTER TABLE produto ADD FOREIGN KEY (id_marca) REFERENCES marca (id);
ALTER TABLE produto ADD FOREIGN KEY (id_unidade) REFERENCES unidade (id);