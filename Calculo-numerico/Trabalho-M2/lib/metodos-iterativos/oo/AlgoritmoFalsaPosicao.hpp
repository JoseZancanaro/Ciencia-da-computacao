#ifndef ALGORITMOFALSAPOSICAO_H
#define ALGORITMOFALSAPOSICAO_H

#include "../DefinicoesIterativos.hpp"

class AlgoritmoFalsaPosicao
{
    public:
        AlgoritmoFalsaPosicao(const FuncaoMatematica &funcao, double a, double b)
            : _funcao(funcao), _iteracao(0), _a(a), _b(b), _x1(0.0), _erro(1.0)
        {
            this->proximo();
        }

        void proximaIteracao()
        {
            this->redefinirIntervalo();
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
            while (_erro > precisao)
                this->proximaIteracao();
            return this->valor();
        }

        double resolverAte(int numeroIteracoes)
        {
            while (_iteracao < numeroIteracoes)
                this->proximaIteracao();
            return this->valor();
        }

        ~AlgoritmoFalsaPosicao(){}

    private:
        FuncaoMatematica _funcao;
        int _iteracao;
        double _a, _b, _x0, _x1, _erro;

        void proximo()
        {
            _x0 = _x1;
            _x1 = (_a * _funcao(_b) - _b * _funcao(_a)) / (_funcao(_b) - _funcao(_a));
        }

        void calcularErro()
        {
            this->_erro = fabs((_x1 - _x0) / _x1);
        }

        void redefinirIntervalo()
        {
            if (this->_funcao(_a) * this->_funcao(_x1) > 0)
                _a = _x1;
            else
                _b = _x1;
        }
};

#endif // ALGORITMOFALSAPOSICAO_H
