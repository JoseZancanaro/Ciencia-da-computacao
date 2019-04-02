#ifndef ARVORESBB_HPP
#define ARVORESBB_HPP

#include <string>

const char nullchar = '\0';

struct NodoSBB
{
    int chave;
    std::string dado;
    NodoSBB *menor;
    NodoSBB *maior;

    // V para vertical e H para horizontal
    char orientaMenor;
    char orientaMaior;
};

struct arvoreSBB
{
    NodoSBB *raiz;
    int quantidade;
};

int inserirArvoreSBB(NodoSBB *&nodo, int chave, std::string dado)
{
    if (nodo == nullptr) {
        nodo = new NodoSBB;
        nodo->chave = chave;
        nodo->dado = dado;
        nodo->maior = nullptr;
        nodo->menor = nullptr;

        // não é necessário as duas instruções abaixo
        nodo->orientaMaior = nullchar;
        nodo->orientaMenor = nullchar;

        return 1;
    }
    else {
        if (chave > nodo->chave) {
            int r = inserirArvoreSBB(nodo->maior, chave, dado);
            if (r == 1) {
                nodo->orientaMaior = 'h';
                r++;
            }
            else
                if (r == 2 && nodo->orientaMaior == 'h') {
                    if (chave > nodo->maior->chave) {
                        //direita direita
                        //dirdir(nodo);
                    }
                    else {
                        //direita esquerda
                        //diresq(nodo);
                    }
                    r = 1;
                }
                else
                    r = 0;

            return r;
        }
        else {
            int r = inserirArvoreSBB(nodo->menor, chave, dado);

                //implementar

                return r;
        }
    }
}

#endif // ARVORESBB_HPP
