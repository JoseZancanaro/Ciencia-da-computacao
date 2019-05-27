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
	tempo_reportado numerIC NULL,
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
SELECT count(id) AS qtd_projeto
FROM projeto;

-- 2
SELECT count(id) AS projeto_concluido
FROM projeto
WHERE concluido = true;

-- 3
SELECT count(id) AS qtd_tarefa_finalizada, sum(tempo_reportado) AS tempo_total
FROM tarefa
WHERE concluida = true;

-- 4
SELECT descricao AS nome_tarefa, tempo_estimado - tempo_reportado AS diferenca_tempo
FROM tarefa
WHERE concluida = true;

-- 5
SELECT max(tempo_reportado) AS tarefa_realizada_mais_demorada
FROM tarefa
WHERE concluida = true;

-- 6
SELECT avg(tempo_estimado) AS media_tempo_estimado
FROM tarefa;

-- 7
SELECT projeto.nome AS nome_projeto, tarefa.descricao as tarefa_relacionada
FROM projeto
INNER JOIN tarefa ON (projeto.id = tarefa.projeto_id);

-- 8
SELECT 	projeto.nome AS nome_projeto, tarefa.descricao AS descricao_tarefa,
		colaborador.nome AS colaborador_responsavel
FROM projeto
INNER JOIN tarefa ON (projeto.id = tarefa.projeto_id)
INNER JOIN colaborador ON (tarefa.colaborador_id = colaborador.id);

-- 9
SELECT 	projeto.nome AS nome_projeto, tarefa.descricao AS descricao_tarefa,
	   	colaborador.nome AS colaborador_responsavel, cargo.nome AS cargo_coloborador
FROM projeto
INNER JOIN tarefa ON (projeto.id = tarefa.projeto_id)
INNER JOIN colaborador ON (tarefa.colaborador_id = colaborador.id)
INNER JOIN cargo ON (colaborador.cargo_id = cargo.id);

-- 10
SELECT 	projeto.nome AS nome_projeto, tarefa.descricao AS descricao_tarefa,
	   	tarefa.tempo_reportado * cargo.salario_por_hora AS custo_real
FROM projeto
INNER JOIN tarefa ON (projeto.id = tarefa.projeto_id)
INNER JOIN colaborador ON (tarefa.colaborador_id = colaborador.id)
INNER JOIN cargo ON (colaborador.cargo_id = cargo.id)
WHERE tarefa.concluida = true;

-- 11
SELECT 	projeto.nome AS nome_projeto, tarefa.descricao AS descricao_tarefa,
	   	tarefa.tempo_estimado * cargo.salario_por_hora AS custo_estimado,
 	   	tarefa.tempo_reportado * cargo.salario_por_hora AS custo_real
FROM projeto
INNER JOIN tarefa ON (projeto.id = tarefa.projeto_id)
INNER JOIN colaborador ON (tarefa.colaborador_id = colaborador.id)
INNER JOIN cargo ON (colaborador.cargo_id = cargo.id)
WHERE tarefa.concluida = true;

-- 12
SELECT 	projeto.nome AS nome_projeto, tarefa.descricao AS descricao_tarefa,
	   	tarefa.tempo_reportado * cargo.salario_por_hora AS custo_real,
	   	tarefa.tempo_estimado * cargo.salario_por_hora AS custo_estimado,
	   	(tarefa.tempo_estimado - tarefa.tempo_reportado) * cargo.salario_por_hora AS diferenca_custos
FROM projeto
INNER JOIN tarefa ON (projeto.id = tarefa.projeto_id)
INNER JOIN colaborador ON (tarefa.colaborador_id = colaborador.id)
INNER JOIN cargo ON (colaborador.cargo_id = cargo.id)
WHERE tarefa.concluida = true;

-- 13
SELECT projeto.nome AS nome_projeto, count(tarefa.projeto_id) AS qtd_tarefas_por_projetos
FROM projeto
LEFT OUTER JOIN tarefa ON (projeto.id = tarefa.projeto_id)
GROUP BY projeto.nome;

-- 14
SELECT cargo.nome AS nome_cargo, count(colaborador.cargo_id) AS qtd_colaborador_por_cargo
FROM cargo
RIGHT OUTER JOIN colaborador ON (cargo.id = colaborador.cargo_id)
GROUP BY cargo.nome;

-- 15 
SELECT projeto.nome AS nome_projeto, sum(tarefa.tempo_reportado) AS tempo_gasto_pro_projeto
FROM projeto
LEFT JOIN tarefa ON (projeto.id = tarefa.projeto_id)
GROUP BY projeto.nome;

-- 16
SELECT colaborador.nome AS nome_colaborador, count(tarefa.concluida) AS qtd_tarefas_concluidas
FROM colaborador
LEFT OUTER JOIN tarefa ON (colaborador.id = tarefa.colaborador_id)
WHERE tarefa.concluida = true
GROUP BY colaborador.nome
ORDER BY colaborador.nome;

-- 17
SELECT colaborador.nome AS nome_colaborador, count(tarefa.concluida) AS qtd_tarefas_necessarias
FROM colaborador
LEFT outer JOIN tarefa ON (colaborador.id = tarefa.colaborador_id)
WHERE tarefa.concluida = false
GROUP BY colaborador.nome
ORDER BY colaborador.nome;

-- 18
SELECT colaborador.nome AS nome_colaborador, sum(tarefa.tempo_reportado) AS tempo_trabalhado
FROM colaborador
INNER JOIN tarefa ON (colaborador.id = tarefa.colaborador_id)
GROUP BY colaborador.nome
ORDER BY colaborador.nome;

-- 19
SELECT projeto.nome AS nome_projeto, sum(tarefa.tempo_estimado) AS tempo_estimado_de_conclusao
FROM projeto
LEFT OUTER JOIN tarefa ON (projeto.id = tarefa.projeto_id)
GROUP BY projeto.nome;

-- 20
SELECT 	projeto.nome AS nome_projeto,
       	sum(tarefa.tempo_estimado * cargo.salario_por_hora) AS custo_estimado_por_projeto
FROM projeto
LEFT OUTER JOIN tarefa ON (projeto.id = tarefa.projeto_id)
LEFT OUTER JOIN colaborador ON (tarefa.colaborador_id = colaborador.id)
LEFT OUTER JOIN cargo ON (colaborador.cargo_id = cargo.id)
GROUP BY projeto.nome;
