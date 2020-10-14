#ifndef LISTAS_H
#define LISTAS_H

/*
	ESTRUTURA DE DADOS LINEARES - LISTAS

	Professor:
	Dr. Rafael de Santiago

	BIBLIOTECA POR:
	Allan Nathan Baron de Souza
	Israel Efraim de Oliveira
	José Carlos Zancanaro
 */

#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>

/* Listas contiguas. */
namespace Contigua
{
	/* Funções gerais para vetores. */
	namespace Util
	{
		/*
			Função definida para copiar valores de um array unidimensional.
			A cópia funciona de um vetor para outro ou no mesmo vetor, desde os índices não sejam conflitantes.
			Parâmetros: Array para ser copiado, array destino, início da cópia,
				limitador (índice do último elemento + 1), ínicio de colagem no array destino.
		*/
		template <typename T>
		void copiarVetor(T* arrayBase, T* arrayFinal, int inicioExtracao, int limiteExtracao, int inicioColagem = 0)
		{
			int indiceDeColagem = inicioColagem;
			for(int indice = inicioExtracao; indice < limiteExtracao; indice++)
				(*arrayFinal)[indiceDeColagem++] = (*arrayBase)[indice];
		}

		/*
			Funçao definida para deslocar elementos de um vetor de trás para frente.
		*/
		template <typename T>
		void deslocarElementosVetor(T* vet, int primeiro, int ultimo, int deslocamento = 1)
		{
			for(int indice = ultimo - 1; indice >= primeiro; indice--)
				(*vet)[(indice+deslocamento)] = (*vet)[indice];
		}

		template <typename T> bool Crescente(T l, T r)
		{
			return (l>r);
		}

		template <typename T> bool Decrescente(T l, T r)
		{
			return (l<r);
		}

		template <typename T> bool CrescenteI(T l, T r) 
		{
			return (l <= r);
		}

		template <typename T> bool DecrescenteI(T l, T r)
		{
			return (l >= r);
		}

		template <typename T>
		void ordenarPorBorbulhamento(T* vet, int tamanho, std::function<bool(T,T)> ordenar)
		{
			bool ordenou = true;
			for (int i = 0; i < tamanho && ordenou; i++) {
				ordenou = false;
				for (int j = 0; j < tamanho - i - 1; j++) {
					if (ordenar(vet[j], vet[j + 1])) {
						std::swap(vet[j], vet[j + 1]);
						ordenou = true;
					}
				}
			}
		}

		template <typename T>
		void realizarFusao(T arr[], int l, int m, int r, std::function<bool(T, T)> ordenar)
		{
			int i, j, indArrayPrincipal;
			int n1 = m - l + 1;
			int n2 = r - m;

			std::vector<int> L, R;

			for (i = 0; i < n1; i++)
				L.push_back(arr[l + i]);
			for (j = 0; j < n2; j++)
				R.push_back(arr[m + 1 + j]);

			i = 0;
			j = 0;
			indArrayPrincipal = l;

			while (i < n1 && j < n2) {
				if (ordenar(L[i],R[j])) {
					arr[indArrayPrincipal] = L[i];
					i++;
				}
				else {
					arr[indArrayPrincipal] = R[j];
					j++;
				}
				indArrayPrincipal++;
			}

			while (i < n1) {
				arr[indArrayPrincipal] = L[i];
				i++;
				indArrayPrincipal++;
			}

			while (j < n2){
				arr[indArrayPrincipal] = R[j];
				j++;
				indArrayPrincipal++;
			}
		}

		template <typename T>
		void ordenacaoPorFusao(T arr[], int l, int r, std::function<bool(T,T)> ordenar)
		{
			if (l < r)
			{
				int m = l + (r - l) / 2;
				ordenacaoPorFusao<T>(arr, l, m, ordenar);
				ordenacaoPorFusao<T>(arr, m + 1, r, ordenar);
				realizarFusao<T>(arr, l, m, r, ordenar);
			}
		}
	}

	/* Lista Contigua estática genérica. */
	namespace Estatica
	{
		template <typename T, int MAX>
		struct ListaCEG
		{
			T elementos[MAX];
			int quantidade;
		};

		template <typename T, int MAX>
		void inicializarListaCEG(ListaCEG<T, MAX>& lista)
		{
			lista.quantidade = 0;
		}

		template <typename T, int MAX>
		bool inserirEmIndiceLCEG(ListaCEG<T, MAX>& lista, T elemento, int indice)
		{
			if (lista.quantidade < MAX && indice <= lista.quantidade && indice >= 0){
				Contigua::Util::deslocarElementosVetor(&lista.elementos, indice, lista.quantidade, 1);
				lista.elementos[indice] = elemento;
				lista.quantidade++;
				return true;
			}
			else return false;
		}

		template <typename T, int MAX>
		bool inserirNoInicioLCEG(ListaCEG<T, MAX>& lista, T elemento)
		{
			return inserirEmIndiceLCEG(lista, elemento, 0);
		}

		template <typename T, int MAX>
		bool inserirNoFimLCEG(ListaCEG<T, MAX>& lista, T elemento)
		{
			return inserirEmIndiceLCEG(lista, elemento, lista.quantidade);
		}

		template <typename T, int MAX>
		bool removerEmIndiceLCEG(ListaCEG<T, MAX>& lista, int indice)
		{
			if (indice >= 0 && indice <= lista.quantidade - 1){
				//Contigua::Util::copiarVetor(&lista.elementos, &lista.elementos, 0, indice, 0);
				Contigua::Util::copiarVetor(&lista.elementos, &lista.elementos, indice + 1, lista.quantidade, indice);
				lista.quantidade--;
				return true;
			}
			else return false;
		}

		template <typename T, int MAX>
		bool removerNoInicioLCEG(ListaCEG<T, MAX>& lista)
		{
			return removerEmIndiceLCEG(lista, 0);
		}

		template <typename T, int MAX>
		bool removerNoFimLCEG(ListaCEG<T, MAX>& lista)
		{
			if (lista.quantidade > 0){
				lista.quantidade--;
				return true;
			}
			else return false;
		}

		template <typename T, int MAX>
		void iterarLCEG(ListaCEG<T, MAX>&lista, std::function<void(T)> func)
		{
			for (int i = 0; i < lista.quantidade; i++)
				func(lista.elementos[i]);
		}
		
		template <typename T, int MAX>
		void bubbleSortLCEG(ListaCEG<T, MAX>&lista, std::function<bool(T,T)> ordenar)
		{
			bool ordenou = true;
			for (int i = 0; i < lista.quantidade && ordenou; i++){
				ordenou = false;
				for (int j = 0; j < lista.quantidade -i -1; j++){
					if (ordenar(lista.elementos[j], lista.elementos[j+1])){
						std::swap(lista.elementos[j], lista.elementos[j+1]);
						ordenou = true;
					}
				}
			}
		}

		template <typename T, int MAX>
		void bubbleSortCrescenteLCEG(ListaCEG<T, MAX>&lista)
		{
			bubbleSortLCEG<T>(lista, Contigua::Util::Crescente<T>);
		}

		template <typename T, int MAX>
		void bubbleSortDecrescenteLCEG(ListaCEG<T, MAX>&lista)
		{
			bubbleSortLCEG<T>(lista, Contigua::Util::Decrescente<T>);
		}

		template <typename T, int MAX>
		void mergeSortLCEG(ListaCEG<T, MAX>&lista, std::function<bool(T, T)> ordenar)
		{
			Contigua::Util::ordenacaoPorFusao<T>(lista.elementos, 0, lista.quantidade - 1, ordenar);
		}

		template <typename T, int MAX>
		void mergeSortCrescenteLCEG(ListaCEG<T, MAX>&lista)
		{
			Contigua::Util::ordenacaoPorFusao<T>(lista.elementos, 0, lista.quantidade - 1, Contigua::Util::CrescenteI<T>);
		}

		template <typename T, int MAX>
		void mergeSortDecrescenteLCEG(ListaCEG<T, MAX>&lista)
		{
			Contigua::Util::ordenacaoPorFusao<T>(lista.elementos, 0, lista.quantidade - 1, Contigua::Util::DecrescenteI<T>);
		}
	}

	/* Lista Contigua dinâmica genérica. */
	namespace Dinamica
	{
		template<typename T>
		struct ListaCDG
		{
			T* elementos;
			int quantidade;	
		};

		template<typename T>
		void inicializarListaCDG(ListaCDG<T>& lista)
		{
			lista.quantidade = 0;
		}

		template <typename T>
		void inserirEmIndiceLCDG(ListaCDG<T>& lista, T elemento, int indice)
		{
			T* tLista = new T[lista.quantidade + 1];

			/*Copiar ambos os lados do vetor, deixando um espaço para o índice selecionado*/
			Contigua::Util::copiarVetor(&lista.elementos, &tLista, 0, indice, 0);
			Contigua::Util::copiarVetor(&lista.elementos, &tLista, indice, lista.quantidade, indice + 1);

			/*Inserir o elemento no novo array espelho*/
			tLista[indice] = elemento;

			/*Redefinir array interno e copiar o espelho para este*/
			lista.elementos = new T[++lista.quantidade];
			Contigua::Util::copiarVetor(&tLista, &lista.elementos, 0, lista.quantidade, 0);

			delete [] tLista;
		}

		template <typename T>
		void inserirNoInicioLCDG(ListaCDG<T>& lista, T elemento)
		{
			inserirEmIndice(lista, elemento, 0);
		}

		template <typename T>
		void inserirNoFimLCDG(ListaCDG<T>& lista, T elemento)
		{
			inserirEmIndice(lista, elemento, lista.quantidade);
		}

		template <typename T>
		void removerEmIndiceLCDG(ListaCDG<T>& lista, int indice)
		{
			T* tLista = new T[lista.quantidade - 1];

			Contigua::Util::copiarVetor(&lista.elementos, &tLista, 0, indice, 0);
			Contigua::Util::copiarVetor(&lista.elementos, &tLista, indice + 1, lista.quantidade, indice);

			lista.elementos = new T[--lista.quantidade];

			Contigua::Util::copiarVetor(&tLista, &lista.elementos, 0, lista.quantidade, 0);

			delete [] tLista;
		}

		template <typename T>
		void removerNoInicioLCDG(ListaCDG<T>& lista)
		{
			removerEmIndice(lista, 0);
		}

		template <typename T>
		void removerNoFimLCDG(ListaCDG<T>& lista)
		{
			removerEmIndice(lista, lista.quantidade-1);
		}

	}
}

/* Listas Encadeadas. */
namespace Encadeada
{
	/* Lista Singular. */
	namespace Singular
	{
		template <typename T>
		struct NoLSE
		{
			T elemento;
			NoLSE<T>* proximo;
		};

		template <typename T>
		NoLSE<T>* novoNoLSE(T elemento, NoLSE<T>* proximo = nullptr)
		{
			NoLSE<T>* noParaRetorno = new NoLSE<T>;
			noParaRetorno->elemento = elemento;
			noParaRetorno->proximo = proximo;
			return noParaRetorno;
		}

		template <typename T>
		struct ListaSE
		{
			NoLSE<T>* inicio;
			NoLSE<T>* fim;
			int tamanho;
		};

		template <typename T>
		void inicializarListaSE(ListaSE<T>& lista)
		{
			lista.inicio = nullptr;
			lista.fim = nullptr;
			lista.tamanho = 0;
		}

		template <typename T>
		NoLSE<T>* encontrarNoLSE(const ListaSE<T>& lista, int posicao)
		{
			if (lista.inicio != nullptr && lista.tamanho > posicao && posicao >= 0){
				int indice = 0;
				NoLSE<T>* tmp = lista.inicio;
				for (; tmp != nullptr && indice < posicao; tmp = tmp->proximo, indice++);
				return tmp;
			}
			else return nullptr;
		}

		template <typename T>
		NoLSE<T>* pegarPenultimoElementoLSE(const ListaSE<T>& lista)
		{
			if (lista.inicio != nullptr)
			{
				NoLSE<T>* tmp;
				for(tmp = lista.inicio; tmp->proximo != lista.fim; tmp = tmp->proximo);
				return tmp;
			} else return nullptr;
		}

		template <typename T>
		bool inserirElementoLSE(ListaSE<T>& lista, T elemento)
		{
			if (lista.inicio == nullptr) {
				lista.inicio = novoNoLSE(elemento);
				lista.fim = lista.inicio;
			}
			else {
				lista.fim->proximo = novoNoLSE(elemento);
				lista.fim = lista.fim->proximo;
			}
			lista.tamanho++;
			return true;
		}

		template <typename T>
		bool inserirNoInicioLSE(ListaSE<T>& lista, T elemento)
		{
			lista.inicio = novoNoLSE(elemento, lista.inicio);
			if (lista.fim == nullptr)
				lista.fim = lista.inicio;
			lista.tamanho++;
			return true;
		}

		template <typename T>
		bool inserirNoFimLSE(ListaSE<T>& lista, T elemento)
		{
			if (lista.fim != nullptr)
			{
				lista.fim->proximo = novoNoLSE(elemento);
				lista.fim = lista.fim->proximo;
			}
			else lista.inicio = lista.fim = novoNoLSE(elemento);
			lista.tamanho++;
			return true;
		}

		template <typename T>
		bool inserirEmPosicaoLSE(ListaSE<T>& lista, T elemento, int posicao)
		{
			if (posicao < 0)
				return false;
			if (lista.tamanho == 0 && posicao > 0)
				return false;
			if (lista.tamanho >= 0 && posicao == 0)
				return inserirNoInicioLSE(lista, elemento);
			if (lista.tamanho == posicao)
				return inserirNoFimLSE(lista, elemento);
			if (lista.tamanho > posicao){
				NoLSE<T> *ant = encontrarNoLSE(lista, posicao-1);
				NoLSE<T> *novo = novoNoLSE(elemento, ant->proximo);
				ant->proximo = novo;
				lista.tamanho++;
				return true;
			}
			return false;
		}

		template <typename T>
		bool removerNoInicioLSE(ListaSE<T>& lista)
		{
			if (lista.inicio != nullptr)
			{
				NoLSE<T>* tmp = lista.inicio;
				lista.inicio = lista.inicio->proximo;
				delete tmp;
				lista.tamanho--;
				return true;
			}
			else return false;
		}

		template <typename T>
		bool removerNoFimLSE(ListaSE<T>& lista)
		{
			if (lista.inicio != nullptr)
			{
				NoLSE<T>* tmp = pegarPenultimoElementoLSE(lista);
				delete tmp->proximo;
				lista.fim = tmp;
				lista.fim->proximo = nullptr;
				lista.tamanho--;
				return true;
			}
			else return false;
		}

		template <typename T>
		bool removerEmPosicaoLSE(ListaSE<T>& lista, int posicao)
		{
			if (posicao < 0)
				return false;
			if (lista.tamanho == 0 && posicao > 0)
				return false;
			if (lista.tamanho >= 0 && posicao == 0)
				return removerNoInicioLSE(lista);
			if (lista.tamanho-1 == posicao)
				return removerNoFimLSE(lista);
			if (lista.tamanho > posicao){
				NoLSE<T> *ant = encontrarNoLSE(lista, posicao-1);
				NoLSE<T> *pos = ant->proximo;
				ant->proximo = pos->proximo;
				delete pos;
				lista.tamanho--;
				return true;
			}
			return false;
		}

		template <typename T>
		void iterarLSE(ListaSE<T>& lista, std::function<void(T)> func)
		{
			for (NoLSE<T>* tmp = lista.inicio; tmp != nullptr; tmp = tmp->proximo)
				func(tmp->elemento);
		}

		template <typename T>
		void bubbleSortLSE(ListaSE<T>& lista, std::function<bool(T,T)> deveOrdenar)
		{
			bool realizouOrdenacao = true;
			for (NoLSE<T>* tmp = lista.inicio; tmp != nullptr && realizouOrdenacao; tmp = tmp->proximo){
				realizouOrdenacao = false;
				for(NoLSE<T>* el = lista.inicio; el->proximo != nullptr; el = el->proximo){
					if (deveOrdenar(el->elemento, el->proximo->elemento)){
						std::swap(el->elemento, el->proximo->elemento);
						realizouOrdenacao = true;
					}
				}
			}
		}

		template <typename T> void bubbleSortCrescenteLSE (ListaSE<T>& lista)
		{
			bubbleSortLSE<T>(lista, Contigua::Util::Crescente<T>);
		}

		template <typename T> void bubbleSortDecrescenteLSE (ListaSE<T>& lista)
		{
			bubbleSortLSE<T>(lista, Contigua::Util::Decrescente<T>);
		}
	}

	/* Lista Duplamente Encadeada. */
	namespace Dupla
	{
		template <typename T>
		struct NoLDE
		{
			T elemento;
			NoLDE<T>* anterior;
			NoLDE<T>* proximo;
		};

		template <typename T>
		NoLDE<T>* novoNoLDE(T elemento, NoLDE<T>* anterior = nullptr, NoLDE<T>* proximo = nullptr)
		{
			NoLDE<T>* nodoParaRetorno = new NoLDE<T>;
			if (nodoParaRetorno != nullptr){
				nodoParaRetorno->elemento = elemento;
				nodoParaRetorno->anterior = anterior;
				nodoParaRetorno->proximo = proximo;
				return nodoParaRetorno;
			}
			else return nullptr;
		}

		template <typename T>
		struct ListaDE
		{
			NoLDE<T>* inicio;
			NoLDE<T>* fim;
			int tamanho;
		};

		template <typename T>
		NoLDE<T>* encontrarNoLDE(const ListaDE<T>& lista, int posicao)
		{
			if (lista.inicio != nullptr && lista.tamanho > posicao && posicao >= 0){
				int indice = 0;
				NoLDE<T>* tmp = lista.inicio;
				for (; tmp != nullptr && indice < posicao; tmp = tmp->proximo, indice++);
				return tmp;
			}
			else return nullptr;
		}

		template <typename T>
		void inicializarListaDE(ListaDE<T>& lista)
		{
			lista.inicio = nullptr;
			lista.fim = nullptr;
			lista.tamanho = 0;
		}

		template <typename T>
		bool inserirNoInicioLDE(ListaDE<T>& lista, T elemento)
		{
			lista.inicio = novoNoLDE(elemento);										/*Alocar elemento LDE como início*/
			if (lista.inicio != nullptr)
			{
				if (lista.fim == nullptr)
					lista.fim = lista.inicio;										/*Definir fim como início*/
				else
					lista.inicio->proximo->anterior = lista.inicio; 				/*Definir o anterior do antigo início*/
				lista.tamanho++;
				return true;
			}
			else return false;
		}

		template <typename T>
		bool inserirNoFimLDE(ListaDE<T>& lista, T elemento)
		{
			NoLDE<T>* novoEl = novoNoLDE(elemento);
			if (novoEl != nullptr){
				if (lista.inicio == nullptr)
					lista.inicio = lista.fim = novoEl;
				else {
					novoEl->anterior = lista.fim;
					lista.fim->proximo = novoEl;
					lista.fim = novoEl;
				}
				lista.tamanho++;
				return true;
			}
			else return false;
		}

		template <typename T>
		bool inserirEmPosicaoLDE(ListaDE<T>& lista, T elemento, int posicao)
		{
			if (posicao < 0)
				return false;
			if (lista.tamanho == 0 && posicao > 0)
				return false;
			if (lista.tamanho >= 0 && posicao == 0)
				return inserirNoInicioLDE(lista, elemento);
			if (lista.tamanho == posicao)
				return inserirNoFimLDE(lista, elemento);
			if (lista.tamanho > posicao){
				NoLDE<T> *pos = encontrarNoLDE(lista, posicao);
				NoLDE<T> *novo = novoNoLDE(elemento, pos->anterior, pos);
				pos->anterior->proximo = novo;
				pos->anterior = novo;
				lista.tamanho++;
				return true;
			}
			return false;
		}

		template <typename T>
		bool removerNoInicioLDE(ListaDE<T>& lista)
		{
			if (lista.inicio != nullptr){
				NoLDE<T>* tmp = lista.inicio;
				lista.inicio = lista.inicio->proximo;
				if (lista.inicio != nullptr)
					lista.inicio->anterior = nullptr;
				else
					lista.fim = nullptr;
				delete tmp;
				lista.tamanho--;
			}
			else return false;
		}

		template<typename T>
		bool removerNoFimLDE(ListaDE<T>& lista)
		{
			if (lista.inicio != nullptr){
				NoLDE<T>* tmp = lista.fim;
				lista.fim = lista.fim->anterior;
				if (lista.fim != nullptr)
					lista.fim->proximo = nullptr;
				else
					lista.inicio = nullptr;
				delete tmp;
				lista.tamanho--;
				return true;
			}
			else return false;
		}

		template <typename T>
		bool removerEmPosicaoLDE(ListaDE<T>& lista, int posicao)
		{
			if (posicao < 0)
				return false;
			if (lista.tamanho == 0 && posicao > 0)
				return false;
			if (lista.tamanho >= 0 && posicao == 0)
				return removerNoInicioLDE(lista);
			if (lista.tamanho-1 == posicao)
				return removerNoFimLDE(lista);
			if (lista.tamanho > posicao){
				NoLDE<T> *pos = encontrarNoLDE(lista, posicao);
				pos->anterior->proximo = pos->proximo;
				pos->proximo->anterior = pos->anterior;
				delete pos;
				lista.tamanho--;
				return true;
			}
			return false;
		}

		template <typename T>
		void iterarLDE(ListaDE<T>& lista, std::function<void(T)> func)
		{
			for (NoLDE<T>* tmp = lista.inicio; tmp != nullptr; tmp = tmp->proximo)
				func(tmp->elemento);
		}

		template <typename T>
		void bubbleSortLDE(ListaDE<T>& lista, std::function<bool(T,T)> deveOrdenar)
		{
			bool realizouOrdenacao = true;
			for (NoLDE<T>* tmp = lista.inicio; tmp != nullptr && realizouOrdenacao; tmp = tmp->proximo){
				realizouOrdenacao = false;
				for(NoLDE<T>* el = lista.inicio; el->proximo != nullptr; el = el->proximo){
					if (deveOrdenar(el->elemento, el->proximo->elemento)){
						std::swap(el->elemento, el->proximo->elemento);
						realizouOrdenacao = true;
					}
				}
			}
		}

		template <typename T> void bubbleSortCrescenteLDE (ListaDE<T>& lista)
		{
			bubbleSortLDE<T>(lista, Contigua::Util::Crescente<T>);
		}

		template <typename T> void bubbleSortDecrescenteLDE (ListaDE<T>& lista)
		{
			bubbleSortLDE<T>(lista, Contigua::Util::Decrescente<T>);
		}
	}
}

#endif