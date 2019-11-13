#ifndef DEFINICOES_NUMERICO_HPP
#define DEFINICOES_NUMERICO_HPP

#include <ostream>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <vector>
#include <cmath>

/* DEFINIÇÕES */

using Linha = std::vector<double>;
using Matriz = std::vector<Linha>;
using Solucao = std::vector<double>;
using FuncaoMatematica = std::function<double(double)>;
using natural = std::vector<double>::size_type; // N = {0, 1, 2, 3, 4, ... }

struct Ponto
{
    double x;
    double y;
};

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &vetor)
{
    for (auto el : vetor)
        os << el << ", ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<std::vector<T>> &vetor)
{
    for (auto el : vetor)
        os << el << std::endl;
    return os;
}

template <typename T>
std::vector<T> operator-(const std::vector<T> &l, const std::vector<T> &r)
{
    // Verificar que vetores são do mesmo tamanho
    if (l.size() != r.size())
        throw std::length_error {"Subtração de vetores de tamanhos diferentes"};

    // Criar vetor de respostas com o mesmo tamanho dos vetores passados
    std::vector<T> resp(l.size());

    // Subtrair respectivos valores
    for (size_t i = 0; i < l.size(); i++)
        resp[i] = l[i] - r[i];
    return resp;
}

template <typename T>
std::vector<T> operator+(const std::vector<T> &l, const std::vector<T> &r)
{
    // Verificar que vetores são do mesmo tamanho
    if (l.size() != r.size())
        throw std::length_error {"Adição de vetores de tamanhos diferentes"};

    // Criar vetor de respostas com o mesmo tamanho dos vetores passados
    std::vector<T> resp(l.size());

    // Subtrair respectivos valores
    for (size_t i = 0; i < l.size(); i++)
        resp[i] = l[i] + r[i];
    return resp;
}

template <typename C, typename T>
std::vector<C> operator*(const std::vector<C> &vetor, T multiplicador)
{
    std::vector<C> linha;
    for (auto d : vetor) {
        linha.push_back(d * multiplicador);
    }
    return linha;
}

double rad (double graus)
{
    return ((graus * M_PI) / 180);
}

#endif // DEFINICOES_NUMERICO_HPP
