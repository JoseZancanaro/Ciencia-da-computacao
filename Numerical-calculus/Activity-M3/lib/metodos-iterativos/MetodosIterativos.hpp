#ifndef ITERATIVOS_H
#define ITERATIVOS_H

#include "DefinicoesIterativos.hpp"

double resolucaoPorBisseccaoLinear(FuncaoMatematica funcao, double a, double b, double precisao, std::ostream *os = nullptr)
{
    natural k = 0;
    double x, y, prevX = 0.0, epsilon = 0.0;

    if (os) {
        *os << std::setw(6) << "k," << std::setw(13) << "a," << std::setw(13) << "b,";
        *os << std::setw(13) << "x," << std::setw(17) << "f(x)," << std::setw(16) << "e" << std::endl;
    }

    do {
        x = (a + b) / 2;
        y = funcao(x);
        epsilon = erro(x, prevX);
        prevX = x;
        if (os) {
            *os << std::setw(5) << k << "," << std::setw(12) << a << "," << std::setw(12) << b << "," << std::setw(12) << x << ",";
            *os << std::setw(16) << y << "," <<  std::setw(16) << epsilon << std::endl;
        }
        if (funcao(a) * y < 0)
            b = x;
        else
            a = x;
        ++k;

    } while (epsilon > precisao && x != 0.0);

    return x;
}

double resolucaoPorFalsaPosicao(FuncaoMatematica funcao, double a, double b, double precisao, std::ostream *os = nullptr)
{
    natural k = 0;
    double x, y, fA, fB, prevX = 0.0, epsilon;

    if (os) {
        *os << std::setw(6) << "k," << std::setw(13) << "a," << std::setw(13) << "b,";
        *os << std::setw(13) << "x," << std::setw(17) << "f(x)," << std::setw(16) << "e" << std::endl;
    }

    do {
        fA = funcao(a);
        fB = funcao(b);
        x = (a * fB - b * fA) / (fB - fA);
        y = funcao(x);
        epsilon = erro(x, prevX);
        prevX = x;
        if (os) {
            *os << std::setw(5) << k << "," << std::setw(12) << a << "," << std::setw(12) << b << "," << std::setw(12) << x << ",";
            *os << std::setw(16) << y << "," <<  std::setw(16) << epsilon << std::endl;
        }
        if (fA * y < 0)
            b = x;
        else
            a = x;
        ++k;
    } while (epsilon > precisao && x != 0.0);

    return x;
}

double resolucaoPorNewton(FuncaoMatematica funcao, FuncaoMatematica derivada, double x, double precisao, std::ostream *os = nullptr)
{
    natural k = 0;
    double y, dy, prevX = 0.0, epsilon;

    if (os) {
        *os << std::setw(6) << "k," << std::setw(13) << "x," << std::setw(17) << "f'(x),";
        *os << std::setw(17) << "f(x)," << std::setw(16) << "e" << std::endl;
    }

    do {
        y = funcao(x);
        dy = derivada(x);
        epsilon = erro(x, prevX);
        prevX = x;
        if (os) {
            *os << std::setw(5) << k << "," << std::setw(12) << x << "," << std::setw(16) << dy << ",";
            *os << std::setw(16) << y << "," << std::setw(15) << epsilon << std::endl;
        }
        x = x - y / dy;
        ++k;
    } while (epsilon > precisao && x != 0.0);

    return x;
}

double resolucaoPorSecantes(FuncaoMatematica funcao, double prevX, double x, double precisao, std::ostream *os = nullptr)
{
    natural k = 0;
    double y, prevY, antX = 0.0, epsilon;

    if (os) {
        *os << std::setw(6) << "k," << std::setw(13) << "x," << std::setw(17) << "f(x),";
        *os << std::setw(16) << "e" << std::endl;
    }

    do {
        y = funcao(x);
        prevY = funcao(prevX);
        epsilon = erro(x, prevX);
        antX = x;
        if (os) {
            *os << std::setw(5) << k << "," << std::setw(12) << x << "," << std::setw(16) << y << ",";
            *os << std::setw(15) << epsilon << std::endl;
        }
        x = (prevX * y - x * prevY) / (y - prevY);
        prevX = antX;
    } while (epsilon > precisao && x != 0.0);

    return x;
}

Solucao eliminacaoGaussJacobi(Matriz &matriz, double precisao)
{
    Solucao respostas(matriz.size());

    for (natural i = 0; i < matriz.size(); i++)
        respostas[i] = matriz[i].back() / matriz[i][i];

    Solucao anteriores {respostas};

    double epsilon = 0.0;

    do {
        for (natural linha = 0; linha < matriz.size(); linha++) {
            double numerador = matriz[linha].back();
            for (natural coluna = 0; coluna < matriz[linha].size(); coluna++)
                if (linha != coluna)
                    numerador -= matriz[linha][coluna] * anteriores[coluna];
            respostas[linha] = numerador / matriz[linha][linha];
            epsilon = erro(respostas - anteriores, respostas);
            anteriores = respostas;
        }
    } while (epsilon > precisao);

    return respostas;
}

Solucao eliminacaoGaussSeidel(Matriz &matriz, double precisao)
{
    Solucao respostas(matriz.size());

    for (size_t i = 0; i < matriz.size(); i++)
        respostas[i] = matriz[i].back() / matriz[i][i];

    Solucao anteriores {respostas};

    double epsilon = 0.0;

    do {
        for (natural linha = 0; linha < matriz.size(); linha++) {
            double numerador = matriz[linha].back();
            for (natural coluna = 0; coluna < matriz[linha].size(); coluna++)
                if (linha != coluna)
                    numerador -= (matriz[linha][coluna] * (linha > coluna ? respostas[coluna] : anteriores[coluna]));
            epsilon = erro(respostas - anteriores, respostas);
            anteriores = respostas;
        }
    } while (epsilon > precisao);

    return respostas;
}

bool convergePorLinhas(const Matriz &matriz)
{
    bool isMenor = true;
    for (natural linha = 0; linha < matriz.size() && isMenor; linha++) {
        double acumulador = 0.0;
        for (natural coluna = 0; coluna < matriz.size(); coluna++)
            if (linha != coluna) acumulador += fabs(matriz[linha][coluna]);
        isMenor = (acumulador / fabs(matriz[linha][linha])) < 1;
    }
    return isMenor;
}

bool convergePorSassenfeld(const Matriz &matriz)
{
    Linha alpha (matriz.size());
    bool isMenor = true;
    for (natural linha = 0; linha < matriz.size() && isMenor; linha++) {
        double acumulador = 0.0;
        for (natural coluna = 0; coluna < matriz.size(); coluna++) {
            if (linha != coluna)
                acumulador += fabs(matriz[linha][coluna]) * (linha > coluna ? alpha[coluna] : 1);
        }
        alpha[linha] = (acumulador /= fabs(matriz[linha][linha]));
        isMenor = acumulador < 1;
    }
    return isMenor;
}

#endif // ITERATIVOS_H
