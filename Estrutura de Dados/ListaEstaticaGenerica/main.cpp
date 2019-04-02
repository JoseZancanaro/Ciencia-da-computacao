#include "listaEstaticaGenerica.hpp"
#include <iostream>

using namespace std;

int main()
{
    ListaEstatica <double, 3> numeros;

    inicializaListaEstatica(numeros);
    inserirFimListaEstatica(numeros, 32.1);
    inserirPosicaoListaEstatica(numeros, 50.02, 1);
    inserirInicioListaEstatica(numeros, 14.15);

    imprimirListaEstatica(numeros);

    cin.get();
    return 0;
}
