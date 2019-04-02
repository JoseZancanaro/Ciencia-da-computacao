#ifndef ELIMINACAOGAUSSIANA_HPP
#define ELIMINACAOGAUSSIANA_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <chrono>
#include "omp.h"

/**
 * Cabeçalho de todas as funções utilizadas para este trabalho.
 */

// Algoritmo definitivo para a proposta deste trabalho:
std::vector<double> eliminacaoDeGaussPivoteamentoParcial(std::vector<std::vector<double>> &matriz);

// Funções auxiliares:
int aleatorioEntre(int minimo, int maximo);

void matrizParaCSV(const std::vector<std::vector<double>> &matriz, std::string local);

std::vector<std::vector<double>> lerMatrizCSV(std::string local);

std::vector<int> gerarCoeficientes(size_t tamanho);

std::vector<std::vector<double>> gerarMatriz(size_t tamanho, std::vector<int> coeficientes);

// Funções de impressão na tela:
void imprimirMatriz(const std::vector<std::vector<double>> &matriz);

template <typename T>
void imprimirVector(std::vector<T> vec)
{
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << "X" << i + 1 << "=" << vec[i] << std::endl;
    }
}

#endif // ELIMINACAOGAUSSIANA_HPP
