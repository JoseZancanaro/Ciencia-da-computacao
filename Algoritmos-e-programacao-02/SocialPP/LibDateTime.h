#pragma once
#include <string>
#include <time.h>

using namespace std;

template<typename T>
string preencherNaEsquerda(T base, char caractereParaPreencher, int quantidadeDeCaracteres)
{
	string texto = to_string(base);

	int tamanhoDoTexto = static_cast<int>(texto.size());
	if (tamanhoDoTexto > quantidadeDeCaracteres)
		tamanhoDoTexto = quantidadeDeCaracteres;

	string textoAjustado = string(quantidadeDeCaracteres - tamanhoDoTexto, caractereParaPreencher) + texto;

	return (textoAjustado);
}

string formatarTextoDeData(int base, char caractereCasoNulo, int quantidadeDeCaracteres)
{
	string valorTemporario = "";

	if (base == 0)
		valorTemporario = string(quantidadeDeCaracteres, caractereCasoNulo);
	else if (to_string(base).size() < quantidadeDeCaracteres)
		valorTemporario = preencherNaEsquerda<int>(base, '0', quantidadeDeCaracteres);
	else
		valorTemporario = to_string(base);

	return (valorTemporario);
}

struct Hora
{
	int hora = 0;
	int minuto = 0;
	string paraTexto()
	{
		return (formatarTextoDeData(hora, '0', 2) + ":" + formatarTextoDeData(minuto, '0', 2));
	}
};

struct Data
{
	int dia = 0;
	int mes = 0;
	int ano = 0;
	string paraTexto()
	{
		return (formatarTextoDeData(dia, '0', 2) + "/" + formatarTextoDeData(mes, '0', 2) + "/" + formatarTextoDeData(ano, '0', 4));
	}
	void redefinir()
	{
		dia = 0;
		mes = 0;
		ano = 0;
	}
};

Data valorData(int dia, int mes, int ano)
{
	Data dataParaRetorno;
	dataParaRetorno.dia = dia;
	dataParaRetorno.mes = mes;
	dataParaRetorno.ano = ano;
	return (dataParaRetorno);
}

struct DataHora
{
	Data data;
	Hora horario;
	string ParaTexto()
	{
		return (data.paraTexto() + " " + horario.paraTexto());
	}
};

int encontrarUltimoDia(int mes, int ano)
{
	if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
	{
		return 30;
	}
	else {
		if (mes == 2) {
			if (ano % 4 == 0 && (ano % 100 != 0 || (ano % 100 == 0 && ano % 400 == 0 && ano > 1582) || (ano <= 1582 && ano % 100 == 0)))
				return 29;
			else
				return 28;
		}
		else
			return 31;
	}
}

int contarDia(int dia, int mes, int ano)
{
	//José Zancanaro:
	//No dia 4 de outubro de 1582, foram omitidos 10 dias do calendário, portanto
	//não devemos considerar os dias entre 4 e 15.
	if (ano == 1582 && mes == 10 && (dia > 4 && dia < 15))
	{
		return 0;
	}
	else {
		return 1;
	}
}

int quantidadeDeDiasAteData(int diaAlvo, int mesAlvo, int anoAlvo)
{
	int quantidade = 0;
	for (int ano = 1; ano <= anoAlvo; ano++) {
		for (int mes = 1; (ano != anoAlvo && mes <= 12) || (ano == anoAlvo && mes <= mesAlvo); mes++) {
			for (int dia = 1; (ano != anoAlvo && mes <= 12 && dia <= encontrarUltimoDia(mes, ano))
				|| (ano == anoAlvo && mes <= mesAlvo && ((mes == mesAlvo && dia <= diaAlvo) || mes != mesAlvo && dia <= encontrarUltimoDia(mes, ano))); dia++)
				quantidade += contarDia(dia, mes, ano);
		}
	}
	return quantidade;
}

DataHora Agora()
{
	DataHora dataTemporaria;

	time_t tempo; time(&tempo);
	tm agora; localtime_s(&agora, &tempo);

	/*Atribuir data*/
	dataTemporaria.data.dia = agora.tm_mday;
	dataTemporaria.data.mes = agora.tm_mon + 1;
	dataTemporaria.data.ano = agora.tm_year + 1900;

	/*Atribuir horário*/
	dataTemporaria.horario.hora = agora.tm_hour;
	dataTemporaria.horario.minuto = agora.tm_min;

	return (dataTemporaria);
}

int diferencaEmAnos(Data dataFinal, Data dataInicial) {
	int anos = dataFinal.ano - dataInicial.ano;
	if (dataFinal.mes < dataInicial.mes ||
		(dataFinal.mes == dataInicial.mes && dataFinal.dia < dataInicial.dia)
		) {
		anos--;
	}
	return (anos);
}