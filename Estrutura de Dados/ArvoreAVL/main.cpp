#include <iostream>
#include "arvoreAVL.hpp"

int main()
{
    int arrayArvore[] = { 101, 0, -1, 38, 41, 42, 39, 50 };

    ArvoreAVL arvore;
    inicializarArvoreAVL(arvore);

    for (int i = 0; i < 8; i++) {
        inserirArvoreAVL(arvore.raiz, arrayArvore[i], "");
        caminharEmOrdem(arvore.raiz);
        std::cout << std::endl;
    }
    std::cin.get();
    return 0;
}
