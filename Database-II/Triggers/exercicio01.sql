-- Criação da tabela
CREATE TABLE logCalculadora (
	id serial,
	valor_1 float,
	valor_2 float,
	resultado float,
	operacao char,
	PRIMARY KEY (id)
);

-- Criação da função trigger
CREATE OR REPLACE FUNCTION tgCalcularResultado() RETURNS trigger AS
$$
BEGIN
	IF NEW.operacao = '+' THEN
		NEW.resultado := NEW.valor_1 + NEW.valor_2;
	ELSIF NEW.operacao = '-' THEN
		NEW.resultado := NEW.valor_1 - NEW.valor_2;
	ELSIF NEW.operacao = '*' THEN
		NEW.resultado := NEW.valor_1 * NEW.valor_2;
	ELSIF NEW.operacao = '/' THEN
		IF NEW.valor_2 = 0 THEN
			RAISE EXCEPTION 'Impossível dividir por 0.';
		END IF;
		NEW.resultado := NEW.valor_1 / NEW.valor_2;
	ELSE
		RAISE EXCEPTION 'Operador (%) inválido', NEW.operacao;
	END IF;

	RETURN NEW;
END;
$$
LANGUAGE PLPGSQL;

-- Criação do TRIGGER
CREATE TRIGGER resultadoLogCalculadora BEFORE INSERT OR UPDATE ON logCalculadora
FOR EACH ROW EXECUTE PROCEDURE tgCalcularResultado();

