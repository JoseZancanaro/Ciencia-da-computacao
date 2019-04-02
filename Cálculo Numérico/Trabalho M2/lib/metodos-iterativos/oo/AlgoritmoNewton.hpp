#ifndef ALGORITMONEWTON_H
#define ALGORITMONEWTON_H

#include "../DefinicoesIterativos.hpp"

class AlgoritmoNewton
{
    public:
        AlgoritmoNewton(const FuncaoMatematica &funcao, const FuncaoMatematica &derivada, double x0)
            : _funcao(funcao), _derivada(derivada), _iteracao(0), _x1(x0), _erro(0.0)
        {
            this->proximo();
        }

        void proximaIteracao()
        {
            this->proximo();
            this->calcularErro();
            this->_iteracao++;
        }

        double valor()
        {
            return _x1;
        }

        double resolverAte(double precisao)
        {
            while (_erro > precisao || _iteracao == 0)
                this->proximaIteracao();
            return this->valor();
        }

        double resolverAte(int numeroIteracoes)
        {
            while (_iteracao < numeroIteracoes)
                this->proximaIteracao();
            return this->valor();
        }

        ~AlgoritmoNewton(){}

    private:
        FuncaoMatematica _funcao, _derivada;
        int _iteracao;
        double _x0, _x1, _erro;

        void proximo()
        {
            _x0 = _x1;
            _x1 = _x1 - _funcao(_x1) / _derivada(_x1);
        }

        void calcularErro()
        {
            this->_erro = fabs((_x1 - _x0) / _x1);
        }
};

#endif // ALGORITMONEWTON_H
