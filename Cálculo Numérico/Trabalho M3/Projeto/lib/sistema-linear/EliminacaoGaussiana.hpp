#ifndef ELIMINACAOGAUSSIANA_HPP
#define ELIMINACAOGAUSSIANA_HPP

#include "../AlgoritmoNumerico.hpp"

Solucao eliminacaoGaussianaSimples(Matriz &matriz)
{
    for (natural pivo = 0; pivo < matriz.front().size() - 2; pivo++) {
        for (natural linha = pivo + 1; linha < matriz.size(); linha++) {
            if (matriz[linha][pivo] != 0.0) {
                double fator = matriz[linha][pivo] / matriz[pivo][pivo];
                for (natural coluna = 0; coluna < matriz[linha].size(); coluna++)
                    matriz[linha][coluna] -= fator * matriz[pivo][coluna];
            }
        }
    }

    for (natural pivo = matriz.front().size() - 2; pivo > 0; pivo--) {
        for (natural linha = 0; linha < pivo; linha++) {
            if (matriz[linha][pivo] != 0.0) {
                double fator = matriz[linha][pivo] / matriz[pivo][pivo];
                for (natural coluna = 0; coluna < matriz[linha].size(); coluna++)
                    matriz[linha][coluna] -= fator * matriz[pivo][coluna];
            }
        }
    }

    Solucao respostas(matriz.size());

    for (natural i = 0; i < matriz.size(); i++) {
        matriz[i][matriz.size()] /= matriz[i][i];
        for (natural j = 0; j < matriz.size(); j++)
           if (i != j) matriz[i][j] /= matriz[i][i];
        matriz[i][i] /= matriz[i][i];
        respostas.at(i) = matriz[i][matriz[i].size() - 1];
    }

    return respostas;
}

Solucao eliminacaoGaussianaComPivoteamento(Matriz &matriz)
{
    for (natural pivo = 0; pivo < matriz.front().size() - 2; pivo++) {
        natural maiorPivo = pivo;
        for (natural linha = pivo + 1; linha < matriz.size(); linha++) {
            if (fabs(matriz[maiorPivo][pivo]) < fabs(matriz[linha][pivo]))
                maiorPivo = linha;
        }
        if (maiorPivo > pivo)
            matriz[pivo].swap(matriz[maiorPivo]);
        for (natural linha = pivo + 1; linha < matriz.size(); linha++) {
            double fator = matriz[linha][pivo] / matriz[pivo][pivo];
            for (natural coluna = 0; coluna < matriz[linha].size(); coluna++)
                matriz[linha][coluna] -= fator * matriz[pivo][coluna];
        }
    }

    for (natural pivo = matriz.front().size() - 2; pivo > 0; pivo--) {
        for (natural linha = 0; linha < pivo; linha++) {
            if (matriz[linha][pivo] != 0.0) {
                double fator = matriz[linha][pivo] / matriz[pivo][pivo];
                for (natural coluna = 0; coluna < matriz[linha].size(); coluna++)
                    matriz[linha][coluna] -= fator * matriz[pivo][coluna];
            }
        }
    }

    Solucao respostas(matriz.size());

    for (natural i = 0; i < matriz.size(); i++) {
        matriz[i].back() /= matriz[i][i];
        for (natural j = 0; j < matriz.size(); j++)
           if (i != j) matriz[i][j] /= matriz[i][i];
        matriz[i][i] /= matriz[i][i];
        respostas.at(i) = matriz[i][matriz[i].size() - 1];
    }

    return respostas;
}

#endif // ELIMINACAOGAUSSIANA_HPP
