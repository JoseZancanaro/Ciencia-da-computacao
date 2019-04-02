#ifndef INTERPOLACAOPOLINOMIAL_HPP
#define INTERPOLACAOPOLINOMIAL_HPP

#include "../AlgoritmoNumerico.hpp"

double resolverPolinomioInterpolado(double x, Solucao solucao)
{
    double acumulador = 0.0;
    for (natural i = 0; i < solucao.size(); i++) {
        acumulador += (solucao.at(i) * pow(x, static_cast<double>(i)));
    }
    return acumulador;
}

Solucao resolverPorSistemaLinear(const std::vector<Ponto> &pontos)
{
    // Criar sistema linear (NxN+1)
    Matriz matriz(pontos.size(), Linha(pontos.size() + 1));

    // Adicionar valores na matriz do sistema linear
    for (natural i = 0; i < pontos.size(); i++) {
        // Preencher primeiro valor
        matriz[i].front() = 1;
        // Preencher colunas restantes na linha
        for (natural j = 1; j < pontos.size(); j++)
            matriz[i][j] = pow(pontos[i].x, static_cast<double>(j));
        // Preencher valor da igualdade da linha
        matriz[i].back() = pontos[i].y;
    }

    // Resolver o sistema linear por eliminação de Gauss [com pivoteamento parcial]
    // Polinômio [a0 + a1 * x + a2 * x^n + ... + an * x^n]
    return eliminacaoGaussianaComPivoteamento(matriz);
}

double resolverPorSistemaLinear(double x, const std::vector<Ponto> &pontos)
{
    return resolverPolinomioInterpolado(x, resolverPorSistemaLinear(pontos));
}

double teoremaDeLagrange(double x, const std::vector<Ponto> &pontos)
{
    double acumulador = 0;

    // Iterar soma de produto [f0 * l0 + f1 * l1 + ... + fn * ln]
    // lk(x) = { [(x - x0) * ... * (x - xn) / [(xk - x0) * ... * (xk - xn)] }
    // A razão de lk omite o termo de xk, isto é, não há (x - xk) / (xk - xk)
    for (natural k = 0; k < pontos.size(); k++) {
        // Numerador e denominador da razão
        double numerador = 1, denominador = 1;
        // Multiplicar numerador e denominador omitindo xk
        for (natural i = 0; i < pontos.size(); i++) {
            if (k != i) {
                numerador *= (x - pontos[i].x);
                denominador *= (pontos[k].x - pontos[i].x);
            }
        }
        // Acumulador += fk(x) * lk(x)
        acumulador += pontos[k].y * (numerador / denominador);
    }

    return acumulador;
}

struct EsquemaPraticoLagrange
{
    Matriz esquema;
    double resposta;
    double produtoDiagonal;
    double S;
};

EsquemaPraticoLagrange teoremaDeLagrangePratico(double x, const std::vector<Ponto> &pontos)
{
    // Criar matriz do esquema prático
    Matriz matriz(pontos.size(), Linha(pontos.size() + 2, 0.0));

    // PI e S
    double produtoDiagonal = 1, S = 0.0;

    // Resolver esquema
    for (natural k = 0; k < pontos.size(); k++) {
        double acumulador = 1.0;
        for (natural i = 0; i < pontos.size(); i++) {
            if (k == i) {
                matriz[k][i] = x - pontos[i].x;
                acumulador *= x - pontos[i].x;
                // produtoDiagonal = Produto dos termos na diagonal principal do esquema
                produtoDiagonal *= x - pontos[i].x;
            }
            else {
                matriz[k][i] = pontos[k].x - pontos[i].x;
                acumulador *= pontos[k].x - pontos[i].x;
            }

        }
        matriz[k][pontos.size()] = acumulador;
        // S = Soma de 0 à n (fk(x) / Dk(x)), onde D é o acumulador
        S += (matriz[k].back() = pontos[k].y / acumulador);
    }

    // Não usamos a matriz para nada :-)
    // É possível calcular os resultados utilizando acumuladores ao longo do loop

    return {matriz, produtoDiagonal * S, produtoDiagonal, S};
}

Matriz tabelaDeDiferencasDivididas(const std::vector<Ponto> &pontos)
{
    Matriz diferencas(pontos.size() * 2 - 1, Linha(pontos.size() + 1));

    for (natural i = 0; i < pontos.size() * 2 - 1; i += 2) {
        diferencas[i].front() = pontos[i / 2].x;
        diferencas[i][1] = pontos[i / 2].y;
    }

    for (natural j = 2; j < diferencas.front().size(); j++) {
        for (natural i = j - 1; i < diferencas.size() - j + 1 ; i += 2) {
            diferencas[i][j] = (diferencas[i + 1][j - 1] - diferencas[i - 1][j - 1]) / (diferencas[i + j - 1].front() - diferencas[i - j + 1].front());
        }
    }

    return diferencas;
}

double esquemaPraticoNewton(double x, const Matriz &diferencas)
{
    double acumulador = diferencas[diferencas.size() / 2].back();
    natural coeficiente = diferencas.size() - 1;
    for (natural j = diferencas.front().size() - 1; j > 1; j--) {
        acumulador *= x - diferencas[coeficiente -= 2].front();
        acumulador += diferencas[j - 2][j - 1];
    }
    return acumulador;
}

#endif // INTERPOLACAOPOLINOMIAL_HPP
