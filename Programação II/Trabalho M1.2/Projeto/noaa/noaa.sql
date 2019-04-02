CREATE DATABASE IF NOT EXISTS noaa;

use noaa;

CREATE TABLE IF NOT EXISTS `ondografos`
(
    `id` INT(11) NOT NULL AUTO_INCREMENT,
    `nome` varchar(64) NOT NULL ,
    `latitude` DOUBLE NOT NULL ,
    `longitude` DOUBLE NOT NULL ,
    `bateria` DOUBLE NOT NULL ,
    `data_lancamento` DATETIME NOT NULL ,
    PRIMARY KEY (`id`)
) ENGINE = InnoDB DEFAULT CHARSET=latin1 ;

CREATE TABLE IF NOT EXISTS `satelites`
(
    `id` INT(11) NOT NULL AUTO_INCREMENT,
    `nome` varchar(64) NOT NULL ,
    `latitude` DOUBLE NOT NULL ,
    `longitude` DOUBLE NOT NULL ,
    `angulo` DOUBLE NOT NULL,
    `bateria` DOUBLE NOT NULL,
    `data_lancamento` DATETIME NOT NULL ,
    PRIMARY KEY (`id`)
) ENGINE = InnoDB DEFAULT CHARSET=latin1 ;

CREATE TABLE IF NOT EXISTS `registrosMeteoceanograficos`
(
    `id` INT(11) NOT NULL AUTO_INCREMENT,
    `id_ondografo` INT(11) NOT NULL ,
    `temperatura` DOUBLE NOT NULL ,
    `umidade` DOUBLE NOT NULL ,
    `pressao` DOUBLE NOT NULL ,
    `altura` DOUBLE NOT NULL ,
    `corrente` DOUBLE NOT NULL ,
    `direcao_corrente` DOUBLE NOT NULL ,
    `vento` DOUBLE NOT NULL ,
    `direcao_vento` DOUBLE NOT NULL ,
    `bateria` DOUBLE NOT NULL ,
    `data` DATETIME NOT NULL ,
    PRIMARY KEY (`id`)
) ENGINE = InnoDB DEFAULT CHARSET=latin1 ;

CREATE TABLE IF NOT EXISTS `registrosAtmosfericos`
(
    `id` INT(11) NOT NULL AUTO_INCREMENT,
    `id_satelite` INT(11) NOT NULL ,
    `temperatura` DOUBLE NOT NULL ,
    `pressao` DOUBLE NOT NULL ,
    `densidade` DOUBLE NOT NULL ,
    `vento` DOUBLE NOT NULL ,
    `direcao_vento` DOUBLE NOT NULL ,
    `bateria` DOUBLE NOT NULL ,
    `data` DATETIME NOT NULL ,
    PRIMARY KEY (`id`)
) ENGINE = InnoDB DEFAULT CHARSET=latin1 ;

CREATE TABLE IF NOT EXISTS `eventosClimaticos`
(
    `id` INT(11) NOT NULL AUTO_INCREMENT,
    `tipo` VARCHAR(64) NOT NULL ,
    `latitude` DOUBLE NOT NULL ,
    `longitude` DOUBLE NOT NULL ,
    `descricao` VARCHAR(256) NOT NULL ,
    `data_inicio` DATETIME NOT NULL ,
    `data_fim` DATETIME ,
    `situacao` VARCHAR(32) NOT NULL ,
    `categoria` VARCHAR(32) NOT NULL ,
    PRIMARY KEY (`id`)
) ENGINE = InnoDB DEFAULT CHARSET=latin1 ;
