## Questão 01
n <-6
p <- 1/4
x = 0:6

prob01 <- dbinom(x = x, size = n, prob = p)
sum(prob01[c(4, 5, 6, 7)]) 

# Ou
1 - pbinom(q = 2, size = n, prob = p)

## Questão 02
n <- 5
p <- 0.3
x <- 0:5

prob02 <- dbinom(x = x, size = n, prob = p)
sum(prob02[c(5,6)])

## Questão 03
n <- 10
p <- 3/20 * 2/3
x <- 0:10

1 - pbinom(q = 1 , size = n, prob = p)

## Questão 04
media <- 10
sigma <- 3.3

# a
1 - pnorm(q = 12, mean = media, sd = sigma)

# b
pnorm(q = 10, mean = media, sd = sigma)

# c
pnorm(q = 13, mean = media, sd = sigma) - pnorm(q = 11, mean = media, sd = sigma)

# d
pnorm(q = 14, mean = media, sd = sigma) - pnorm(q = 8, mean = media, sd =sigma)

# e
1 - pnorm(q = 20, mean = media, sd = sigma)

## Questão 05
n <- 50
p <- 0.8 * 0.4 * 0.5
x <- 0:50

prob05 <- dbinom(x = x, size = n, prob = p)
sum(prob05[31:51]) 

# ou
1 - pbinom(q = 29, size = n, prob = p)

## Questão 06
media <- 20
sigma <- 2.5

1 - pnorm(q = 27, mean = media, sd = sigma)

## Questão 07
p <- 0.03
media <-  4.5
sigma <- 1.25

qnorm(p = 1 - p, mean = media, sd = sigma)

## Questão 08
media <- 3.10
sigma <- 150 / 100  # em metros

1 - pnorm(q = 5, mean = media, sd = sigma)
