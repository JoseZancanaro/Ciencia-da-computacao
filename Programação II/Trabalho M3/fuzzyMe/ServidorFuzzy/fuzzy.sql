CREATE DATABASE IF NOT EXISTS fuzzy;

use fuzzy;

CREATE TABLE IF NOT EXISTS `usuarios`
(
    `id` INT(11) NOT NULL AUTO_INCREMENT,
    `nome` varchar(64) NOT NULL ,
    `senha` varchar(512) NOT NULL,
    `foto` MEDIUMBLOB NOT NULL,
    PRIMARY KEY (`id`)
) ENGINE = InnoDB DEFAULT CHARSET=latin1 ;

CREATE TABLE IF NOT EXISTS `posts`
(
    `id` INT(11) NOT NULL AUTO_INCREMENT,
    `id_autor` varchar(64) NOT NULL ,
    `texto` varchar(256) NOT NULL ,
    `imagem` LONGBLOB NOT NULL ,
    `data` DATETIME NOT NULL ,
    PRIMARY KEY (`id`)
) ENGINE = InnoDB DEFAULT CHARSET=latin1 ;
