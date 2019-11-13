-- Criação das tabelas
CREATE TABLE cliente (
	id serial,
	nome varchar(255) NOT NULL,
	_pontos int NOT NULL,
	PRIMARY KEY (id)
);

CREATE TABLE venda (
	id serial,
	data date NOT NULL,
	_valor_total float DEFAULT 0,
	cliente_id int,
	PRIMARY KEY (id)
);

CREATE TABLE produto (
	id serial,
	nome varchar(255) NOT NULL,
	qtd_estoque int NOT NULL CHECK (qtd_estoque >= 0),
	PRIMARY KEY (id)
);

CREATE TABLE venda_produto (
	quantidade int NOT NULL,
	valor_unitario float NOT NULL,
	_valor_total float NOT NULL DEFAULT 0,
	produto_id int,
	venda_id int,
	PRIMARY KEY (produto_id, venda_id)
);

-- Relacionamento entre tabelas
ALTER TABLE venda ADD FOREIGN KEY (cliente_id) REFERENCES cliente (id);
ALTER TABLE venda_produto ADD FOREIGN KEY (produto_id) REFERENCES produto (id);
ALTER TABLE venda_produto ADD FOREIGN KEY (venda_id) REFERENCES venda (id);

-- Valores que devem ser tratados:
-- (1) cliente._pontos -> redundante
-- (2) venda_produto._valor_total -> redundante
-- (3) venda._valor_total -> redundante
-- (4) produto.qtd_estoque -> atualizar quando um produto for vendido

-- Parte 02 - INSERT e UPDATE
-- Parte 03 - INSERT, UPDATE e DELETE
-- Parte 04 - INSERT, UPDATE e DELETE

-- Parte 01
CREATE OR REPLACE FUNCTION tgAtualizarPontos() RETURNS trigger AS
$$
DECLARE
	valor int := 0;
	retorno record;
BEGIN
	IF (TG_OP = 'INSERT') THEN
		valor := 1;
		retorno := NEW;
	ELSIF (TG_OP = 'DELETE') THEN
		valor := -1;
		retorno := OLD;
	END IF;

	UPDATE cliente SET _pontos = _pontos + valor WHERE id = retorno.cliente_id;
	RETURN retorno;
END;
$$
LANGUAGE PLPGSQL;

-- Parte 02, 03 e 04
CREATE OR REPLACE FUNCTION tgValidarVendaProduto() RETURNS trigger AS
$$
BEGIN
	IF (TG_OP = 'INSERT') THEN
		NEW._valor_total = NEW.valor_unitario * NEW.quantidade;
		
		UPDATE produto SET qtd_estoque = qtd_estoque - NEW.quantidade
		WHERE id = NEW.produto_id;
		
		UPDATE venda SET _valor_total = _valor_total + NEW._valor_total
		WHERE id = NEW.venda_id;
		
		RETURN NEW;
		
	ELSIF (TG_OP = 'UPDATE') THEN
		NEW._valor_total = NEW.valor_unitario * NEW.quantidade;
		
		UPDATE produto SET qtd_estoque = qtd_estoque - (NEW.quantidade - OLD.quantidade) 
		WHERE id = NEW.produto_id;
		
		UPDATE venda SET _valor_total = _valor_total + (NEW._valor_total - OLD._valor_total)
		WHERE id = NEW.venda_id;
		
		RETURN NEW;
	
	ELSE
		UPDATE produto SET qtd_estoque = qtd_estoque + OLD.quantidade
		WHERE id = OLD.produto_id;
		
		UPDATE venda SET _valor_total = _valor_total - OLD._valor_total
		WHERE id = OLD.venda_id;
		
		RETURN OLD;
	END IF;
END;
$$
LANGUAGE PLPGSQL;

-- Criação do TRIGGER para a parte 01
CREATE TRIGGER atualizarPontos BEFORE INSERT OR DELETE ON venda
FOR EACH ROW EXECUTE PROCEDURE tgAtualizarPontos();

-- Criação do TRIGGER para a parte 02, 03 e 04  
CREATE TRIGGER validarVendaProduto BEFORE INSERT OR UPDATE OR DELETE ON venda_produto
FOR EACH ROW EXECUTE PROCEDURE tgValidarVendaProduto();

