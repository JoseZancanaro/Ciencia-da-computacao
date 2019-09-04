-- Criação da tabela:
CREATE TABLE CondicaoVento (
	id serial,
	velocidade float,
	direcao float,
	PRIMARY KEY (id)
);

-- Função para popular a tabela CondicaoVento
CREATE OR REPLACE FUNCTION popularTabelaCondicaoVento(qtdInsercao int) RETURNS void AS
$$
DECLARE
	i int := 1;
BEGIN
	FOR i IN i..qtdInsercao LOOP
		INSERT INTO CondicaoVento (id, velocidade, direcao) 
		VALUES (i, random() * 200, random() * 360);
	END LOOP;
END;
$$
LANGUAGE PLPGSQL;

-- Popular a tabela com 200 inserções.
select popularTabelaCondicaoVento(200);
	
-- Exercício 03
CREATE OR REPLACE FUNCTION direcaoDescricaoVento(angulo decimal) RETURNS varchar AS
$$
DECLARE	
	descricaoVento varchar(5) := '';
BEGIN
	IF (angulo BETWEEN 315 AND 360) OR (angulo BETWEEN 0 and 45) THEN
		descricaoVento := 'Norte';
	ELSIF angulo BETWEEN 45 AND 135 THEN
		descricaoVento := 'Leste';
	ELSIF angulo BETWEEN 135 AND 225 THEN
		descricaoVento := 'Sul';
	ELSIF angulo BETWEEN 225 AND 315 THEN
		descricaoVento := 'Oeste';
	ELSE
		RAISE EXCEPTION 'Angulo informado: % é menor que 0 ou maior que 360', angulo;
	END IF;

	RETURN descricaoVento;
END;
$$
LANGUAGE PLPGSQL;

-- Exercício 04
CREATE OR REPLACE FUNCTION incidenciaPorDirecaoDoVento_1() RETURNS SETOF varchar AS
$$
DECLARE
 	total int := COUNT(id) FROM CondicaoVento;
 	linhaAtual record;
BEGIN
	FOR linhaAtual IN 
		SELECT direcaoDescricaoVento(direcao::decimal) AS direcao, COUNT(direcaoDescricaoVento(direcao::decimal)) AS qtdDirecao 
		FROM CondicaoVento GROUP BY direcaoDescricaoVento(direcao::decimal)
	LOOP
		RETURN NEXT CONCAT(linhaAtual.direcao, ': ', ROUND(linhaAtual.qtdDirecao * 100 / total, 2), '%');
	END LOOP;
END;
$$
LANGUAGE PLPGSQL;

-- Exercício 05
CREATE TYPE vento AS (direcao varchar(5), percentual float);

CREATE OR REPLACE FUNCTION incidenciaPorDirecaoDoVento_2() RETURNS SETOF vento AS
$$
DECLARE
	retorno vento;
 	total int := COUNT(id) FROM CondicaoVento;
 	linhaAtual record;
BEGIN
	FOR linhaAtual IN 
		SELECT direcaoDescricaoVento(direcao::decimal) AS direcao, COUNT(direcaoDescricaoVento(direcao::decimal)) AS qtdDirecao 
		FROM CondicaoVento GROUP BY direcaoDescricaoVento(direcao::decimal)
	LOOP
		retorno.direcao := linhaAtual.direcao;
		retorno.percentual := linhaAtual.qtdDirecao * 100 / total;
		RETURN NEXT retorno;
	END LOOP;
END;
$$
LANGUAGE PLPGSQL;

