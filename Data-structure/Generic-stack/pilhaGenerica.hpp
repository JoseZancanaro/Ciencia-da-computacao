#ifndef PILHAGENERICA_HPP
#define PILHAGENERICA_HPP

#include <string>
#include <iostream>

template <typename T>
struct Elemento {
    T dado;
    Elemento *debaixo;
};

template <typename T>
struct Pilha {
    Elemento<T> *topo;
    int quantidade;
};

template <typename T>
void inicializarPilha(Pilha<T> &pilha)
{
    pilha.topo = nullptr;
    pilha.quantidade = 0;
}

// PUSH = inserir dado
template <typename T>
bool push(Pilha<T> &pilha, T dado)
{
    Elemento<T> *novo = new Elemento<T>;                // Alocar novo elemento
    if (novo == nullptr)								// Verificar alocação
        return false;

    novo->dado = dado;									// Acomodar o dado
    novo->debaixo = pilha.topo;							// Registrar o antigo topo como elemento abaixo do novo elemento
    pilha.topo = novo;									// Definir o novo elemento como topo
    pilha.quantidade++;									// Incrementar a quantidade
    return true;
}

// POP = tomar o dado
template <typename T>
bool pop(Pilha<T> &pilha)
{
    if (pilha.quantidade == 0)							// Verificar se a pilha esta vazia
        return false;

    Elemento<T> *apagar;                                // Novo elemento
    apagar = pilha.topo;								// Novo elemento recebe o atual topo da pilha
    pilha.topo = pilha.topo->debaixo;					// Atual topo da pilha recebe o seu antecessor (debaixo)
    pilha.quantidade--;									// Decrementar quantidade
    delete apagar;										// Deletar o elemento criado antes
    return true;
}

#endif // PILHAGENERICA_HPP
