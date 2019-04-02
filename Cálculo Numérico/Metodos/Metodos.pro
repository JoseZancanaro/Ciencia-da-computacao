TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    algoritmoNumerico.hpp \
    interpolacaoPolinomial.hpp \
    metodos.hpp \
    metodosAuxiliares.hpp \
    metodosExibicao.hpp
