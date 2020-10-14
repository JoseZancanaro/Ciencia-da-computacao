#ifndef ARVOREB_HPP
#define ARVOREB_HPP

#include <string>

const int m = 2;	// Minimo, fator máximo é (2 * m)

struct Pagina {
    int registros[2 * m];
    int quantidade;
    std::string dados[2 * m];
    Pagina *filhos[2 * m + 1];
};

/**
 * Desafio 01: Crie uma função que receba a página raíz de uma árvore B
 * e retorne quantos registros ímpares existem nas páginas folhas.
 */

int verificarFolhasImpares(Pagina *pagina)
{
    if (pagina == nullptr) {
        return 0;
    }

    if (pagina->filhos[0] == nullptr) {
        int contador = 0;
        for (int i = 0; i < pagina->quantidade; i++) {
            if (pagina->registros[i] % 2 == 1) {
                contador++;
            }
        }
        return contador;
    }

    int contador = 0;
    for (int i = 0; i < pagina->quantidade + 1; i++) {
        contador += verificarFolhasImpares(pagina->filhos[i]);
    }
    return contador;
}

/**
 * Desafio 02: Criar uma função que receba uma página raíz e um inteiro K.
 * A função deve retornar quantos registros existem no nível K.
 */

int contarRegistroNoNivel(Pagina *pagina, int k)
{
    if (pagina == nullptr) {
        return 0;
    }

    if (k == 0) {
        return pagina->quantidade;
    }

    int contador = 0;
    for (int i = 0; i < pagina->quantidade + 1; i++) {
        contador += contarRegistroNoNivel(pagina->filhos[i], k - 1);
    }
    return contador;
}

#endif // ARVOREB_HPP
