#ifndef EQUACAODIFERENCIAL_HPP
#define EQUACAODIFERENCIAL_HPP

#include "../AlgoritmoNumerico.hpp"

Ponto metodoDeEuler(std::function<double(double, double)> diferencial, Ponto ponto, double h,
                        std::function<bool(Ponto)> condicao, std::ostream *os = nullptr)
{
    while (condicao(ponto)) {
        ponto.y = ponto.y + h * diferencial(ponto.x, ponto.y);
        ponto.x = ponto.x + h;
        if (os)
            (*os) << ponto.x << "," << ponto.y << std::endl;
    }
    return ponto;
}

#endif // EQUACAODIFERENCIAL_HPP
