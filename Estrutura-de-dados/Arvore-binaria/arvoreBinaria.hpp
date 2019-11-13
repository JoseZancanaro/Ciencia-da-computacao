#ifndef ARVOREBINARIA_HPP
#define ARVOREBINARIA_HPP

#include <algorithm>
#include <string>
#include <iostream>

struct NodoABB {
    int chave;
    std::string dado;
    NodoABB *menor;
    NodoABB *maior;
};

struct ArvoreBB {
    NodoABB *raiz;
    int quantidade;
};

void inicializarArvoreBB(ArvoreBB &arvore)
{
    arvore.raiz = nullptr;
    arvore.quantidade = 0;
}

bool inserirArvoreBB_it(ArvoreBB &arvore, int chave, std::string dado)
{
    NodoABB *nodo = new NodoABB;
    if (nodo == nullptr)
        return false;

    nodo->chave = chave;
    nodo->dado = dado;
    nodo->menor = nullptr;
    nodo->maior = nullptr;

    if (arvore.quantidade == 0) {
        arvore.raiz = nodo;
        arvore.quantidade++;
        return true;
    }

    NodoABB *nav = arvore.raiz, *inserir = nullptr;
    while (nav != nullptr) {
        inserir = nav;
        if (nav->chave == chave) {
            delete nodo;
            return false;
        }
        else if (chave > nav->chave)
            nav = nav->maior;
        else
            nav = nav->menor;
    }

    // Inserir está com a posição a ser colocado o nodo, motivo do processo abaixo

    if (chave > inserir->chave)
        inserir->maior = nodo;
    else
        inserir->menor = nodo;

    arvore.quantidade++;
    return true;
}

bool inserirArvoreBB_rec(NodoABB *&nodo, int chave, std::string dado)
{
    if (nodo == nullptr) {
        nodo = new NodoABB;
        nodo->chave = chave;
        nodo->dado = dado;
        nodo->maior = nullptr;
        nodo->menor = nullptr;
        return true;
    }
    else {
        if (chave == nodo->chave)
            return false;

        else if (chave > nodo->chave)
            return inserirArvoreBB_rec(nodo->maior, chave, dado);
        else
            return inserirArvoreBB_rec(nodo->menor, chave, dado);
    }
}

// Complemento da recursiva, incrementando a quantidade
bool inserirABB_recDefinitiva(ArvoreBB &arvore, int chave, std::string dado)
{
    bool inseriu = inserirArvoreBB_rec(arvore.raiz, chave, dado);

    if (inseriu)
        arvore.quantidade++;

    return inseriu;
}

// Infixa [Em ordem] (Esquerda, Visita, Direita)
void percorrerArvoreInfixa(NodoABB *nodo)
{
    if (nodo != nullptr) {
        percorrerArvoreInfixa(nodo->menor);
        std::cout << nodo->chave << " | ";
        percorrerArvoreInfixa(nodo->maior);
    }
}

// PosFixa [Pós ordem] (Esquerda, Direita, Visita)
void percorrerArvorePosfixa(NodoABB *nodo)
{
    if (nodo != nullptr) {
        percorrerArvorePosfixa(nodo->menor);
        percorrerArvorePosfixa(nodo->maior);
        std::cout << nodo->chave << " | ";
    }
}

// PreFixa [Prefixa] (Visita, Esquerda, Direita)
void percorrerArvorePrefixa(NodoABB *nodo)
{
    if (nodo != nullptr) {
        std::cout << nodo->chave << " | ";
        percorrerArvorePrefixa(nodo->menor);
        percorrerArvorePrefixa(nodo->maior);
    }
}

std::string buscarDadoIterativa(ArvoreBB arvore, int chave)
{
    NodoABB *atual = arvore.raiz;

    while (atual != nullptr) {
        if (atual->chave == chave)
            return atual->dado;

        if (chave > atual->chave)
            atual = atual->maior;
        else
            atual = atual->menor;
    }
    return "Chave desconhecida";
}

std::string buscarDadoRecursiva(NodoABB *nodo, int chave)
{
    if (nodo == nullptr)
        return "Chave desconhecida";

    if (nodo->chave == chave)
        return nodo->dado;
    else {
        if (chave > nodo->chave)
            return buscarDadoRecursiva(nodo->maior, chave);
        else
            return buscarDadoRecursiva(nodo->menor, chave);
    }
}

int buscarChaveRecursiva(NodoABB *nodo, std::string dado)
{
    if (nodo == nullptr)
        return -1;

    if (nodo->dado == dado)
        return nodo->chave;

    int buscaNaEsquerda = buscarChaveRecursiva(nodo->menor, dado);
    if (buscaNaEsquerda != -1)
        return buscaNaEsquerda;

    return buscarChaveRecursiva(nodo->maior, dado);
}

void removerNodo(NodoABB *&nodo)
{
    NodoABB *maiorDosMenores = nodo->menor, *pai = nullptr;

    if (maiorDosMenores == nullptr) {
        NodoABB *mem = nodo;
        nodo = nodo->maior;
        delete mem;
    }
    else {
        while (maiorDosMenores->maior != nullptr) {
            pai = maiorDosMenores;
            maiorDosMenores = maiorDosMenores->maior;
        }
        maiorDosMenores->maior = nodo->maior;

        if (pai != nullptr) {
            pai->maior = maiorDosMenores->menor;
            maiorDosMenores->menor = nodo->menor;

        }
        delete nodo;
        nodo = maiorDosMenores;
    }
    // OBS = Complexidade do pior caso altura da arvore -1
}

bool encontrarRemover(NodoABB *&nodo, int chave)
{
    if (nodo == nullptr)
        return false;

    if (chave == nodo->chave) {
        removerNodo(nodo);
        return true;
    }
    if (chave > nodo->chave)
        return encontrarRemover(nodo->maior, chave);
    else
        return encontrarRemover(nodo->menor, chave);

    // OBS = Complexidado do pior caso seria altura da árvore.
}

#endif // ARVOREBINARIA_HPP
