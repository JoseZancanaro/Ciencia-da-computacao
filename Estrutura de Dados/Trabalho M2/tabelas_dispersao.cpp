#include "tabela_hash.hpp"

#include <iostream>
#include <string>
#include <locale>
#include <fstream>

using namespace std;
using namespace aberta;
using namespace encadeada;

const int SORT_VALOR_MINIMO = 1;
const int SORT_VALOR_MAXIMO = 32000;

void gravarEmArquivo(string nome, string operacao, double ocupacao, int instrucoes)
{
	ofstream arquivo("output.csv", ios::app);
	arquivo << nome << ","
			<< operacao << ","
			<< ocupacao << ","
			<< instrucoes << "\n";
	arquivo.close();
}

template <int MAX>
void gravarHashAbertaEmArquivo(TabelaHashAberta<int,MAX> tabela)
{
	ofstream arquivo("aberta.csv", ios::out | ios::trunc);
	
	for (int i = 0; i < 1000; i++){
		arquivo << i << " : " << tabela.elementos[i].chave << " -> " << tabela.hash(tabela.elementos[i].chave, MAX) << "\n";
	}

	arquivo.close();
}

template <int MAX>
void gravarHashEncadeadaEmArquivo(TabelaHashEncadeada<int,MAX> tabela)
{
	ofstream arquivo("encadeada.csv", ios::out | ios::trunc);
	
	for (int i = 0; i < 1000; i++){
		for (TNodoIndexado<int> *nodo = tabela.elementos[i]; nodo != nullptr; nodo = nodo->proximo){
			arquivo << i << " : " << nodo->chave << " -> " << tabela.hash(nodo->chave, MAX) << "\n";
		}
	}

	arquivo.close();
}

int main()
{
	// Configurações iniciais.
	setlocale(LC_ALL, "Portuguese");
	srand(time(nullptr));

	// Redefinir arquivo com títulos.
	ofstream arquivo("output.csv", ios::out | ios::trunc);
	arquivo << "Tipo," << "Operação,"
			<< "Ocupação," << "Instruções\n";
	arquivo.close();

	int contar, sort;

	// Criar tabela de dispersão - endereçamento aberto.
	TabelaHashAberta<int, 1000> tabelaAberta;
	inicializarTabelaHash(tabelaAberta);

	for (int i = 1; i <= 2000; i++){
		contar = 1;
		sort = rand() % (SORT_VALOR_MAXIMO - SORT_VALOR_MINIMO) + SORT_VALOR_MINIMO;
		inserirEmTabelaHash(tabelaAberta, sort, sort, contar);
		contar = 1;
		consultarChaveEmTabelaHash(tabelaAberta, sort, contar);
		if (i == 90 || i == 240 || i == 740 || i == 990 || i == 1990){
			// Efetuar inserções.
			for (int j = 0; j < 10; j++){
				contar = 1;
				sort = rand() % (SORT_VALOR_MAXIMO - SORT_VALOR_MINIMO) + SORT_VALOR_MINIMO;
				inserirEmTabelaHash(tabelaAberta, sort, sort, contar);
				gravarEmArquivo("End. Aberto", "Inserção", (i+10) / 1000.0, contar);
				
			}
			// Efetuar consultas.
			for (int j = 0; j < 10; j++){
				contar = 1;
				sort = rand() % (SORT_VALOR_MAXIMO - SORT_VALOR_MINIMO) + SORT_VALOR_MINIMO;
				consultarChaveEmTabelaHash(tabelaAberta, sort, contar);
				gravarEmArquivo("End. Aberto", "Consulta", (i+10) / 1000.0, contar);
			}
			i += 10;
		}
	}

	// Gravar estado final da tabela.
	gravarHashAbertaEmArquivo(tabelaAberta);

	// Criar tabela de dispersão - encadeamento de chaves.
	TabelaHashEncadeada<int, 1000> tabelaEncadeada;
	inicializarTabelaHash(tabelaEncadeada);

	for (int i = 1; i <= 2000; i++){
		contar = 1;
		sort = rand() % (SORT_VALOR_MAXIMO - SORT_VALOR_MINIMO) + SORT_VALOR_MINIMO;
		inserirEmTabelaHash(tabelaEncadeada, sort, sort, contar);
		contar = 1;
		consultarChaveEmTabelaHash(tabelaEncadeada, sort, contar);
		if (i == 90 || i == 240 || i == 740 || i == 990 || i == 1990){
			// Efetuar inserções
			for (int j = 0; j < 10; j++){
				contar = 1;
				sort = rand() % (SORT_VALOR_MAXIMO - SORT_VALOR_MINIMO) + SORT_VALOR_MINIMO;
				inserirEmTabelaHash(tabelaEncadeada, sort, sort, contar);
				gravarEmArquivo("Encadeamento", "Inserção", (i+10) / 1000.0, contar);
			}
			// Efetuar consultas.
			for (int j = 0; j < 10; j++){
				contar = 1;
				sort = rand() % (SORT_VALOR_MAXIMO - SORT_VALOR_MINIMO) + SORT_VALOR_MINIMO;
				consultarChaveEmTabelaHash(tabelaEncadeada, sort, contar);
				gravarEmArquivo("Encadeamento", "Consulta", (i+10) / 1000.0, contar);
			}
			i += 10;
		}
	}

	// Gravar estado final da tabela.
	gravarHashEncadeadaEmArquivo(tabelaEncadeada);

	return 0;
}
