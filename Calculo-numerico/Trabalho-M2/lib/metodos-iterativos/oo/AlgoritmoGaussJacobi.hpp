#ifndef ALGORITMOGAUSSJACOBI_H
#define ALGORITMOGAUSSJACOBI_H

#include "../DefinicoesIterativos.hpp"

class AlgoritmoGaussJacobi
{
    public:
        AlgoritmoGaussJacobi(const Matriz &matriz)
            : _matriz {matriz}, _respostas(matriz.size(), 0),
              _anteriores(matriz.size(), 0), _precisao(0), _iteracao(0)
        {
            inicializar();
        }

        AlgoritmoGaussJacobi(Matriz &&matriz)
            : _matriz {matriz}, _respostas(matriz.size(), 0),
              _anteriores(matriz.size(), 0), _precisao(0), _iteracao(0)
        {
            inicializar();
        }

        void proximaIteracao()
        {
            for (size_t i = 0; i < _matriz.size(); i++) {
                double numerador = _matriz[i][_matriz.size()];
                for (size_t j = 0; j < _matriz.size(); j++)
                    if (i != j) numerador -= _matriz[i][j] * _anteriores[j];
                _respostas[i] = numerador / _matriz[i][i];
            }
            _precisao = erro(_respostas - _anteriores, _respostas);
            _anteriores = _respostas;
            _iteracao++;
            this->atualizarHistorico();
        }

        Solucao& resolverAte(double precisao)
        {
            while (_precisao > precisao || _iteracao == 0)
                this->proximaIteracao();
            return _respostas;
        }

        Solucao& resolverAte(int iteracoes)
        {
            while (_iteracao < iteracoes)
                this->proximaIteracao();
            return _respostas;
        }

        double getPrecisao()
        {
            return _precisao;
        }

        int getIteracao()
        {
            return _iteracao;
        }

        Solucao& getResultado()
        {
            return _respostas;
        }

        Matriz& getMatriz()
        {
            return _matriz;
        }

        Matriz getHistorico()
        {
            return _historico;
        }

        ~AlgoritmoGaussJacobi(){}

    private:
        Matriz _matriz;
        Solucao _respostas, _anteriores;
        double _precisao;
        int _iteracao;

        Matriz _historico;

        void inicializar()
        {
            for (size_t i = 0; i < _matriz.size(); i++) {
                _respostas[i] = _matriz[i].front() / _matriz[i][i];
                _anteriores[i] = _respostas[i];
            }
        }

        void atualizarHistorico()
        {
            _historico.push_back(_respostas);
            _historico.back().push_back(_precisao);
        }
};

#endif // ALGORITMOGAUSSJACOBI_H
