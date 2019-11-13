#ifndef LISTAENCADEADAGENERICA_HPP
#define LISTAENCADEADAGENERICA_HPP

#include <string>
#include <iostream>

struct Musica {
    std::string titulo;
    std::string artista;
};

template <typename T>
struct Elemento {
    T dado;
    Elemento<T> *proximo;
};

template <typename T>
struct ListaEncadeada /* ListaEncadeada = PlayList */
{
    Elemento<T> *inicio;
    int quantidade;
};

template <typename T>
void inicializarListaEncadeada(ListaEncadeada <T>&lista)
{
    lista.inicio = nullptr;
    lista.quantidade = 0;
}

template <typename T>
bool inserirInicioListaEncadeada(ListaEncadeada<T> &lista, T dado)
{
    /* 1° passo: alocar elemento.
     * 2° passo: acomodar a musica no elemento.
     * 3° passo: próximo do novo elemento é inicio.
     * 4° passo: o novo passa a ser inicio.
     * 5° passo: incrementar a quantidade.
     */

    Elemento<T> *novo = new Elemento<T>;     // 1°
    if (novo == nullptr)
        return false;

    novo->dado = dado;                      // 2°
    novo->proximo = lista.inicio;           // 3°
    lista.inicio = novo;                    // 4°
    lista.quantidade++;                     // 5°
    return true;
}

template <typename T>
bool inserirFimListaEncadeada(ListaEncadeada<T> &lista, T dado)
{
    /* 1° passo: alocar novo elemento.
     * 2° passo: acomodar a música no novo elemento.
     * 3° passo: o registro próximo do novo elemento deve ser NULL.
     * 4° passo: encontrar o último elemento(laço de repetção).
     * 5° passo: último elemento registra o endereço do novo como seu próximo elemento.
     * 6° passo: incrementar a quantidade.
     */

    if (lista.quantidade == 0)
        return inserirInicioListaEncadeada(lista, dado);

    Elemento<T> *novo = new Elemento<T>;    // 1°
    if (novo == nullptr)
        return false;

    novo->dado = dado;  					// 2°
    novo->proximo = nullptr;				// 3°
    Elemento<T> *ultimo = lista.inicio;     // 4°
    while (ultimo->proximo != nullptr)
        ultimo = ultimo->proximo;

    ultimo->proximo = novo;                 // 5°
    lista.quantidade++;                     // 6°
    return true;
}
template <typename T>
bool removerInicioListaEncadeada(ListaEncadeada<T> &lista)
{
    /* 1° passo: guardar o endereço do inicio.
     * 2° passo: o segundo elemento passa a ser o inicio.
     * 3° passo: desalocar o antigo inicio. (save)
     * 4° passo: decrementar a quantidade.
     */

    if (lista.quantidade == 0)
        return false;

    Elemento<T> *save = lista.inicio;       // 1°
    lista.inicio = lista.inicio->proximo;	// 2°
    delete save;							// 3°
    lista.quantidade--;						// 4°
    return true;
}

template <typename T>
bool removerFimListaEncadeada(ListaEncadeada<T> &lista)
{
    if (lista.quantidade == 1)
        removerInicioListaEncadeada(lista);

    if (lista.quantidade == 0)
        return false;

    /* encontrar o fim da lista, criar ponteiro que aponta no inicio da lista. */
    Elemento<T> *navegar = lista.inicio;
    while (navegar->proximo->proximo != nullptr)
        navegar = navegar->proximo;

    delete navegar->proximo;
    navegar->proximo = nullptr;
    lista.quantidade--;
    return true;
}

template <typename T>
void imprimirListaEncadeada(ListaEncadeada<T> lista)
{
    for (Elemento<T> *aux = lista.inicio; aux != nullptr; aux = aux->proximo)
        std::cout << aux->dado << std::endl;
}

#endif // LISTAENCADEADAGENERICA_HPP
