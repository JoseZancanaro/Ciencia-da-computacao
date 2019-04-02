#ifndef ALGORITMONUMERICO_HPP
#define ALGORITMONUMERICO_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <algorithm>

struct Ponto
{
    double x;
    double y;
};

#ifndef METODOSEXIBICAO_HPP
    #include "metodosExibicao.hpp"
#endif // METODOSEXIBICAO_HPP

#ifndef METODOSAUXILIARES_HPP
    #include "metodosAuxiliares.hpp"
#endif // METODOSAUXILIARES_HPP

#ifndef METODOS_HPP
    #include "metodos.hpp"
#endif // METODOS_HPP

#ifndef INTERPOLACAOPOLINOMIAL_HPP
    #include "interpolacaoPolinomial.hpp"
#endif // INTERPOLAÇÃOPOLINOMIAL_HPP

#endif // ALGORITMONUMERICO_HPP
