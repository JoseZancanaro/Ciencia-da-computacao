
#ifndef INTEGRACAONUMERICA_HPP
#define INTEGRACAONUMERICA_HPP

#include <functional>
#include <iostream>
#include <cmath>

double areaPorTrapezios(std::function<double(double)> funcao, double x0, double xn, double precisao, std::ostream *os)
{
    double area = 0.0, areaAnterior = 0.0, epsilon = 0.0;

    int n = 1;

    do {
        double h = (xn - x0) / n;
        double soma = funcao(x0) + funcao(xn);

        double inicio = x0 + h, fim = xn - h;

        for (double meio = inicio; meio <= fim; meio += h) {
            soma += 2 * funcao(meio);
        }

        area = (h / 2) * soma;

        if (os) {
            (*os) << n - 1 << "," << n + 1 << "," << area << std::endl;
        }

        epsilon = fabs((area - areaAnterior) / area);
        n++;

        areaAnterior = area;
    } while (epsilon > precisao);

    return area;
}

double areaPorSimpson(std::function<double(double)> funcao, double x0, double xn, double precisao, std::ostream *os)
{
    double area = 0.0, areaAnterior = 0.0, epsilon = 0.0;

    int n = 2;

    do {
        double h = (xn - x0) / n;
        double soma = funcao(x0) + funcao(xn);

        double inicio = x0 + h, fim = xn - h;

        bool por4 = true;

        for (double meio = inicio; meio <= fim; meio += h) {
            if (por4)
                soma += 4 * funcao(meio);
            else
                soma += 2 * funcao(meio);
            por4 = !por4;
        }

        area = (h / 3) * soma;

        if (os) {
            (*os) << (n / 2) - 1 << "," << n + 1 << "," << area << std::endl;
        }

        epsilon = fabs((area - areaAnterior) / area);
        n += 2;

        areaAnterior = area;
    } while (epsilon > precisao);

    return area;
}

#endif // INTEGRACAONUMERICA_HPP
