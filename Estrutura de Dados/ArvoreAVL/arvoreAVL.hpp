#ifndef ARVOREAVL_HPP
#define ARVOREAVL_HPP

#include <string>
#include <iostream>

struct NodoAVL{
    int chave;
    std::string dado;
    NodoAVL *maior;
    NodoAVL *menor;
    int balanceamento;
};

struct ArvoreAVL {
    NodoAVL *raiz;
    int quantidade;
};

void inicializarArvoreAVL(ArvoreAVL &arvore)
{
    arvore.raiz = nullptr;
    arvore.quantidade = 0;
}

int inserirArvoreAVL(NodoAVL *&nodo, int chave, std::string dado)
{
    if (nodo == nullptr) {
        nodo = new NodoAVL;
        nodo->chave = chave;
        nodo->dado = dado;
        nodo->maior = nullptr;
        nodo->menor = nullptr;
        nodo->balanceamento = 0;
        return 1;
    }

    if (chave > nodo->chave) {
        int soma = inserirArvoreAVL(nodo->maior, chave, dado);
        nodo->balanceamento += soma;

        if (nodo->balanceamento == 2) {
            if (chave > nodo->maior->chave)
                direitaDireita(nodo, nodo->maior, nodo->maior->maior);
            else
                direitaEsquerda(nodo, nodo->maior, nodo->maior->menor);

            soma = 0;
        }
        if (nodo->balanceamento == 0)
            soma = 0;

        return soma;

    }
    else {
        int sub = inserirArvoreAVL(nodo->menor, chave, dado);
        nodo->balanceamento -= sub;

        if (nodo->balanceamento == -2) {
            if (chave < nodo->menor->chave)
                esquerdaEsquerda(nodo, nodo->menor, nodo->menor->menor);
            else
                esquerdaDireita(nodo, nodo->menor, nodo->menor->maior);

            sub = 0;
        }
        if (nodo->balanceamento == 0)
            sub = 0;

        return sub;
    }
}

void caminharEmOrdem(NodoAVL *nodo)
{
    if (nodo != nullptr) {
        caminharEmOrdem(nodo->menor);
        std::cout << nodo->chave << " | ";
        caminharEmOrdem(nodo->maior);
    }
}

//metodo professor
void dirdir(NodoAVL *&a, NodoAVL *&b, NodoAVL *&c)
{
    a->maior = b->menor;
    b->menor = a;
    a->balanceamento = 0;
    b->balanceamento = 0;

    a = b;
}

#endif // ARVOREAVL_HPP
