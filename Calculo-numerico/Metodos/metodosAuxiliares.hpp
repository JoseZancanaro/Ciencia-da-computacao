#ifndef METODOSAUXILIARES_HPP
#define METODOSAUXILIARES_HPP

#include "algoritmoNumerico.hpp"

// Funções Auxiliares:
// Definir vetor distância.
std::vector<double> vetorDistancia(const std::vector<double> &vecAtual, const std::vector<double> &vecAnterior)
{
    if(vecAtual.size() != vecAnterior.size()){
        throw std::length_error{"Tamanhos diferentes"};
    }
    std::vector<double> vd(vecAtual.size());
    for(size_t i = 0; i < vecAtual.size(); i++){
        vd[i] = vecAtual[i] - vecAnterior[i];
    }

    return vd;
}

// Encontrar o maior valor do vector.
double max(const std::vector<double> &vec)
{
    double valorMaximo = fabs(vec[0]);
    for(size_t i = 1; i < vec.size(); i++){
        if(valorMaximo < fabs(vec[i])){
            valorMaximo = fabs(vec[i]);
        }
    }
    return valorMaximo;
}

// Condição de parada
double parada(double xn, double anterior)
{
    return (fabs((xn - anterior) / xn));
}

// Critérios para saber se é possível realizar método para Gauss-Jacobi ou Gauss-Seidel.
bool criterioDasLinhas(const std::vector<std::vector<double>> &matriz)
{
    bool isMenor = true;

    for(size_t linha = 0; linha < matriz.size() && isMenor; linha++){
        double acumulador = 0.0;
        for(size_t coluna = 0; coluna < matriz.size(); coluna++){
            if(linha != coluna)
                acumulador += fabs(matriz[linha][coluna]);
        }
        acumulador /= fabs(matriz[linha][linha]);
        isMenor = (acumulador < 1);
    }
    return isMenor;
}

bool criterioDeSassenfeld(const std::vector<std::vector<double>> &matriz)
{
    std::vector<double> beta(matriz.size());
    bool isMenor = true;

    for(size_t linha = 0; linha < matriz.size() && isMenor; linha++){
        for(size_t coluna = 0; coluna < matriz.size(); coluna++){
            if(linha != coluna)
                beta[linha] += fabs(matriz[linha][coluna]) * (linha > coluna ? beta[coluna] : 1);
        }
        beta[linha] /= fabs(matriz[linha][linha]);
        isMenor = beta[linha] < 1;
    }
    return isMenor;
}

#endif // METODOSAUXILIARES_HPP
