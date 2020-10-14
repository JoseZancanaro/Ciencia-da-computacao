## Carregando a base de dados co2.csv (disponível no meu one drive) 
db <- read.table(file = "co2.csv", header = TRUE, sep = ";", dec = ",")

## Instalando os pacotes
install.packages(c("ggplot2", "dplyr"), dependencies = TRUE) 

## Carregando os pacotes
library(ggplot2)
library(dplyr)

## Calculando a média de co2 para diferentes épocas
tab01 <- db %>%
  group_by(DECADA) %>%
  summarise(media = mean(CO2), desvio = sd(CO2), n = n()) %>%
  mutate(erro.padrao = desvio / sqrt(n))
tab01

## Definindo alpha
alpha <- 0.05

## Quantidade de probabilidade da tabela t
tab01$t <- qt(p = 1 - alpha / 2, df = tab01$n - 1)
tab01

## Margem de erro...
tab01$ME <- tab01$t * tab01$erro.padrao
tab01

## Gráfico...
p00 <- ggplot() + 
  geom_errorbar(data = tab01, 
                aes(x = DECADA, ymin = media - ME, ymax = media + ME)) +
  geom_point(data = tab01, 
             aes(x = DECADA, y = media),
             pch = 21, fill = "white", size = 4)
p00