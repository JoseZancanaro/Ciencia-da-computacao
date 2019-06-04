-- 1
-- A
duracao_hora decimal(10,2) NOT NULL CHECK (duracao_hora >= 1 AND duracao_hora <= 60);

-- B
salario_hora decimal (10,2) NOT NULL CHECK (salario_hora >= 10);

-- C
ano_contratacao int NOT NULL CHECK (ano_contratacao > 2000);

-- 2
INSERT INTO projeto (id, nome, data_inicio, id_colaborador_gerente) 
VALUES 	(1, 'Desenvolvimento do Site Coca-Cola', '13/11/2018', NULL),
	    (2, 'Desenvolvimento Sistema UNIVALI', '01/10/2018', NULL),
	    (3, 'Análise do Sistema Rede Globo', '23/05/2019', NULL),
	    (4, 'Desenvolvimento do Sistema Block Buster', '20/03/2019', NULL);

-- 3
INSERT INTO cargo (id, nome, salario_hora) 
VALUES 	(1, 'Programador Júnior', 18.00),
	    (2, 'Programador Pleno', 30.00),
	    (3, 'Programador Senior', 42.00),
	    (4, 'Analista de Sistemas Pleno', 32.00),
	    (5, 'Analista de Sistemas Senior', 44.00),
	    (6, 'Administrador de DB Pleno', 31.00),
	    (7, 'Administrador de DB Senior', 43.00);

-- 4
INSERT INTO colaborador (id, id_cargo, nome, ano_contratacao) 
VALUES 	(1, 2, 'João', 2017),
		(2, 1, 'Pedro', 2015),
		(3, 3, 'Ana', 2014),
		(4, 1, 'Fernando', 2010),
		(5, 2, 'Juliana', 2015),
		(6, 5, 'Sérgio', 2014),
		(7, 6, 'Alan', 2011),
		(8, 3, 'Bruna', 2009);

-- 5
INSERT INTO tarefa (id, id_colaborador_responsavel, id_projeto, descricao, duracao_hora, concluida) 
VALUES 	(1, 6, 1, 'Modelagem do sistema', 35, true),
    	(2, 2, 1, 'Criação interfaces', 20, false),
        (3, 1, 1, 'Módulo administrativo', 40, false),
        (4, 7, 2, 'Criação do Banco de Dados', 30, true),
        (5, 3, 2, 'Módulo administrativo', 60, true),
        (6, 4, 2, 'Criação interfaces', 40, true),
        (7, 6, 2, 'Treinamento dos usuários', 20, false),
        (8, 4, 3, 'Modelagem do sistema', 40, true),
        (9, 4, 3, 'Módulo administrativo', 30, true),
        (10, 4, 3, 'Criação interfaces', 40, false),
        (11, 7, 3, 'Criação das views', 16, true),
        (12, 4, 3, 'Publicação do sistema', 8, false);

-- 6
UPDATE projeto SET id_colaborador_gerente = 3 WHERE id = 1;
UPDATE projeto SET id_colaborador_gerente = 6 WHERE id in (2,3);
UPDATE projeto SET id_colaborador_gerente = 8 WHERE id = 4;

-- 7
UPDATE cargo SET salario_hora = salario_hora * 1.1 WHERE id in (1, 2, 3);

-- 8 
SELECT nome AS nome_colaborador, 2019 - ano_contratacao AS anos_na_empresa FROM colaborador;

-- 9
SELECT descricao AS descricao_tarefa, (duracao_hora * 60) * 1.5 AS tarefa_em_minutos 
FROM tarefa WHERE concluida = false ORDER BY descricao asc;

-- 10
SELECT 	
  colaborador.nome AS nome_colaborador, 
  (cargo.salario_hora * 44) * 4 AS salario_mensal
FROM 
  colaborador
  INNER JOIN cargo ON (colaborador.id_cargo = cargo.id);

-- 11
SELECT
  projeto.nome AS nome_projeto,
  tarefa.descricao AS descricao_tarefa,
  tarefa.duracao_hora AS tempo_necessario_em_horas
FROM	
  projeto
  INNER JOIN tarefa ON (projeto.id = tarefa.id_projeto);

-- 12
SELECT 
  colaborador.nome AS nome_colaborador,
  projeto.nome AS nome_projeto_gerenciado
FROM 
  colaborador
  INNER JOIN projeto ON (colaborador.id = projeto.id_colaborador_gerente);

-- 13
SELECT 
  projeto.nome AS nome_projeto,
  count(tarefa.id) AS qtd_tarefas
FROM 
  projeto
  LEFT OUTER JOIN tarefa ON (projeto.id = tarefa.id_projeto)
GROUP BY projeto.nome;

-- 14
SELECT 
  projeto.nome AS nome_projeto,
  sum(tarefa.duracao_hora) AS tempo_necessario_em_horas
FROM
  projeto
  LEFT JOIN tarefa ON (projeto.id = tarefa.id_projeto)
GROUP BY projeto.nome;

-- 15
SELECT 
  projeto.nome AS nome_projeto,
  sum(tarefa.duracao_hora * cargo.salario_hora) AS custo_projeto
FROM 
  projeto
  INNER JOIN colaborador ON (projeto.id_colaborador_gerente = colaborador.id)
  INNER JOIN cargo ON (colaborador.id_cargo = cargo.id)
  INNER JOIN tarefa ON (projeto.id = tarefa.id_projeto)
GROUP BY projeto.nome;