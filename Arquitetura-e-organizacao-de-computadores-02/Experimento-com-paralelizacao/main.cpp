#include "eliminacaoGaussiana.hpp"

/**
 * Eliminação de Gauss por Pivoteamento Parcial com Paralelização OpenMP.
 * @author José Carlos Zancanaro.
 */

int main()
{
    std::string local = "../CSV/matriz512.csv";
    std::vector<std::vector<double>> matriz {lerMatrizCSV(local)};

    /* Função sem impressão de resultados, para validar no experimento: */
    eliminacaoDeGaussPivoteamentoParcial(matriz);

    /* Função com impressão de resultados do sistema linear */
    //imprimirVector(eliminacaoDeGaussPivoteamentoParcial(matriz));

    return 0;
}
