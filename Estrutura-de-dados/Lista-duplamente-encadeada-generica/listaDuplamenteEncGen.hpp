#ifndef LISTADUPLAMENTEENCGEN_HPP
#define LISTADUPLAMENTEENCGEN_HPP

#include <string>

struct Musica {
    std::string titulo;
    std::string artista;
};

template <typename T>
struct Elemento {
    T dado;
    T *proximo;
    T *anterior;
};

template <typename T>
struct ListaDuplamente {
    T *inicio;
    T *fim;
    int quantidade;
};

template <typename T>
void inicializarLista(ListaDuplamente<T> &lista)
{
    lista.inicio = nullptr;
    lista.fim = nullptr;
    lista.quantidade = 0;
}

template <typename T>
bool inserirInicioLista(ListaDuplamente<T> &lista, T dado)
{
    Elemento<T> *novo = new Elemento<T>;
    if (novo == nullptr)
        return false;

    novo->dado = dado;
    novo->anterior = nullptr;
    novo->proximo = lista.inicio;
    lista.inicio = novo;

    if (lista.quantidade == 0)
        lista.fim = novo;
    else
        lista.inicio->proximo->anterior;

    lista.quantidade++;
    return true;
}

template <typename T>
bool inserirFimLista(ListaDuplamente<T> &lista, T dado)
{
    Elemento<T> *novo = new Elemento<T>;
    if (novo == nullptr)
        return false;

    novo->dado = dado;
    novo->proximo = nullptr;
    novo->anterior = lista.fim;

    if (lista.quantidade > 0)
        lista.fim->proximo = novo;

    else
        lista.inicio = novo;

    lista.fim = novo;
    lista.quantidade++;
    return true;
}

template <typename T>
bool removerInicioLista(ListaDuplamente<T> &lista)
{
    if (lista.quantidade == 0)
        return false;

    Elemento<T> *save = lista.inicio;
    lista.inicio = lista.inicio->proximo;
    delete save;

    if (lista.quantidade > 1)
        lista.inicio->anterior = nullptr;
    else
        lista.fim = nullptr;

    lista.quantidade--;
    return true;
}

template <typename T>
bool removerFimLista(ListaDuplamente<T> &lista)
{
    if (lista.quantidade == 0)
        return false;

    Elemento<T> *save = lista.fim;
    lista.fim = lista.fim->anterior;
    delete save;

    if (lista.quantidade > 1)
        lista.fim->proximo = nullptr;
    else
        lista.inicio = nullptr;

    lista.quantidade--;
    return true;
}

#endif // LISTADUPLAMENTEENCGEN_HPP
