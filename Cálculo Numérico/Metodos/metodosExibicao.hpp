#ifndef METODOSEXIBICAO_HPP
#define METODOSEXIBICAO_HPP

#include "algoritmoNumerico.hpp"

// Funções de exibição.
void exibirBisseccao(int i, double a, double b, double xmed, double f_a, double f_x, double e)
{
    printf("%d %.4f %.4f %.6f %.6f %.6f %.5f\n",
        i, a, b, xmed, f_a, f_x, e);
}

void exibirFalsaPosicao(int i, double a, double b, double x, double f_a, double f_b, double f_x, double e)
{
    printf("%d %.4f %.4f %.6f %.6f %.6f %.6f %.5f\n",
        i, a, b, x, f_a, f_b, f_x, e);
}

void exibirMetodoNewton(int i, double x, double f_x, double df_x, double e)
{
    printf("%d %.8f %.8f %.8f %.5f\n",
        i, x, f_x, df_x, e);
}

void exibirMetodoSecantes(int i, double x, double f_x, double e)
{
    printf("%d %.8f %.8f %.5f\n",
        i, x, f_x, e);
}

void imprimirMatriz(std::vector<std::vector<double>> matriz)
{
    for(unsigned long i = 0; i < matriz.size(); i++){
        for(unsigned long j = 0; j < matriz[i].size(); j++){
            std::cout << matriz[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void imprimirVector(std::vector<double> vec)
{
    for(size_t i = 0; i < vec.size(); i++){
        std::cout << "X" << i + 1 << " = " << vec[i] << std::endl;
    }
}

#endif // METODOSEXIBICAO_HPP
