#ifndef FILAGENERICA_HPP
#define FILAGENERICA_HPP

#include <iostream>

template <typename T>
struct ElementoFila {
    T dado;
    ElementoFila<T> *proximo;
};

template <typename T>
struct Fila {
    ElementoFila<T> *inicio;
    ElementoFila<T> *fim;
    int quantidade;
};

template <typename T>
void inicializarFila(Fila<T> &fila)
{
    fila.inicio = nullptr;
    fila.fim = nullptr;
    fila.quantidade = 0;
}

// QUEUE
template <typename T>
bool enfileirar(Fila<T> &fila, T dado)
{
    ElementoFila<T> *novo = new ElementoFila<T>;						// Alocar novo elemento
    if (novo == nullptr)                                                // Verifica se foi alocado
        return false;

    novo->dado = dado;													// Acomodar dado
    novo->proximo = nullptr;											// Proximo no novo é nullptr
    if (fila.quantidade == 0) 											// Verifica se lista vazia
        fila.inicio = novo;
    else
        fila.fim->proximo = novo;										// O fim da fila grava como o proximo o novo elemento

    fila.fim = novo;													// Considerar novo como fim da fila
    fila.quantidade++;													// Incrementar a quantidade
    return true;
}

// DEQUEUE
template <typename T>
bool desenfileirar(Fila<T> &fila)
{
    if (fila.quantidade == 0)                                           // Verifica se lista está vazia
        return false;

    ElementoFila<T> *apagar = fila.inicio;								// Novo elemento chamado apagar recebe inicio da fila
    fila.inicio = fila.inicio->proximo;									// O inicio atual passa a ser o seu proximo
    fila.quantidade--;													// Decrementar quantidade
    delete apagar;														// Desaloca memória

    if (fila.inicio == nullptr)											// Verifica se a fila ficou vazia
        fila.fim = nullptr;

    return true;
}

#endif // FILAGENERICA_HPP
