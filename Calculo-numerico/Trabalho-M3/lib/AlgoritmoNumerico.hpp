#ifndef ALGORITMONUMERICO_H
#define ALGORITMONUMERICO_H

/* ALGORITMOS NUMÉRICOS */

#include "DefinicoesNumerico.hpp"

#ifndef INTERVALO_H
    #include "Intervalo.hpp"
#endif

#ifndef SISTEMALINEAR_H
    #include "SistemaLinear.hpp"
#endif

#ifndef ITERATIVOS_H
    #include "./metodos-iterativos/MetodosIterativos.hpp" // ALGORITMO(S) : MÉTODOS ITERATIVOS PROCEDIMENTAIS
#endif

#ifndef ELIMINACAOGAUSSIANA_HPP
    #include "./sistema-linear/EliminacaoGaussiana.hpp" // ALGORITMO(S) : ELIMINAÇÃO GAUSSIANA SIMPLES E COM PIVOTEAMENTO PARCIAL
#endif

#ifndef ALGORITMOBISSECCAO_H
    #include "./metodos-iterativos/oo/AlgoritmoBisseccao.hpp" // ALGORITMO : MÉTODO ITERATIVO DE BISSECÇÃO LINEAR
#endif

#ifndef ALGORITMOFALSAPOSICAO_H
    #include "./metodos-iterativos/oo/AlgoritmoFalsaPosicao.hpp" // ALGORITMO : MÉTODO ITERATIVO DA FALSA POSIÇÃO
#endif

#ifndef ALGORITMONEWTON_H
    #include "./metodos-iterativos/oo/AlgoritmoNewton.hpp" // ALGORITMO : MÉTODO ITERATIVO DE NEWTON
#endif

#ifndef ALGORITMOSECANTES_H
    #include "./metodos-iterativos/oo/AlgoritmoSecantes.hpp" // ALGORITMO : MÉTODO ITERATIVO DAS SECANTES
#endif

#ifndef ALGORITMOGAUSSSIMPLES_H
    #include "./sistema-linear/oo/AlgoritmoGaussSimples.hpp" // ALGORITMO : ELIMINAÇÃO GAUSSIANA
#endif

#ifndef ALGORITMOGAUSSPIVOTEAMENTO_H
    #include "./sistema-linear/oo/AlgoritmoGaussParcial.hpp" // ALGORITMO : ELIMINAÇÃO GAUSSIANA COM PIVOTEAMENTO PARCIAL
#endif

#ifndef ALGORITMOGAUSSJACOBI_H
    #include "./metodos-iterativos/oo/AlgoritmoGaussJacobi.hpp" // ALGORITMO : MÉTODO ITERATIVO DE GAUSS-JACOBI
#endif

#ifndef ALGORITMOGAUSSSEIDEL_H
    #include "./metodos-iterativos/oo/AlgoritmoGaussSeidel.hpp" // ALGORITMO : MÉTODO ITERATIVO DE GAUSS-SEIDEL
#endif

#ifndef INTERPOLACAOPOLINOMIAL_HPP
    #include "./interpolacao-polinomial/InterpolacaoPolinomial.hpp" // ALGORITMO : INTERPOLAÇÕES POLINOMIAIS (SISTEMA LINEAR, TEOREMA DE LAGRANGE E ESQUEMA PRÁTICO)
#endif

#ifndef EQUACAODIFERENCIAL_HPP
    #include "./equacao-diferencial/EquacaoDiferencial.hpp"
#endif

#endif // ALGORITMONUMERICO_H
