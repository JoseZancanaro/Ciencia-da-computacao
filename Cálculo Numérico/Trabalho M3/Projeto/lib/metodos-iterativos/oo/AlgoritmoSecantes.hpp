#ifndef ALGORITMOSECANTES_H
#define ALGORITMOSECANTES_H

#include "../DefinicoesIterativos.hpp"

class AlgoritmoSecantes
{
    public:
        AlgoritmoSecantes(const FuncaoMatematica &funcao, double x0)
            : _funcao(funcao), _iteracao(0), _x1(x0), _erro(0.0)
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

        ~AlgoritmoSecantes(){}

    private:
        std::function<double(double)> _funcao;
        int _iteracao;
        double _x0, _x1, _erro;

        void proximo()
        {
            double x0 = _x0;
            _x0 = _x1;
            _x1 = (x0 * _funcao(_x1) - _x1 * _funcao(x0)) / (_funcao(_x1) - _funcao(x0));
        }

        void calcularErro()
        {
            this->_erro = fabs((_x1 - _x0) / _x1);
        }
};

#endif // ALGORITMOSECANTES_H
