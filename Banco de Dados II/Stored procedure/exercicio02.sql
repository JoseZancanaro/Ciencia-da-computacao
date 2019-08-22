-- Criação de tabela:
CREATE TABLE calculadoraLog (
	id SERIAL NOT NULL,
	valor_1 float NOT NULL,
	valor_2 float NOT NULL,
	operador char NOT NULL,
	resultado float NOT NULL,
	PRIMARY KEY (id)
);

CREATE OR REPLACE FUNCTION calcular(x float, y float, _operador char) RETURNS  float AS
$$
DECLARE
	_resultado float := 0;
BEGIN
	IF sinal = '+' THEN
		_resultado := x + y;
	ELSIF sinal = '-' THEN 
		_resultado := x - y; 
	ELSIF sinal = '*' THEN 
		_resultado := x * y;
	ELSIF sinal = '/' THEN
		IF y = 0 THEN 
			RAISE EXCEPTION 'Impossível dividir por Zer0.';
		END IF;
		_resultado := x / y;
	ELSE
	 	RAISE EXCEPTION 'Operador "%" inválido.', _operador; 
	END IF;
	
	INSERT INTO calculadoraLog (valor_1, valor_2, operador, resultado) VALUES (x, y, _operador, _resultado);
	RETURN _resultado;
END;
$$
LANGUAGE PLPGSQL;

SELECT calcular(11, 0, '/');

-- Lembrete:
-- Célula: RETURNS tipo
-- Vários registros: RETURNS record + ter parametros OUT nome tipo
-- Várias células RETURNS setof tipo
-- RAISE NOTICE exibe mensagem no console.



