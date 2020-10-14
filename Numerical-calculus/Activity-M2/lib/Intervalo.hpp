#ifndef INTERVALO_H
#define INTERVALO_H

#include "AlgoritmoNumerico.hpp"

template <typename T>
class Intervalo {
    private:
        T inicio;
        T fim;
    public:
        Intervalo (T inicio, T fim)
            : inicio(inicio), fim(fim) {}
        T getInicio() {
            return this->inicio;
        }
        T getFim() {
            return this->fim;
        }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, Intervalo<T> i)
{
    os << "[" << i.getInicio() << "," << i.getFim() << "]";
    return os;
}

template <typename T>
Intervalo<T> encontrarIntervaloComRaiz (T inicio, FuncaoMatematica funcao, T incremento = 1) {
    T i = inicio - 1;
    double xA = -1, xB = -1;
    do {
        i += incremento;
        xA = funcao (i);
        xB = funcao (i + 1);
    } while (xA * xB >= 0);
    return Intervalo<T>(i, i + 1);
}

#endif // INTERVALO_H
