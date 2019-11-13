-- Criar tabelas: 
CREATE TABLE cargo (
	id int NOT NULL,
	nome varchar(50) NOT NULL,
	salario_por_hora numeric NOT NULL,
	PRIMARY KEY (id)
);

CREATE TABLE colaborador (
	id int NOT NULL,
	nome varchar(255) NOT NULL,
	data_nascimento date NOT NULL,
	cargo_id int NOT NULL,
	PRIMARY KEY (id)
);

CREATE TABLE projeto (
	id int NOT NULL,
	nome varchar(255) NOT NULL,
	concluido boolean NOT NULL,
	PRIMARY KEY (id)
);

CREATE TABLE tarefa (
	id int NOT NULL,
	descricao text NOT NULL,
	tempo_estimado numeric NOT NULL,
	tempo_reportado numeric NULL,
	concluida boolean NOT NULL,
	projeto_id int NOT NULL,
	colaborador_id int NOT NULL,
	PRIMARY KEY (id)
);

-- Relacionar tabelas:
ALTER TABLE colaborador ADD FOREIGN KEY (cargo_id)
REFERENCES cargo (id);

ALTER TABLE tarefa ADD FOREIGN KEY (projeto_id)
REFERENCES projeto (id);

ALTER TABLE tarefa ADD FOREIGN KEY (colaborador_id)
REFERENCES colaborador (id);

-- Popular tabelas:
INSERT INTO cargo (id, nome, salario_por_hora)
VALUES	(1, 'cargo01', 10),
	(2, 'cargo02', 11),
	(3, 'cargo03', 12);

INSERT INTO colaborador (id, nome, data_nascimento, cargo_id)
VALUES	(1, 'colaborador01', '2000-01-01', 1),
	(2, 'colaborador02', '2000-02-02', 1),
	(3, 'colaborador03', '2000-03-03', 2),
	(4, 'colaborador04', '2000-04-04', 2),
	(5, 'colaborador05', '2000-05-05', 3),
	(6, 'colaborador06', '2000-06-06', 3);

INSERT INTO projeto (id, nome, concluido)
VALUES	(1, 'projeto01', false),
	(2, 'projeto02', false),
	(3, 'projeto03', false);

INSERT INTO tarefa (id, descricao, tempo_estimado, tempo_reportado, concluida, projeto_id, colaborador_id)
VALUES	(1, 'tarefa01', 15, 16, false, 1, 1),
	(2, 'tarefa02', 16, 17, false, 1, 2),
	(3, 'tarefa03', 17, 18, false, 2, 3),
	(4, 'tarefa04', 18, 19, false, 2, 4),
	(5, 'tarefa05', 19, 20, false, 3, 5),
	(6, 'tarefa06', 20, 21, false, 3, 6);

-- Respostas:
-- 1 
SELECT nome FROM projeto WHERE nome like 'a%';

-- 2
SELECT nome FROM projeto WHERE nome like '%a';

-- 3
SELECT nome FROM projeto WHERE nome like '%a%';

-- 4
SELECT nome FROM projeto WHERE nome like '__a';

-- 5
SELECT ceil(count(id) / 5.0) AS paginas_necessarias FROM tarefa;

-- 6
SELECT descricao FROM tarefa ORDER BY descricao LIMIT 5;

-- 7
SELECT descricao FROM tarefa ORDER BY descricao LIMIT 5 OFFSET 5;

-- 8
SELECT 
  projeto.nome, tarefa.descricao,
  CASE
  	WHEN tarefa.tempo_reportado IS null THEN 'Não iniciada'
  	WHEN NOT tarefa.tempo_reportado IS null AND tarefa.concluida = false THEN 'Em desenvolvimento'
  	ELSE 'Concluída'
  END
FROM 
	projeto
	INNER JOIN tarefa ON (projeto.id = tarefa.projeto_id)

-- 9
SELECT 
  nome,
  CASE 
	WHEN extract(month FROM data_nascimento) = 1 THEN 'Janeiro'
	WHEN extract(month FROM data_nascimento) = 2 THEN 'Fevereiro'
	WHEN extract(month FROM data_nascimento) = 3 THEN 'Março'
	WHEN extract(month FROM data_nascimento) = 4 THEN 'Abril'
	WHEN extract(month FROM data_nascimento) = 5 THEN 'Maio'
	WHEN extract(month FROM data_nascimento) = 6 THEN 'Junho'
	WHEN extract(month FROM data_nascimento) = 7 THEN 'Julho'
	WHEN extract(month FROM data_nascimento) = 8 THEN 'Agosto'
	WHEN extract(month FROM data_nascimento) = 9 THEN 'Setembro'
	WHEN extract(month FROM data_nascimento) = 10 THEN 'Outubro'
	WHEN extract(month FROM data_nascimento) = 11 THEN 'Novembro'
	WHEN extract(month FROM data_nascimento) = 12 THEN 'Dezembro'
  END
FROM colaborador;

-- 10
-- Enunciado igual ao numero 08.	
