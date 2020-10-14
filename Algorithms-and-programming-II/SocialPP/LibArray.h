#pragma once

template<typename Tipo>
void copiarArray(Tipo *arrayBase, Tipo *ArrayDestino, long tamanho)
{
	for (long indiceDeCopia = 0; indiceDeCopia < tamanho; indiceDeCopia++)
		ArrayDestino[indiceDeCopia] = arrayBase[indiceDeCopia];
}

/* ESTRUTURA DE LISTAGEM
 * Utilizando struct como class, apesar de não ser indicado por convenções de programação.
 */
template<typename TipoDeElemento>
struct Lista
{
	int quantidadeDeElementos;
	TipoDeElemento* elemento;

	void AdicionarElemento(TipoDeElemento elementoParaCadastrar)
	{
		TipoDeElemento* novaLista = new TipoDeElemento[quantidadeDeElementos];
		copiarArray(elemento, novaLista, quantidadeDeElementos);

		elemento = new TipoDeElemento[quantidadeDeElementos + 1];
		copiarArray(novaLista, elemento, quantidadeDeElementos);
		elemento[quantidadeDeElementos] = elementoParaCadastrar;

		delete[] novaLista;
		quantidadeDeElementos++;
	}

	int Contar()
	{
		return (quantidadeDeElementos);
	}

	void Redefinir()
	{
		quantidadeDeElementos = 0;
		TipoDeElemento* elemento = new TipoDeElemento[0];
	}

	Lista()
	{
		Redefinir();
	}
};