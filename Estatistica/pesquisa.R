## Necessário ter o pacote readxl instalado e carregado
db <- read_xlsx(path  = "EMCT-Pesquisa EC.xlsx", sheet = "Filtro") 

## Observando um resumo dos dados...
summary(db)
 
## Criando um glossário para as perguntas...
glos <- data.frame(Perguntas = names(db), Sinonimo = LETTERS[1:12])

## Renomeando a base de dados original...
names(db) <- LETTERS[1:12]

## Resumindo o número de indivíduos por sexo
tab01 <- db %>%
  group_by(E) %>%
  summarise(n = n())
tab01

## Calculando a proporção
tab01$prop <- tab01$n/100

## Valor esperado na população
tab01$N <- tab01$prop * 541
tab01

## Gráfico de barra - proporção do sexo
p00 <- ggplot() +
    geom_bar(data = tab01, aes(x = E, y = N, fill = E), width = 0.9, stat = "identity") +
    geom_label(data = tab01, aes(x = E, y = N, label = round(N))) + 
    labs(x = "Sexo", y = "Número de alunos") + 
    scale_fill_manual(values = c("red", "blue"))
p00

## Gráfico de pizza - proporção do sexo
p01 <- ggplot() +
  geom_bar(data = tab01, aes(x = "", y = N, fill = E), width = 1, stat = "identity") +
  coord_polar("y", start = 0) 
p01

## Resumindo o número de indivíduos fumantes por sexo
tab02 <- db %>%
  group_by(E, G) %>%
  summarise(n = n()) %>%
  mutate(N = (n/100) * 541) 
tab02

## Gráfico de barra - fumantes por sexo
p02 <- ggplot() +
  geom_bar(data = tab02, aes(x = E, y = N, fill = E), width = 0.9, stat = "identity") +
  facet_wrap(~G) +
  geom_label(data = tab02, aes(x = E, y = N, label = round(N))) + 
  labs(x = "Fuma?", y = "Número de alunos")
p02

## Ingerir bebida x fuma
tab03 <- db %>%
  group_by(G, H) %>%
  summarise(n = n()) %>%
  mutate(N = round((n/100) * 541))
tab03

## Gŕafico de barra - bebida x fuma
p03 <- ggplot() +
  geom_bar(data = tab03, aes(x = G, y = N, fill = N), width = 0.9, stat = "identity") +
  facet_wrap(~H) +
  geom_label(data = tab03, aes(x = G, y = N, label = round(N))) +
  labs(x = "Fuma?", y = "Número de aluno")
p03