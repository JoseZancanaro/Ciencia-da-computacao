#ifndef ALGORITMOGAUSSPIVOTEAMENTO_H
#define ALGORITMOGAUSSPIVOTEAMENTO_H

#include <vector>
#include <cmath>

class AlgoritmoGaussParcial
{
    public:
        AlgoritmoGaussParcial(const std::vector<std::vector<double>> &matriz)
            : _matriz {matriz}, _respostas(matriz.size(), 0),
              _inferior {false}, _superior {false}, _dividiu {false}
        {}

        AlgoritmoGaussParcial(std::vector<std::vector<double>> &&matriz)
            : _matriz {matriz}, _respostas(matriz.size(), 0),
              _inferior {false}, _superior {false}, _dividiu {false}
        {}

        std::vector<double> escalonarCompletamente()
        {
            // Possibilitar que seja possível chamar algum outro método
            // e concluir o escalonamento com este.
            if (!_inferior) this->escalonarTriangularInferior();
            if (!_superior) this->escalonarTriangularSuperior();
            if (!_dividiu) this->dividirCoeficientes();
            this->capturarRespostas();
            return _respostas;
        }

        void escalonarTriangularInferior()
        {
            if (!_inferior) {
                // Iterar pivôs
                for (size_t pivo = 0; pivo < _matriz.size() - 1; pivo++) {
                    // Encontrar o maior pivo
                    size_t maiorPivo = pivo;
                    for (size_t linha = pivo + 1; linha < _matriz.size(); linha++) {
                        if (fabs(_matriz[maiorPivo][pivo]) < fabs(_matriz[linha][pivo]))
                            maiorPivo = linha;
                    }
                    // Trocar linha se o maiorPivo for diferente (maior) que o pivo selecionado
                    if (maiorPivo > pivo)
                        _matriz[pivo].swap(_matriz[maiorPivo]);
                    // Escalonar sempre abaixo da diagonal principal
                    for (size_t linha = pivo + 1; linha < _matriz.size(); linha++) {
                        if (_matriz[linha][pivo] != 0.0)
                            this->escalonarLinha(linha, pivo, _matriz[linha][pivo] / _matriz[pivo][pivo]);
                    }
                }
                _inferior = true;
            }
        }

        void escalonarTriangularSuperior()
        {
            if (!_superior) {
                // Iterar pivôs
                for (size_t pivo = _matriz.size() - 1; pivo > 0; pivo--) {
                    // Escalonar sempre acima da diagonal principal
                    for (size_t linha = 0; linha < pivo; linha++) {
                        if (_matriz[linha][pivo] != 0.0)
                            this->escalonarLinha(linha, pivo, _matriz[linha][pivo] / _matriz[pivo][pivo]);
                    }
                }
                _superior = true;
            }
        }

        void dividirCoeficientes()
        {
            if (_inferior && _superior && !_dividiu) {
                for (size_t i = 0; i < _matriz.size(); i++) {
                    // Dividir colunas anteriores à diagonal principal
                    for (size_t j = 0; j < i; j++)
                        _matriz[i][j] /= _matriz[i][i];
                    // Dividir colunas posteriores à diagonal principal
                    for (size_t j = i + 1; j < _matriz[i].size(); j++)
                        _matriz[i][j] /= _matriz[i][i];
                    // Dividir o próprio termo (igualar a zero)
                    _matriz[i][i] = 1;
                }
                _dividiu = true;
            }
        }

        bool foiEscalonada()
        {
            // Retornar se concluiu o escalonamento
            return _inferior && _superior && _dividiu;
        }

        bool inferiorFoiEscalonada()
        {
            return _inferior;
        }

        bool superiorFoiEscalonada()
        {
            return _superior;
        }

        std::vector<double> getResultado()
        {
            return _respostas;
        }

        std::vector<std::vector<double>>& getMatriz()
        {
            return _matriz;
        }

        ~AlgoritmoGaussParcial(){}

    private:
        std::vector<std::vector<double>> _matriz;
        std::vector<double> _respostas;
        bool _inferior, _superior, _dividiu;

        void escalonarLinha(size_t linha, size_t pivo, double fator)
        {
            for (size_t coluna = 0; coluna < _matriz[linha].size(); coluna++)
                _matriz[linha][coluna] -= fator * _matriz[pivo][coluna];
        }

        void capturarRespostas()
        {
            for (size_t i = 0; i < _matriz.size(); i++) {
                _respostas[i] = _matriz[i][_matriz.size()];
            }
        }
};

#endif // ALGORITMOGAUSSPIVOTEAMENTO_H
