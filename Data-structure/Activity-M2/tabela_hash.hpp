#ifndef TABELAS_HASH_HPP
#define TABELAS_HASH_HPP

#include <math.h>
#include <functional>

/* Função de dispersão por divisão (módulo de uma chave por um tamanho). */
int hashModular(int chave, int tamanho)
{
	if (chave < 0)
		chave = (chave % tamanho) + tamanho;
	return (chave % tamanho);
}

namespace aberta
{
	/* Elemento indexado. */
	template <typename T>
	struct TElementoIndexado
	{
		int chave;
		T dado;
		bool ocupado;
	};

	/* Tabela hash com tratamento de colisão através do endereçamento aberto. */
	template <typename T, int MAX>
	struct TabelaHashAberta
	{
		TElementoIndexado<T> elementos[MAX];
		int quantidade;
		std::function<int(int,int)> hash;																// Armazenar função de dispersão
	};

	/* Inicializar uma tabela hash aberta. */
	template <typename T, int MAX>
	void inicializarTabelaHash(TabelaHashAberta<T, MAX> &tabela, std::function<int(int,int)> funcao = hashModular)
	{
		tabela.quantidade = 0;
		tabela.hash = funcao;
		for (int i = 0; i < MAX; i++)
			tabela.elementos[i].ocupado = false;
	}

	/* Função para inserir em um índice relativo à chave numa tabela hash. */
	template <typename T, int MAX>
	bool inserirEmTabelaHash(TabelaHashAberta<T, MAX> &tabela, int chave, T dado, int &instrucoes)
	{
		if (tabela.quantidade < MAX) {																	// Verificar se a tabela possui espaços livres:
			int posicao = tabela.hash(chave, MAX), limiteBusca = 0;
			for (; tabela.elementos[posicao].ocupado && limiteBusca < MAX; posicao = tabela.hash(posicao + 1, MAX)) {
				if (tabela.elementos[posicao].chave == chave)											// e verificar se não há chaves idênticas:
					return false;
				limiteBusca++;																			// Não inserir se chave houver repetição.
				instrucoes++;
			}
			tabela.elementos[posicao].chave = chave;													// Inserir chave.
			tabela.elementos[posicao].dado = dado;														// Inserir dado.
			tabela.elementos[posicao].ocupado = true;													// Definir posição como ocupada.
			tabela.quantidade++;
			return true;
		}
		return false;																					// Tabela cheia.
	}

	/* Consultar a chave na tabela hash e retornar um ponteiro para o dado onde foi encontrada. */
	template <typename T, int MAX>
	T* consultarChaveEmTabelaHash(TabelaHashAberta<T, MAX> &tabela, int chave, int &instrucoes)
	{
		if (tabela.quantidade != 0) {																	// Não consultar tabelas vazias																									
			int posicao = tabela.hash(chave, MAX), limiteBusca = 0;										// Procurar enquanto houver posições ocupadas.
			for (; tabela.elementos[posicao].ocupado && limiteBusca < MAX; posicao = tabela.hash(posicao + 1, MAX)) {
				if (tabela.elementos[posicao].chave == chave) {											// Se chaves forem iguais:
					return &tabela.elementos[posicao].dado;												// Retornar ponteiro pro dado.
				}
				limiteBusca++;
				instrucoes++;
			}
			return nullptr;
		}
		return nullptr;																					// Tabela vazia.
	}
}

namespace encadeada
{
	/* Nodo indexado. */
	template <typename T>
	struct TNodoIndexado
	{
		int chave;
		T dado;
		TNodoIndexado<T> *proximo;
	};

	/* Criar novo nodo indexado. */
	template <typename T>
	TNodoIndexado<T> *novoTNodoIndexado(int chave, T dado, TNodoIndexado<T> *proximo = nullptr)
	{
		TNodoIndexado<T> *novo = new TNodoIndexado<T>;													// Alocar memória.
		if (novo != nullptr) {																			// Se a memória foi alocada:
			novo->chave = chave;																		// Definir chave.
			novo->dado = dado;																			// Definir dado.
			novo->proximo = proximo;																	// Definir próximo.
		}
		return novo;																					// Retornar endereço do novo nodo;
	}

	/* Tabela hash (de dispersão) com tratamento de colisão através do encadeamento de dados. */
	template <typename T, int MAX>
	struct TabelaHashEncadeada
	{
		TNodoIndexado<T> *elementos[MAX];																// Vetor de ponteiros para listas encadeadas.
		int quantidade;
		std::function<int(int,int)> hash;																// Função para armazenar lista encadeada.
	};

	/* Inicializar tabela hash de listas encadeadas. */
	template <typename T, int MAX>
	void inicializarTabelaHash(TabelaHashEncadeada<T, MAX> &tabela, std::function<int(int,int)> funcao = hashModular)
	{
		tabela.quantidade = 0;																			// Definir quantidade da tabela como 0.
		tabela.hash = funcao;
		for (int i = 0; i < MAX; i++)																	// Definir todos os elementos como nulos.
			tabela.elementos[i] = nullptr;
	}

	/* Inserir em uma tabela hash de listas encadeadas. */
	template <typename T, int MAX>
	bool inserirEmTabelaHash(TabelaHashEncadeada<T, MAX> &tabela, int chave, T dado, int &instrucoes)
	{
		TNodoIndexado<T> *novo = novoTNodoIndexado(chave, dado);										// Criar novo nodo acomodando chave e dado.
		if (novo != nullptr) {																			// Verificar se a memória foi alocada:
			int indiceInsercao = tabela.hash(chave, MAX);												// Encontrar índice da lista onde o nodo será inserido.
			TNodoIndexado<T> *nav = tabela.elementos[indiceInsercao], *inserirEm = nullptr;				// Criar ponteiro para a lista no índice hash.
			if (nav == nullptr)																			// Se a lista estava vazia:
				tabela.elementos[indiceInsercao] = novo;												// Definir o novo como o inicio.
			else {																						// Senão:
				while (nav != nullptr) {																// Procurar último elemento
					instrucoes++;
					inserirEm = nav;
					if (nav->chave == chave) {															// Verificar se chave já existia:	
						delete novo;																	// Desalocar memória.
						return false;																	// Não é possível inserir chaves repetidas.
					}
					nav = nav->proximo;
				}
				inserirEm->proximo = novo;																// Inserir novo elemento no fim da lista.
			}
			tabela.quantidade++;
			return true;
		}
		return false;																					// Memória não alocada.
	}

	/* Consultar um dado numa tabela hash através de sua chave. */
	template <typename T, int MAX>
	T* consultarChaveEmTabelaHash(TabelaHashEncadeada<T, MAX> &tabela, int chave, int &instrucoes)
	{
		int indiceInsercao = tabela.hash(chave, MAX);												// Encontrar índice hash.
		TNodoIndexado<T> *procurar = tabela.elementos[indiceInsercao];								// Criar ponteiro para busca iniciando no índice hash.
		while (procurar != nullptr) {																// Enquanto há elementos na lista:
			if (procurar->chave == chave) return &procurar->dado;									// Retornar se chaves são iguais.
			procurar = procurar->proximo;
			instrucoes++;																			// Senão, navegar para o próximo elemento na lista.
		}
		return nullptr;																				// Não há elementos na lista ou chave não existe.
	}
}

#endif