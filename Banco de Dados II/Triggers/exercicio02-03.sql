-- Criação das tabelas
CREATE TABLE professor (
	id serial,
	nome varchar(255),
	ativo bool,
	PRIMARY KEY (id)
);

CREATE TABLE disciplina (
	id serial,
	nome varchar(255),
	professor_id int,
	PRIMARY KEY (id)
);

-- Relacionamento entre tabelas
ALTER TABLE disciplina ADD FOREIGN KEY (professor_id) REFERENCES professor (id); 

-- Exercício 02
CREATE OR REPLACE FUNCTION tgValidarProfAtivo() RETURNS trigger AS
$$
BEGIN
	IF NOT NEW.ativo THEN
		RAISE EXCEPTION 'Professor inativo não pode se relacionar com disciplinas';
	END IF;
	
	RETURN NEW;
END;
$$
LANGUAGE PLPGSQL;

--Exercício 03
CREATE OR REPLACE FUNCTION tgValidarRemocaoProf() RETURNS trigger AS
$$
DECLARE 
	linhaAtual record;
BEGIN
	FOR linhaAtual IN SELECT professor_id FROM disciplina LOOP
		IF OLD.id = linhaAtual.professor_id THEN
			RAISE EXCEPTION 'Não pode desativar professor relacionado com disciplina';
		END IF;
	END LOOP;

	RETURN OLD;
END;
$$
LANGUAGE PLPGSQL;

-- Criação do TRIGGER para o exercício 02
CREATE TRIGGER professorAtivo BEFORE INSERT OR UPDATE ON professor
FOR EACH ROW EXECUTE PROCEDURE tgValidarProfAtivo();

-- Criação do TRIGGER para o exercício 03
CREATE TRIGGER remocaoProfessor BEFORE DELETE ON professor
FOR EACH ROW EXECUTE PROCEDURE tgValidarRemocaoProf();

