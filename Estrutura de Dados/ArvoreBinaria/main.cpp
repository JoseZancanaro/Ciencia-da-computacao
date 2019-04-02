#include "arvoreBinaria.hpp"
#include <iostream>

using namespace std;

int main()
{
    ArvoreBB arvore;
    inicializarArvoreBB(arvore);

    // Nodos da arvore
    inserirABB_recDefinitiva(arvore, 25, "a");
    inserirABB_recDefinitiva(arvore, 15, "b");
    inserirABB_recDefinitiva(arvore, 1,   "c");
    inserirABB_recDefinitiva(arvore, 19, "d");
    inserirABB_recDefinitiva(arvore, 50, "aqui");
    inserirABB_recDefinitiva(arvore, 49, "f");
    inserirABB_recDefinitiva(arvore, 51, "g");

    // Teste para percorrer os nodos
    cout << "Infixa: \t";
    percorrerArvoreInfixa(arvore.raiz);
    cout << endl << endl << "Prefixa:\t";
    percorrerArvorePrefixa(arvore.raiz);
    cout << endl << endl << "Posfixa:\t";
    percorrerArvorePosfixa(arvore.raiz);
    cout << endl << endl;

    // Teste para buscar uma chave a partir do dado ("aqui")
    cout << endl << "Buscando pelo dado, retorna a chave: " << buscarChaveRecursiva(arvore.raiz, "aqui");

    // Teste para buscar um dado a parir da chave (50)
    cout << endl << "Buscando pela chave, retorna o dado: " << buscarDadoRecursiva(arvore.raiz, 50);

    cin.get();
    return 0;
}
