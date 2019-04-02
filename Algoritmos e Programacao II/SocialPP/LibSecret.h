#pragma once
#include "LibCLI.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

const string anomalous[8] =
{
	"       /\\       ",
	"      /  \\      ",
	"     /    \\     ",
	"    / ,--. \\    ",
	"   / < () > \\   ",
	"  /   `--'   \\  ",
	" /            \\ ",
	"/______________\\"
};

const string nomeUsuarioAnomalous = "@avaliacao";

void mostrarTextoEasterEgg(string texto, int atraso)
{
	cout << string(quantidadeParaAlinharCentro(texto), ' ');
	for (int i = 0; i < texto.length(); i++) {
		cout << texto.at(i);
		Sleep(atraso);
	}
	pularLinha(1);
}

void mostrarEasterEggFinalizacao()
{
	pularLinha(2);
	mostrarTextoEasterEgg("Boas festas e nos vemos em breve!", 40);
}

void mostrarEasterEggAguardar()
{
	pularLinha(1);
	mostrarTextoEasterEgg("Please wait while we hack your profile...", 50);
	Sleep(1000);
}

void mostrarEasterEggBinarios(int segundos = 4)
{
	clock_t inicio = clock();
	while (double(clock() - inicio) / CLOCKS_PER_SEC < segundos) {
		cout << rand() % 2 << "\t";
	}
}

void mostrarEasterEggHorus()
{
	pularLinha(2);
	for (int i = 0; i < 8; i++) {
		alinharTextoCentro(anomalous[i]);
		pularLinha(1);
	}
}

void mostrarEasterEggHino()
{
	mostrarTextoEasterEgg("We are a region", 50);
	mostrarTextoEasterEgg("Forgive and forgot", 50);
	mostrarTextoEasterEgg("And expecto patronum!", 50);
}

void mostrarEasterEggTitulo()
{
	escreverLinhaContinua();
	alinharTextoCentro("--==[ WE ARE ANOMALOUS ]==--");
	pularLinha(1);
	escreverLinhaEspessa();
	pularLinha(2);
}

void mostrarEasterEgg()
{
	limparConteudo();
	alterarCorTexto(COR_VERDE_CLARO);
	mostrarEasterEggTitulo();
	mostrarEasterEggHino();
	mostrarEasterEggHorus();
	mostrarEasterEggAguardar();
	mostrarEasterEggBinarios();
	mostrarEasterEggFinalizacao();
	pausar();
}