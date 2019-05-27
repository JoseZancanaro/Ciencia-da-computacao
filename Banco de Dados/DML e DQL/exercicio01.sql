-- 1
CREATE TABLE categoria (
	id integer NOT NULL,
	descricao varchar(255) NULL,
	PRIMARY KEY (id)
);

CREATE TABLE marca (
	id integer NOT NULL,
	nome varchar(255) NULL,
	PRIMARY KEY (id)
);

CREATE TABLE unidade (
 	id integer NOT NULL,
	descricao varchar(255) NULL,
	PRIMARY KEY (id)
);

CREATE TABLE produto (
	id integer NOT NULL,
	descricao varchar(255) NULL,
	preco_custo decimal(10,2) NULL,
	preco_venda decimal(10,2) NULL,
	qtd_estoque integer NULL,
	qtd_estoque_minimo integer NULL,
	id_categoria integer NULL,
	id_marca integer NULL,
	id_unidade integer NULL,
	PRIMARY KEY (id)
);

ALTER TABLE produto ADD FOREIGN KEY (id_categoria) REFERENCES categoria (id);
ALTER TABLE produto ADD FOREIGN KEY (id_marca) REFERENCES marca (id);
ALTER TABLE produto ADD FOREIGN KEY (id_unidade) REFERENCES unidade (id);


-- 2
INSERT INTO marca (id, nome) VALUES (1, 'Nike'), (2, 'Adidas'), 
(3, 'Reebok'), (4, 'Wilson'), (5, 'Speedy'), (6, 'Butterfly');

-- 3
INSERT INTO categoria (id, descricao) VALUES (1, 'Confecção'), (2, 'Calçados'),
(3, 'Bolas'), (4, 'Natação'), (5, 'Tênis'), (6, 'Tênis de Mesa');

-- 4
INSERT INTO unidade (id, descricao) VALUES (1, 'Peça'), (2, 'Par'),
(3, 'Gramas'), (4, 'Litro'), (5, 'Caixa'), (6, 'Cartela');

-- 5
INSERT INTO produto (id, descricao, preco_custo, preco_venda, qtd_estoque, qtd_estoque_minimo, id_categoria, id_marca, id_unidade) 
VALUES 	(1, 'Camisa Brasil 1', 100.00, 160.00, 18, 6, 1, 1, 1),
	(2, 'Bola Adidas Copa 2010', 150.00, 240.00, 2, 3, 3 ,2 ,1),
	(3, 'Camisa França 2', 110.00, 170.00, 1, 2, 1, 2, 1),
	(4, 'Bola de Tênis de Mesa Profissional c/ 6', 20.00, 32.00, 12, 6, 6, 6, 6),
	(5, 'Bola de Tênis c/ 3', 11.00, 18.00, 4, 6, 5, 4, 5),
	(6, 'Raquete Tênis Profissional', 280.00, 460.00, 2, 2, 5, 4, 1),
	(7, 'Camisa Esportiva', 20.00, 32.00, 12, 3, 1, 3, 1),
	(8, 'Chuteira de Campo de Couro', 90.00, 170.00, 8, 6, 2, 1, 2),
	(9, 'Chuteira de Futsal de Sintético', 40.00, 65.00, 12, 6, 2, 3, 2),
	(10, 'Óculos de Natação Expert', 35.00, 60.00, 3, 6, 4, 5, 1),
	(11, 'Maio de Natação Sublime', 70.00, 125.00, 3, 3, 4, 5, 1);

-- 6 
UPDATE unidade SET descricao = 'Kilos' WHERE id = 3;

-- 7
UPDATE marca SET nome = 'Speed' WHERE id = 5;

-- 8
UPDATE produto SET descricao = 'Camisa Lazer de Poliéster' WHERE id = 7;

-- 9
UPDATE produto SET preco_venda = 155.00 WHERE id = 8;

-- 10
UPDATE produto SET qtd_estoque = 6 	WHERE id = 9; 

-- 11
UPDATE produto SET preco_venda = preco_venda * 1.1 WHERE id % 2 = 1; 

-- 12
UPDATE produto SET descricao = 'Maio de Natação Sublime Especial', 
preco_custo = 64.00, preco_venda = 115.00, qtd_estoque = 9, qtd_estoque_minimo = 6 
WHERE id = 11;

-- 13
DELETE FROM unidade WHERE id = 4;

-- 14
DELETE FROM produto WHERE id = 7;

-- 15
SELECT * FROM marca;

-- 16
SELECT * FROM categoria ORDER BY descricao;

-- 17
SELECT * FROM unidade ORDER BY id desc;

-- 18
SELECT descricao, preco_venda FROM produto ORDER BY preco_venda;

-- 19
SELECT descricao, preco_custo, preco_venda FROM produto ORDER BY preco_custo desc;

-- 20
SELECT descricao, preco_custo, preco_venda, qtd_estoque, qtd_estoque_minimo 
FROM produto ORDER BY descricao desc;

-- 21
SELECT * FROM produto WHERE preco_venda > 100.00;

-- 22
SELECT * FROM produto 
WHERE preco_venda >= 100.00 AND preco_venda <= 200.00 
ORDER BY descricao, preco_custo; 

-- 23
SELECT descricao, qtd_estoque FROM produto 
WHERE qtd_estoque >= 8 AND qtd_estoque <= 20
ORDER BY descricao;

-- 24
SELECT * FROM produto WHERE qtd_estoque < qtd_estoque_minimo;

-- 25
SELECT descricao, (qtd_estoque_minimo / 2) + qtd_estoque_minimo - qtd_estoque 
AS necessario_comprar FROM produto where qtd_estoque <= qtd_estoque_minimo;

-- 26
SELECT descricao, preco_venda * qtd_estoque 
AS valor_arrecadado FROM produto; 

-- 27
SELECT descricao, (preco_venda * qtd_estoque) - (preco_custo * qtd_estoque) 
AS valor_lucrado FROM produto;

-- 28
SELECT descricao, (((preco_venda * qtd_estoque) - (preco_custo * qtd_estoque)) / preco_custo) * 100 
AS percentual_lucro FROM produto;

-- 29
SELECT descricao, ((preco_venda * qtd_estoque) - (preco_custo * qtd_estoque)) * 0.35 
AS valor_do_imposto FROM produto;

