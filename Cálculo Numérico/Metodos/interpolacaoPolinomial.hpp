#ifndef INTERPOLACAOPOLINOMIAL_HPP
#define INTERPOLACAOPOLINOMIAL_HPP

#include "algoritmoNumerico.hpp"

// Fórmula de Lagrange:
double formulaDeLagrange(double x, const std::vector<Ponto> &pontos)
{
    double acumulador = 0.0;

    /* lk(x) = (x - x0)...(x - xk-1)(x - xk+1)...(x - xn)
            -----------------------------------------------
           (xk - x0)...(xk - xk-1)(xk - xk+1)...(xk - xn)
     */

    for(size_t k = 0; k < pontos.size(); k++){
        double numerador = 1.0, denominador = 1.0;
        for(size_t i = 0; i < pontos.size(); i++){
            if(k != i){
                numerador *= x - pontos[i].x;
                denominador *= pontos[k].x - pontos[i].x;
            }
        }
        /* lk(x) = numerador / denominador,
         * acumulador = p(x)
         * p(x) = fk(x) * lk(x) + ...fn(x) * ln(x).
         */
        acumulador += pontos[k].y * (numerador / denominador);
    }
    return acumulador;
}

// Esquema prático de Lagrange:
double esquemaPraticoDeLagrange(double x, const std::vector<Ponto> &pontos)
{
    double S = 0.0;
    double diagonalPrincipal = 1.0;

    for(size_t k = 0; k < pontos.size(); k++){
        double DK = 1.0;
        for(size_t i = 0; i < pontos.size(); i++){
            if(k == i){
                diagonalPrincipal *= x - pontos[i].x;
                DK *= x - pontos[i].x;
            }
            else{
                DK *= pontos[k].x - pontos[i].x;
            }
        }
        S += pontos[k].y / DK;
    }
    return diagonalPrincipal * S;
}

// Obter o polinomio a partir de pontos e resolver com gauss pivoteamento parcial:
std::vector<double> obterPolinomioInterpolador(const std::vector<Ponto> &pontos)
{
    std::vector<std::vector<double>> matriz (pontos.size(), std::vector<double>(pontos.size() + 1));

    for(size_t k = 0; k < pontos.size(); k++){
        for(size_t i = 0; i < pontos.size(); i++){
            matriz[k][i] = pow(pontos[k].x, i);
        }
        matriz[k].back() = pontos[k].y;
    }

    return eliminacaoDeGaussPivoteamentoParcial(matriz);
}

// Resolver o polinomio
double resolverPolinomio(double x, const std::vector<double> &vetor)
{
    double acumulador = 0.0;
    for(size_t i = 0; i < vetor.size(); i++){
        acumulador += vetor[i] * pow(x, i);
    }

    return acumulador;
}

// Sobrecarga da função resolverPolinomio
double resolverPolinomio(double x, const std::vector<Ponto> &pontos)
{
    return resolverPolinomio(x, obterPolinomioInterpolador(pontos));
}

// Construir tabela para métodos de Newton:
std::vector<std::vector<double>> tabelaDiferencasDivididas(const std::vector<Ponto> &pontos)
{
    std::vector<std::vector<double>> matriz(2 * pontos.size() -1, std::vector<double>(pontos.size() + 1));

    for(size_t i = 0; i < matriz.size(); i += 2){
        matriz[i][0] = pontos[i/ 2].x;
        matriz[i][1] = pontos[i/ 2].y;
    }

    for(size_t coluna = 2; coluna < matriz[0].size(); coluna++){
        for(size_t linha = coluna - 1; linha <= matriz.size() - coluna; linha += 2){
             matriz[linha][coluna] = (matriz[linha + 1][coluna - 1] - matriz[linha - 1][coluna - 1]) /
                                     (matriz[linha + coluna - 1][0] - matriz[linha - coluna + 1][0]);
        }
    }

    return matriz;
}

// Fórmula de Newton:
double formulaDeNewton(double x, const std::vector<std::vector<double>> &matriz)
{
    double resposta = matriz[0][1];
    for(size_t i = 2; i < matriz[0].size(); i++){
        double acumulador = 1.0;
        for(size_t j = 0; j < i - 1; j++){
            acumulador *= x - matriz[2 * j][0];
        }
        resposta += acumulador * matriz[i - 1][i];
    }

    return resposta;
}

// Esquema Prático de Newton:
double esquemaPraticoDeNewton(double x, const std::vector<std::vector<double>> &matriz)
{
    double resposta = matriz[matriz.size() / 2][matriz[0].size() - 1] /* matriz[linha].back() */;
    size_t coeficiente = matriz.size() - 3;

    for(size_t i = matriz[0].size() - 2; i > 0; i--){
        resposta = resposta * (x - matriz[coeficiente][0]) + matriz[i - 1][i];
        coeficiente -= 2;
    }

    return resposta;
}

#endif // INTERPOLACAOPOLINOMIAL_HPP
