-- Questão 01
CREATE OR REPLACE FUNCTION calculaBTU(tamAmbiente integer, nPessoa integer, nEquipamento integer, exposicaoSol boolean)
RETURNS integer AS
$$
DECLARE 
	qtdBTU integer := 0;
BEGIN
	IF (exposicaoSol) THEN 
		qtdBTU := qtdBTU + tamAmbiente * 800;
	ELSE
		qtdBTU := qtdBTU + tamAmbiente * 600;
	END IF;
	
	IF (nPessoa > 1) THEN
		qtdBTU := qtdBTU + nPessoa * 600;
	END IF;
	
	qtdBTU := qtdBTU + nEquipamento * 600;
	
	RETURN qtdBTU;
END;
$$
LANGUAGE PLPGSQL;

-- Questão 02
CREATE OR REPLACE FUNCTION calculaConsumoEquipamento(ligado timestamp, desligado timestamp, potencia integer) 
RETURNS float AS
$$
DECLARE
	consumoTotal float := 0.0;
	horasFuncionandoTime time := desligado::time - ligado::time;
	horasFuncionando integer := 0;
BEGIN
	IF (desligado::time < ligado::time) THEN
		RAISE EXCEPTION 'Tempo desligado é menos que o tempo ligado';
	END IF;
	
	horasFuncionando := EXTRACT(hour FROM horasFuncionandoTime);
	
	consumoTotal := potencia * horasFuncionando / 1000;
	RETURN consumoTotal;
END;
$$
LANGUAGE PLPGSQL;

-- Questão 03
CREATE OR REPLACE FUNCTION tgVerificarTarefaConcluida() RETURNS trigger AS
$$
BEGIN
	IF (NEW.concluida) THEN
		RAISE EXCEPTION 'RN_NAO_E_PERMITIDO_CADASTRAR_TAREFAS_COM_SITUACAO_CONCLUIDA';
	END IF;
	
	RETURN NEW;
END;
$$
LANGUAGE PLPGSQL;

-- Gatilho questão 03
CREATE TRIGGER verificarTarefaConcluida BEFORE INSERT ON tarefa
FOR EACH ROW EXECUTE PROCEDURE tgVerificarTarefaConcluida();

-- Questão 04
CREATE OR REPLACE FUNCTION tgPontoReputacao() RETURNS trigger AS
$$
DECLARE 
	valor integer := 0;
BEGIN
	IF (NOT OLD.concluida) AND (NEW.concluida) THEN
		valor := 1;
	END IF;
	
	UPDATE colaborador SET _reputacao = _reputacao + valor WHERE id = NEW.colaborador_id;
	RETURN NEW;
END;
$$
LANGUAGE PLPGSQL;

-- Gatilho questão 04
CREATE TRIGGER pontoReputacao BEFORE UPDATE ON tarefa
FOR EACH ROW EXECUTE PROCEDURE tgPontoReputacao();

-- Questão 05
CREATE OR REPLACE FUNCTION tgTarefaReaberta() RETURNS trigger AS
$$
DECLARE
	valor integer := 0;
BEGIN
	IF (OLD.concluida) AND (NOT NEW.concluida) THEN 
		valor := -3;
	END IF;
	
	UPDATE colaborador SET _reputacao = _reputacao + valor WHERE id = NEW.colaborador_id;
	RETURN NEW;
END;
$$
LANGUAGE PLPGSQL;

-- Gatilho questão 05
CREATE TRIGGER tarefaReaberta BEFORE UPDATE ON tarefa
FOR EACH ROW EXECUTE PROCEDURE tgTarefaReaberta();

-- Questão 06
CREATE OR REPLACE FUNCTION tgCalcularCusto() RETURNS trigger AS
$$
DECLARE 
	linhaAtual record;
BEGIN
	FOR linhaAtual IN SELECT cargo.salario_por_hora / 60 AS salario_por_minuto
		FROM cargo INNER JOIN colaborador ON (cargo.id = colaborador.cargo_id)
		WHERE colaborador.id = NEW.colaborador_id LOOP
	
		NEW._custo = linhaAtual.salario_por_minuto * NEW.duracao_em_minutos;
	END LOOP;
	
	RETURN NEW;
END;
$$
LANGUAGE PLPGSQL;

-- Gatilho questão 06
CREATE TRIGGER calcularCusto BEFORE INSERT OR UPDATE ON tarefa
FOR EACH ROW EXECUTE PROCEDURE tgCalcularCusto();
