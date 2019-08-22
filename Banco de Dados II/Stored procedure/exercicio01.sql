--Criação de tabela:
CREATE TABLE somalog (
	id serial NOT NUL,
	valor_1 int NOT NULL,
	valor_2 int NOT NULL,
	resultado int NOT NULL,
	PRIMARY KEY (id)
);

CREATE OR REPLACE FUNCTION exercicio01(int, int) RETURNS INT AS
$$
	INSERT INTO somalog (valor_1, valor_2, resultado) VALUES ($1, $2, $1 + $2);
	SELECT $1 + $2;
$$
LANGUAGE SQL;

SELECT exercicio01(10,2);

