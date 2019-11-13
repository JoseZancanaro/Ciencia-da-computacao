#pragma once
#include <Windows.h>

const int COR_PADRAO = 7, COR_VERDE_ESCURO = 2, COR_CINZA = 8, COR_AZUL_BASICO = 9, COR_VERDE_CLARO = 10;
const int COR_AZUL_CLARO = 11, COR_VERMELHO = 12, COR_ROSA = 13, COR_AMARELO = 14, COR_BRANCO = 15;

COORD posicaoDeInsercaoNoConsole()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleBuffer;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBuffer))
	{
		return consoleBuffer.dwCursorPosition;
	}
	else
	{
		return { 0, 0 };
	}
}

int larguraDoTerminal()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleBuffer;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleBuffer);
	
	int largura = consoleBuffer.srWindow.Right - consoleBuffer.srWindow.Left;
	return (largura);
}

int meioDoTerminal()
{
	return (larguraDoTerminal() / 2);
}

int quantidadeParaAlinharCentro(string texto)
{
	return (meioDoTerminal() - posicaoDeInsercaoNoConsole().X - (texto.size() / 2));
}

int quantidadeParaAlinharDireita(string texto)
{
	return (larguraDoTerminal() - posicaoDeInsercaoNoConsole().X - texto.size());
}

void preencherLinhaComCaractere(char caractere)
{
	cout << string(larguraDoTerminal(), caractere) << endl;
}

void preencherQuantidadeDeCaracteres(char caractere, int quantidade)
{
	cout << string(quantidade, caractere);
}

void escreverLinhaContinua()
{
	preencherLinhaComCaractere('-');
}

void escreverLinhaEspessa()
{
	preencherLinhaComCaractere('=');
}

void limparConteudo()
{
	system("cls");
}

void alterarCorTexto(int cor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

void redefinirCorTexto()
{
	alterarCorTexto(COR_PADRAO);
}

void alinharTextoCentro(string texto)
{
	preencherQuantidadeDeCaracteres(' ', quantidadeParaAlinharCentro(texto));
	cout << texto;
}

void alinharTextoDireita(string texto)
{
	preencherQuantidadeDeCaracteres(' ', quantidadeParaAlinharDireita(texto));
	cout << texto << endl;
}

void alinharTextoDireita(string texto, char pintarCaracter, int cor)
{
	preencherQuantidadeDeCaracteres(' ', quantidadeParaAlinharDireita(texto));
	for (int indice = 0; indice < texto.size(); indice++) {
		if (texto.at(indice) == pintarCaracter)
		{
			alterarCorTexto(cor);
			cout << texto.at(indice);
			redefinirCorTexto();
		}
		else {
			cout << texto.at(indice);
		}
	}
	cout << endl;
}

void pularLinha(int quantidade)
{
	if (quantidade > 0)
	{
		cout << endl;
		pularLinha(quantidade - 1);
	}
}

void limparBuffer()
{
	cin.seekg(0, ios::end); //Único jeito de descartar informações após espaço do cin (Stack Overflow: How do I flush the cin buffer?)
	cin.clear();
}

void pausar()
{
	cin.ignore();
	cin.get();
}