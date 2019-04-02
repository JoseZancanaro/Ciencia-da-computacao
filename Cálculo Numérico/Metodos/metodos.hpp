#ifndef METODOS_HPP
#define METODOS_HPP

#include "algoritmoNumerico.hpp"

// Método de Bissecção:
double bisseccao(double a, double b, std::function<double(double)> funcao, std::function<double(double, double)> parada, double precisao)
{
    double funcaoA;
    double funcaoXn;
    double xn = 0.0;
    double anterior = 0.0;
    double parar = 1.0;

    std::function<double(double, double) > obterXn = [](double a, double b){
        return ((a + b) / 2);
    };

    for (int i = 0; parar > precisao; i++) {
        xn = obterXn(a, b);
        funcaoA = funcao(a);
        funcaoXn = funcao(xn);
        parar = parada(xn, anterior);
        exibirBisseccao(i, a, b, xn, funcaoA, funcaoXn, parar);
        anterior = xn;

        if (funcaoA * funcaoXn < 0) {
            b = xn;
        }
        else
            a = xn;
    }

    return xn;
}

// Método da Falsa posição:
double falsaPosicao(double a, double b, std::function<double(double)> funcao, std::function<double(double, double)> parada, double precisao)
{
    double funcaoA;
    double funcaoB;
    double funcaoXn;
    double xn = 0.0;
    double anterior = 0.0;
    double parar = 1.0;

    std::function<double(double,double,double,double)> obterXn = [](double a, double funcaoA, double b, double funcaoB){
        return ((a * funcaoB) - (b * funcaoA)) / (funcaoB - funcaoA);
    };

    for (int i = 0; parar > precisao; i++) {
        funcaoA = funcao(a);
        funcaoB = funcao(b);
        xn = obterXn(a, funcaoA, b, funcaoB);
        funcaoXn = funcao(xn);
        parar = parada(xn, anterior);
        anterior = xn;

        exibirFalsaPosicao(i, a, b, xn, funcaoA, funcaoB, funcaoXn, parar);
        if (funcaoA * funcaoXn < 0) {
            b = xn;
        }
        else
            a = xn;
    }

    return xn;
}

// Método de Newton:
double metodoDeNewton(double xn, std::function<double(double)> funcao, std::function<double(double)> derivada, std::function<double(double, double)> parada, double precisao)
{
    double funcaoXn = 0.0;
    double DerivadaXn = 0.0;
    double parar = 1.0;
    double anterior = 0.0;

    for (int i = 0; parar > precisao; i++) {
        funcaoXn = funcao(xn);
        DerivadaXn = derivada(xn);
        parar = parada(xn, anterior);
        anterior = xn;
        exibirMetodoNewton(i, xn, funcaoXn, DerivadaXn, parar);
        xn = anterior - (funcaoXn / DerivadaXn);
    }

    return xn;
}

// Método das Secantes:
double metodoDasSecantes( double xn, double xnAnterior, std::function<double(double)> funcao, double precisao)
{
    double funcaoXnAtual = 0.0;
    double funcaoXn = 0.0;
    double funcaoXnAnterior = 0.0;
    double parar = 1.0;
    double xnAtual = 0.0;

    std::function<double(double, double, double, double)> obterXn = [](double xn,double funcaoXn, double xnAnterior, double funcaoXnAnterior){
        return ((xnAnterior * funcaoXn) - (xn * funcaoXnAnterior)) / (funcaoXn - funcaoXnAnterior);
    };

    for(int i = 0; parar > precisao; i++){
        funcaoXnAnterior = funcao(xnAnterior);
        funcaoXn = funcao(xn);
        xnAtual = obterXn(xn, funcaoXn, xnAnterior, funcaoXnAnterior);
        funcaoXnAtual = funcao(xnAtual);
        parar = parada(xnAtual, xnAnterior);
        xnAnterior = xn;
        xn = xnAtual;
        exibirMetodoSecantes(i,xnAtual, funcaoXnAtual, parar);
    }
    return xnAtual;
}

// Eliminação de Gauss:
std::vector<double> eliminacaoDeGauss(std::vector<std::vector<double>> &matriz)
{
    // Zerar abaixo da diagonal principal usando o método do maior pivô disponível (em módulo).
    for(unsigned long pivo = 0; pivo < matriz[0].size() - 2; pivo++){
        for(unsigned long linha = pivo + 1; linha < matriz.size(); linha++){
            double fator = matriz[linha][pivo] / matriz[pivo][pivo];
            for(unsigned long coluna = 0; coluna < matriz[0].size(); coluna++){
                matriz[linha][coluna] -= (fator) * (matriz[pivo][coluna]);
            }
        }
    }

     // Zerar acima da diagonal principal.
    for(unsigned long pivo = matriz[0].size() - 2; pivo > 0; pivo--){
        for(unsigned long linha = 0; linha < pivo; linha++){
            double fator = matriz[linha][pivo] / matriz[pivo][pivo];
            for(unsigned long coluna = 0; coluna < matriz[0].size(); coluna++){
                matriz[linha][coluna] -= (fator) * (matriz[pivo][coluna]);
            }
        }
    }


    // Finalizar eliminação.
    std::vector<double> respostas;
    for(size_t i = 0; i < matriz.size(); i++){
        matriz[i][matriz[i].size() - 1] /= matriz[i][i];
        matriz[i][i] /= matriz[i][i];
        respostas.push_back(matriz[i][matriz[i].size() - 1]);
    }

    return respostas;
}

// Eliminação de Gauss com pivoteamento parcial:
std::vector<double> eliminacaoDeGaussPivoteamentoParcial(std::vector<std::vector<double>> &matriz)
{
    // Zerar abaixo da diagonal principal usando o método do maior pivô disponível (em módulo).
    for(unsigned long pivo = 0; pivo < matriz[0].size() - 2; pivo++){
        size_t maiorPivo = pivo;                                            // size_t é um apelido para unsigned long.
        for(size_t i = pivo + 1; i < matriz.size(); i++){
            if(fabs(matriz[i][pivo]) > fabs(matriz[maiorPivo][pivo])){
                maiorPivo = i;
            }
        }
        if(pivo != maiorPivo){
            matriz[pivo].swap(matriz[maiorPivo]);
        }
        for(unsigned long linha = pivo + 1; linha < matriz.size(); linha++){
            double fator = matriz[linha][pivo] / matriz[pivo][pivo];
            for(unsigned long coluna = 0; coluna < matriz[0].size(); coluna++){
                matriz[linha][coluna] -= (fator) * (matriz[pivo][coluna]);
            }
        }
    }

    // Zerar acima da diagonal principal.
    for(unsigned long pivo = matriz[0].size() - 2; pivo > 0; pivo--){
        for(unsigned long linha = 0; linha < pivo; linha++){
            double fator = matriz[linha][pivo] / matriz[pivo][pivo];
            for(unsigned long coluna = 0; coluna < matriz[0].size(); coluna++){
                matriz[linha][coluna] -= (fator) * (matriz[pivo][coluna]);
            }
        }
    }

    // Finalizar eliminação.
    std::vector<double> respostas;
    for(size_t i = 0; i < matriz.size(); i++){
        matriz[i][matriz[i].size() - 1] /= matriz[i][i];
        matriz[i][i] /= matriz[i][i];
        respostas.push_back(matriz[i][matriz[i].size() - 1]);
    }

    return respostas;
}

// Gauss-Jacobi:
std::vector<double> gaussJacobi(std::vector<std::vector<double>> matriz, double precisao)
{
    double parada = 0;

    std::vector<double> respostas(matriz.size());
    for(size_t i = 0; i < matriz.size(); i++){
        respostas[i] = matriz[i][matriz[i].size() - 1] / matriz[i][i];
    }

    std::vector<double> anteriores {respostas};

    do {
        for(size_t linha = 0; linha < matriz.size(); linha++){
            double numerador = matriz[linha][matriz[linha].size() - 1];
            for(size_t coluna = 0; coluna < matriz[linha].size(); coluna++){
                if(linha != coluna){
                    numerador -= (matriz[linha][coluna] * anteriores[coluna]);
                }
            }
            respostas[linha] = numerador / matriz[linha][linha];
        }

        std::vector<double> vd {vetorDistancia(respostas, anteriores)};
        parada = max(vd) / max(respostas);
        anteriores = respostas;
    } while (parada > precisao);

    return respostas;
}

// Gauss-Seidel:
std::vector<double> gaussSeidel(std::vector<std::vector<double>> matriz, double precisao)
{
    double parada = 0;

    std::vector<double> respostas(matriz.size());
    for(size_t i = 0; i < matriz.size(); i++){
        respostas[i] = matriz[i][matriz[i].size() - 1] / matriz[i][i];
    }

    std::vector<double> anteriores {respostas};

    do {
        for(size_t linha = 0; linha < matriz.size(); linha++){
            double numerador = matriz[linha][matriz.size()];
            for(size_t coluna = 0; coluna < matriz[linha].size(); coluna++){
                if(linha != coluna){
                    numerador -= (matriz[linha][coluna] * (linha > coluna ? respostas[coluna] : anteriores[coluna]));
                }
            }
            respostas[linha] = numerador /matriz[linha][linha];
        }

        std::vector<double> vd {vetorDistancia(respostas, anteriores)};
        parada = max(vd) / max(respostas);
        anteriores = respostas;
    } while (parada > precisao);

    return respostas;
}

#endif // METODOS_HPP
