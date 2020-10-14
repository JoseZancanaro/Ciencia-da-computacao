#ifndef SISTEMALINEAR_H
#define SISTEMALINEAR_H

#include "AlgoritmoNumerico.hpp"

class SistemaLinear
{
    public:
        SistemaLinear(Matriz matriz, Solucao respostas)
            : _A(matriz.size(), Linha(matriz.size())), _X {respostas},
              _B(matriz.size()), _produtoAX(matriz.size())
        {
            if (matriz.size() != matriz[0].size() - 1)
                throw std::length_error {"Impossível extrair componentes A e B da matriz."};

            for (natural i = 0; i < matriz.size(); i++) {
                for (natural j = 0; j < matriz.size(); j++)
                    _A[i][j] = matriz[i][j];
                _B[i] = matriz[i][matriz.size()];
            }
        }

        Solucao& resolver()
        {
            for (natural i = 0; i < _A.size(); i++) {
                for (natural j = 0; j < _A.size(); j++) {
                    _produtoAX[i] += _A[i][j] * _X[j];
                }
            }
            return _produtoAX;
        }

    private:
        Matriz _A;
        Solucao _X, _B, _produtoAX;
};

#endif // SISTEMALINEAR_H
