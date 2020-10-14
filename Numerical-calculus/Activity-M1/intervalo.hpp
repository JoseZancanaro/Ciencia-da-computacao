#ifndef INTERVALO_H
#define INTERVALO_H

#include <functional>

template <typename T>
class Intervalo {
private:
    T inicio;
    T fim;
public:
    Intervalo (T inicio, T fim) : inicio(inicio), fim(fim) {}
    T getInicio() {
        return this->inicio;
    }
    T getFim() {
        return this->fim;
    }
};

template <typename T>
Intervalo<T> encontrarIntervaloComRaiz (int inicio, std::function<double (double)> funcao, int incremento = 1) {
    int i = inicio - 1;
    double xA = -1, xB = -1;
    do {
        i += incremento;
        xA = funcao (i);
        xB = funcao (i + 1);
    } while (xA * xB >= 0);
    return Intervalo<T>(i, i + 1);
}

#endif // INTERVALO_H
