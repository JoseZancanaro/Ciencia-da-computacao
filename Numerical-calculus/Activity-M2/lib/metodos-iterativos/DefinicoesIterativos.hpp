#ifndef DEFINICOESITERATIVO_HPP
#define DEFINICOESITERATIVO_HPP

#include "../DefinicoesNumerico.hpp"

double maiorModulo(const Linha &a)
{
    double maior = std::fabs(a.front());
    for (natural i = 1; i < a.size(); i++)
        if (std::fabs(a[i]) > maior) maior = std::fabs(a[i]);
    return maior;
}

double erro(double x, double prevX)
{
    if (x != 0.0) {
        return std::fabs((x - prevX) / x);
    }
    return 1; // Fim do mundo
}

double erro(const Linha &d, const Linha &x)
{
    double maiorEmX = maiorModulo(x);
    if (maiorEmX != 0.0) {
        return std::fabs(maiorModulo(d) / maiorEmX);
    }
    return 1; // Fim do mundo
}

#endif // DEFINICOESITERATIVO_HPP
