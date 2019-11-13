#ifndef LISTAESTATICAGENERICA_HPP
#define LISTAESTATICAGENERICA_HPP

#include <iostream>

template <typename T, int MAX>
struct ListaEstatica
{
    T elementos[MAX];
    int quantidade;
};

template <typename T, int MAX>
void trocarIndices(ListaEstatica<T, MAX> &lista, int posicao = 0)
{
    for (int indice = lista.quantidade; indice > posicao; indice--) {
        lista.elementos[indice] = lista.elementos[indice - 1];
    }
}

template <typename T, int MAX>
void removerIndice(ListaEstatica<T, MAX> &lista, int posicao = 0)
{
    for (int indice = posicao; indice < lista.quantidade - 1; indice++) {
        lista.elementos[indice] = lista.elementos[indice + 1];
    }
}

template <typename T, int MAX>
void inicializaListaEstatica(ListaEstatica<T, MAX> &lista)
{
    lista.quantidade = 0;
}

template <typename T, int MAX>
bool inserirFimListaEstatica(ListaEstatica<T, MAX> &lista, T dado)
{
    if (lista.quantidade == MAX)
        return false;

    lista.elementos[lista.quantidade] = dado;
    lista.quantidade++;
    return true;
}

template<typename T, int MAX>
bool inserirInicioListaEstatica(ListaEstatica<T, MAX> &lista, T dado)
{
    if (lista.quantidade == MAX)
        return false;

    trocarIndices(lista);
    lista.elementos[0] = dado;
    lista.quantidade++;
    return true;
}

template <typename T, int MAX>
bool inserirPosicaoListaEstatica(ListaEstatica<T, MAX> &lista, T dado, int posicao)
{
    if (lista.quantidade == MAX || posicao > lista.quantidade)
        return false;

    trocarIndices(lista, posicao); /* posição de indice que será trocado. */
    lista.elementos[posicao] = dado;
    lista.quantidade++;
    return true;
}

template <typename T,int MAX>
bool removerFimListaEstatica(ListaEstatica<T, MAX> &lista)
{
    if (lista.quantidade > 0) {
        lista.quantidade--;
        return true;
    }
    return false;
}

template <typename T, int MAX>
bool removerIncioListaEstatica(ListaEstatica<T, MAX> &lista)
{
    if (lista.quantidade > 0) {
        removerIndice(lista, 0);
        lista.quantidade--;
        return true;
    }
    return false;
}

template <typename T, int MAX>
bool removerPosicaoListaEstatica(ListaEstatica<T, MAX> &lista, int posicao)
{
    if (lista.quantidade > 0) {
        removerIndice(lista, posicao); /* posicao será a indice de partida para a remoção. */
        lista.quantidade--;
        return true;
    }
    return false;
}

template <typename T, int MAX>
void imprimirListaEstatica(ListaEstatica<T, MAX> lista)
{
    for (int indice = 0; indice < lista.quantidade; indice++)
        std::cout << "Valor: " << lista.elementos[indice] << " | ";
}

#endif // LISTAESTATICAGENERICA_HPP
