#pragma once
#ifndef ARVORE_DE_EXPRESSAO_HPP
#define ARVORE_DE_EXPRESSAO_HPP
#include <string>

struct Nodo{
	char dado;
	Nodo *esquerda;
	Nodo *direita;
};

struct Arvore{
	Nodo *raiz;
};

int executarArvore(Nodo *raiz)
{
	if (raiz->direita == nullptr && raiz->esquerda == nullptr) {
		return (int)raiz->dado;
	}
	else {
		switch (raiz->dado){
		case '+':
			return executarArvore(raiz->esquerda) + executarArvore(raiz->direita);
			break;
		case '-':
			return executarArvore(raiz->esquerda) - executarArvore(raiz->direita);
			break;
		case '*':
			return executarArvore(raiz->esquerda) * executarArvore(raiz->direita);
			break;
		case '/':
			return executarArvore(raiz->esquerda) / executarArvore(raiz->direita);
			break;
		}
	}
}

Nodo *montarArvore(std::string expressao)
{
	if (expressao.size() == 0) {
		return nullptr;
	}
	
	Nodo *raiz = nullptr;

	bool somaOuSub = false;
	bool somenteNumero = true;

	int contemParanteses = 0;
	int posicaoMenorPrioridade = -1;

	for (int i = 0; i < expressao.size(); i++) {
		switch (expressao.at(i)) {
			case '(':
				contemParanteses++;
				somenteNumero = false;
				break;
			case ')':
				contemParanteses--;
				somenteNumero = false;
				break;
			case '+':
				if (contemParanteses == 0) {
					posicaoMenorPrioridade = i;
					somaOuSub = true;
					somenteNumero = false;
				}
				break;
			case '-':
				if (contemParanteses == 0) {
					posicaoMenorPrioridade = i;
					somaOuSub = true;
					somenteNumero = false;
				}
				break;
			case '*':
				if (contemParanteses == 0 && somaOuSub == false) {
					posicaoMenorPrioridade = i;
					somenteNumero = false;
				}
				break;
			case '/':
				if (contemParanteses == 0 && somaOuSub == false) {
					posicaoMenorPrioridade = i;
					somenteNumero = false;
				}
				break;
		}
	}

	if (posicaoMenorPrioridade == -1) {
		if (somenteNumero) {
			for (int i = 0; i < expressao.size(); i++) {
				if (expressao.at(i) >= 48 && expressao.at(i) <= 57) {	// Tabela ASCII, 48 = '0' e 57 = '9'. 
					raiz = new Nodo;
					raiz->dado = (expressao.at(i) - 48);
					raiz->direita = nullptr;
					raiz->esquerda = nullptr;
				}
			}
		}
		else {
			raiz = montarArvore(expressao.substr(1, expressao.size() - 2));
		}
	}
	else {
		raiz = new Nodo;
		raiz->dado = expressao.at(posicaoMenorPrioridade);
		raiz->esquerda = montarArvore(expressao.substr(0, posicaoMenorPrioridade));
		raiz->direita = montarArvore(expressao.substr(posicaoMenorPrioridade + 1));
	}
	return raiz;
}

#endif // !ARVORE_DE_EXPRESSAO_HPP

