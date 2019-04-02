TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    ./lib/AlgoritmoNumerico.hpp \
    ./lib/SistemaLinear.hpp \
    ./lib/metodos-iterativos/MetodosIterativos.hpp \
    ./lib/metodos-iterativos/oo/AlgoritmoBisseccao.hpp \
    ./lib/metodos-iterativos/oo/AlgoritmoFalsaPosicao.hpp \
    ./lib/metodos-iterativos/oo/AlgoritmoNewton.hpp \
    ./lib/metodos-iterativos/oo/AlgoritmoSecantes.hpp \
    ./lib/metodos-iterativos/oo/AlgoritmoGaussJacobi.hpp \
    ./lib/metodos-iterativos/oo/AlgoritmoGaussSeidel.hpp \
    ./lib/sistema-linear/oo/AlgoritmoGaussSimples.hpp \
    ./lib/sistema-linear/oo/AlgoritmoGaussParcial.hpp \
    ./lib/interpolacao-polinomial/InterpolacaoPolinomial.hpp \
    lib/DefinicoesNumerico.hpp \
    lib/sistema-linear/EliminacaoGaussiana.hpp \
    lib/metodos-iterativos/DefinicoesIterativos.hpp \
    lib/minimos-quadrados/MinimosQuadrados.hpp \
    lib/equacao-diferencial/EquacaoDiferencial.hpp \
    lib/integracao/IntegracaoNumerica.hpp
