## Carregando a base de dados crabs.csv (disponível no meu one drive)
db <- read.table("crabs.csv", header = TRUE, sep = ";", dec = ",")

head(db)

# Comparando os dados de CW
aggregate(CW ~ especie, data = db, mean)
aggregate(CW ~ especie, data = db, sd)

# Teste de hipótese para comparar a média da população Laranja 
# contra a população Azul
t.test(CW ~ especie, data = db, conf.level = 0.95, alternative = "two.sided")

# Comparando os dados de CL
aggregate(CL ~ especie, data = db, mean)
aggregate(CL ~ especie, data = db, sd)
t.test(CL ~ especie, data = db, conf.level = 0.95, alternative = "two.sided")

# Comparando os dados de RW
aggregate(RW ~ especie, data = db, mean)
aggregate(RW ~ especie, data = db, sd)
t.test(RW ~ especie, data = db, conf.level = 0.95, alternative = "two.sided")

# Comparando os dados de FL
aggregate(FL ~ especie, data = db, mean)
aggregate(FL ~ especie, data = db, sd)
t.test(FL ~ especie, data = db, conf.level = 0.95, alternative = "two.sided")

# Comparando os dados de BD
aggregate(BD ~ especie, data = db, mean)
aggregate(BD ~ especie, data = db, sd)
t.test(BD ~ especie, data = db, conf.level = 0.95, alternative = "two.sided")