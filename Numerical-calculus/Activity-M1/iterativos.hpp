#ifndef ITERATIVOS_H
#define ITERATIVOS_H

#include <iostream>
#include <fstream>
#include <iomanip>

#include <functional>
#include <vector>
#include <cmath>

using fn = std::function<double (double)>;

double erro (const double &a, const double &b) {
    return fabs ((a - b) / a);
}

double resolucaoPorBisseccaoLinear (double a, double b, fn funcao, double precisao, std::ofstream *out = nullptr) {
   double x = 0.0,
          fA = 0.0,
          fX = 0.0,
          xAnt = 0.0,
          e = precisao + 0.1;

   for (int i = 0; i == 1 || e > precisao; i++) {
       x = (a + b) / 2;
       fA = funcao (a);
       fX = funcao (x);
       e = erro (x, xAnt);
       xAnt = x;
       if (out){
           (*out) << i << "," << a << "," << b << "," << x << "," << fX << "," << e << std::endl;
       }
       if (fA * fX < 0)
           b = x;
       else
           a = x;
   }

   return x;
}

double resolucaoPorFalsaPosicao (double a, double b, fn funcao, double precisao, std::ofstream *out = nullptr) {
    double x = 0.0,
           fA = 0.0,
           fB = 0.0,
           fX = 0.0,
           ult = 0.0,
           e = precisao + 0.1;

    for (int i = 0; i == 1 || e > precisao; i++) {
        fA = funcao (a);
        fB = funcao (b);
        x = ((a * fB) - (b * fA)) / (fB - fA);
        fX = funcao (x);
        e = erro (x, ult);
        if (out){
            (*out) << i << "," << a << "," << b << "," << x << "," << fX << "," << e << std::endl;
        }
        ult = x;
        if (fA * fX < 0)
            b = x;
        else
            a = x;
    }

    return x;
}

double resolucaoPorNewton (double x, fn funcao, fn derivada, double precisao, std::ofstream *out = nullptr) {
    double fX = 0.0,
           dfX = 0.0,
           ult = 0.0,
           e = precisao + 0.1;

    for (int i = 0; i == 1 || e > precisao; i++) {
        fX = funcao (x);
        dfX = derivada (x);
        e = erro (x, ult);
        if (out){
            (*out) << i << "," << x << "," << dfX << "," << fX << "," << e << std::endl;
        }
        ult = x;
        x = x - fX / dfX;
    }
    return x;
}

double resolucaoPorSecante (double anterior, double x, fn funcao, double precisao, std::ofstream *out = nullptr) {
    double fX = 0.0,
           fXant = 0.0,
           ult = 0.0,
           e = precisao + 0.1;

    for (int i = 0; i == 1 || e > precisao; i++) {
        fX = funcao (x);
        fXant = funcao (anterior);
        e = erro (x, anterior);
        ult = x;
        if (out){
            (*out) << i << "," << x << "," << fX << "," << e << std::endl;
        }
        x = (anterior * fX - x * fXant) / (fX - fXant);
        anterior = ult;
    }

    return x;
}

std::vector<double> eliminacaoDeGauss (std::vector<std::vector<double>> &vec) {
    std::vector<double> respostas(vec.size());

    auto aplicarTransformacao = [&vec](size_t lin, size_t col, size_t pivo, double fator) -> double {
        return (vec[lin][col] - (fator * vec[pivo][col]));
    };

    for (unsigned long pivo = 0; pivo < vec[0].size() - 2; pivo++) {
        if (pivo == 5)
            pivo = 5;
        for (unsigned long linha = pivo + 1; linha < vec.size(); linha++) {
            double fator = vec[linha][pivo] / vec[pivo][pivo];
            for (unsigned long coluna = 0; coluna < vec[0].size(); coluna++)
                vec[linha][coluna] = aplicarTransformacao (linha, coluna, pivo, fator);
        }
    }

    for (unsigned long pivo = vec[0].size() - 2; pivo > 0; pivo--) {
        for (unsigned long linha = 0; linha < pivo; linha++) {
            double fator = vec[linha][pivo] / vec[pivo][pivo];
            for (unsigned long coluna = 0; coluna < vec[0].size(); coluna++)
                vec[linha][coluna] = aplicarTransformacao (linha, coluna, pivo, fator);
        }
    }

    for (unsigned long i = 0; i < vec.size(); i++) {
        vec[i][vec[i].size() -1] /= vec[i][i];
        respostas.at(i) = vec[i][vec[0].size() - 1];
    }

    return respostas;
}

double rad (double graus)
{
    return ((graus * M_PI) / 180);
}

#endif // ITERATIVOS_H
