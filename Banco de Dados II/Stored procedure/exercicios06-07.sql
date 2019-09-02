-- Criação da tabela
CREATE TABLE agendamento (
	id serial,
	cliente varchar(50),
	inicio timestamp,
	termino timestamp,
	primary key (id)
);

-- Função auxiliar que valida o horário de atendimento, das 08:00 ás 12:00 e das 13:30 ás 17:30
CREATE OR REPLACE FUNCTION validarHorario(horarioInicial time, horarioFinal time) RETURNS bool AS
$$	
BEGIN
	IF (horarioInicial >= '08:00:00' AND horarioInicial < '12:00:00') THEN
		IF (horarioFinal > '08:00:00' AND horarioFinal <= '12:00:00') THEN
			RETURN TRUE;
		END IF;
	ELSIF (horarioInicial >= '13:30:00' AND horarioInicial < '17:30:00') THEN
		IF (horarioFinal > '13:30:00' AND horarioFinal <= '17:30:00') THEN
			RETURN TRUE;
		END IF;
	END IF;
	
	RETURN FALSE;
END;
$$
LANGUAGE PLPGSQL;

-- Função auxiliar que valida o intervalo
CREATE OR REPLACE FUNCTION validarIntervalo(dataInicio timestamp, dataFim timestamp) RETURNS bool AS
$$
DECLARE
	linhaAtual record;
BEGIN
	FOR linhaAtual IN SELECT * FROM agendamento LOOP
		IF (dataInicio >= linhaAtual.inicio AND dataInicio < linhaAtual.termino) THEN
			RETURN FALSE;
		ELSIF (dataFim > linhaAtual.inicio AND dataFim <= linhaAtual.termino) THEN
			RETURN FALSE;
		ELSIF (dataInicio < linhaAtual.inicio AND dataFim > linhaAtual.termino) THEN
			RETURN FALSE;
		END IF;
	END LOOP;

	RETURN TRUE;
END;
$$
LANGUAGE PLPGSQL;

-- Exercício 06
CREATE OR REPLACE FUNCTION agendaHorario(dataInicio timestamp, duracao integer, nomeCliente varchar(50))
RETURNS bool AS
$$
DECLARE
	dataFim timestamp := dataInicio + (TO_TIMESTAMP(duracao * 60) AT TIME ZONE 'UTC')::time;
	nomeDia int := EXTRACT(dow FROM dataInicio); 
BEGIN
	-- Verificar se é sábado (6) ou domingo (0)
	IF nomeDia IN (0, 6) THEN
		RETURN FALSE;
	END IF;

	-- Verificar se pode inserir na tabela
	IF (validarHorario(dataInicio::time, dataFim::time)) 
		AND validarIntervalo(dataInicio, dataFim) THEN
			
		INSERT INTO agendamento (cliente, inicio, termino) VALUES (nomeCliente, dataInicio, dataFim);
		RETURN TRUE;
	END IF;

	RETURN FALSE;
END;
$$
LANGUAGE PLPGSQL;

-- Exercício 07
CREATE OR REPLACE FUNCTION proximoHorarioVago(duracao integer) RETURNS timestamp AS 
$$
DECLARE
	dataAtual timestamp := '2019-09-02 13:27:00';
	duracaoTime time := (TO_TIMESTAMP(60 * duracao) AT TIME ZONE 'UTC')::time;
	dataFinal timestamp := dataAtual + duracaoTime;
	intervalo timestamp;
	horarioVago timestamp;
	terminoAnterior timestamp;
	horarioAtualValido bool := validarHorario(dataAtual::time, dataFinal::time);
	primeiroDaTabela bool := TRUE;
	tabelaVazia bool := FALSE;
	linhaAtual record;
BEGIN
	-- Verificar se tabela agendamento esta vazia
	IF (SELECT count(id) FROM agendamento) = 0 THEN
		tabelaVazia := TRUE;
		-- Verificar se a função foi chamada em um sábado(6) ou domingo(0)
		IF (EXTRACT(dow FROM dataAtual) = 6) THEN  
			horarioVago := concat(dataAtual::date + 2, ' 08:00:00');
			RETURN horarioVago;
		ELSIF (EXTRACT(dow FROM dataAtual) = 0) THEN
			horarioVago := concat(dataAtual::date + 1, ' 08:00:00');
			RETURN horarioVago;
		END IF;
	END IF;

	-- Verificar se precisa redefinir a dataAtual para um horário válido
	IF (NOT horarioAtualValido AND (dataAtual::time < '12:00:00' OR dataAtual::time > '17:30:00')) THEN
		dataAtual := concat(current_timestamp::date, ' 08:00:00');
	ELSE
		dataAtual := concat(current_timestamp::date, ' 13:30:00');
	END IF;

	dataFinal := dataAtual + duracaoTime;
	horarioAtualValido := TRUE;

	-- Verificar se possível horário vago
	IF (tabelaVazia) AND (validarHorario(dataAtual::time, dataFinal::time)) THEN
		horarioVago := concat(dataAtual::date, ' ', dataAtual::time);
		RETURN horarioVago;
	END IF;
	
	-- Percorrer registros de inicio, termino de vagas de horário
	FOR linhaAtual IN SELECT inicio, termino FROM agendamento WHERE inicio >= dataAtual ORDER BY inicio LOOP
		IF (horarioAtualValido) THEN
			IF (primeiroDaTabela) AND (dataFinal::time <= linhaAtual.inicio::time) THEN
				horarioVago := concat(linhaAtual.inicio::date, ' ', dataAtual::time);
				RETURN horarioVago;
			
			ELSIF (NOT primeiroDaTabela) AND (intervalo <= linhaAtual.inicio) 
			AND (validarHorario(terminoAnterior::time, linhaAtual.inicio::time)) THEN
				horarioVago := concat(linhaAtual.inicio::date, ' ', terminoAnterior::time);
				RETURN horarioVago;
			ELSE
				primeiroDaTabela := FALSE;
				tabelaVazia := FALSE;
				terminoAnterior := linhaAtual.termino;
				intervalo := terminoAnterior + duracaoTime;
			END IF;
		END IF;
	END LOOP;
	
	-- Caso não ache intervalos, retorna após o termino do ultimo registro.
	IF (validarHorario(terminoAnterior::time, (terminoAnterior + duracaoTime)::time)) THEN
		horarioVago := concat(terminoAnterior::date, ' ', terminoAnterior::time);
		RETURN horarioVago;
	END IF;
END;
$$
LANGUAGE PLPGSQL;

