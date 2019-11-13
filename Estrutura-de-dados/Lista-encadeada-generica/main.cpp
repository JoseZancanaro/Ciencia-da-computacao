#include "listaEncadeadaGenerica.hpp"

using namespace std;

void imprimirListaMusica(ListaEncadeada<Musica> lista)
{
    for (Elemento<Musica> *aux = lista.inicio; aux != nullptr; aux = aux->proximo){
        std::cout << aux->dado.artista << std::endl;
        std::cout << aux->dado.titulo << std::endl << std::endl;
    }
}

int main()
{
    ListaEncadeada <Musica>play;
    Musica a {"Run", "Foo Fighters"};
    Musica b {"B.Y.O.B", "System of a Down"};

    inicializarListaEncadeada(play);
    inserirFimListaEncadeada(play, a);
    inserirInicioListaEncadeada(play, b);
    imprimirListaMusica(play);
    removerInicioListaEncadeada(play);
    removerFimListaEncadeada(play);
    imprimirListaMusica(play);

    cin.get();
    return 0;
}
