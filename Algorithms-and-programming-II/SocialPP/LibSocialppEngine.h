#pragma once
#include "LibArray.h"
#include "LibDateTime.h"
#include <iostream>
#include <string>

using namespace std;

const int MASCULINO = 1, FEMININO = 2;
const int AUTENTICACAO_SUCESSO = 1, AUTENTICACAO_USUARIO_INEXISTE = 2, AUTENTICACAO_SENHA_INCORRETA = 3;

const int LIMITE_TAMANHO_PUBLICACAO = 280;

struct Publicacao
{
	string autor;
	string conteudo;
	Lista<string> marcacoes;
	DataHora dataDeRegistro;

	Publicacao()
	{}

	Publicacao(string autor, string conteudo, Lista<string> marcacoes, DataHora dataDeRegistro):
		autor(autor), conteudo(conteudo), marcacoes(marcacoes), dataDeRegistro(dataDeRegistro)
	{}
};

struct Usuario
{
	string nome;
	string nomeDeUsuario;
	string senha;
	string genero;
	Data dataDeNascimento;

	int idade()
	{
		int idadeParaRetorno = 0;

		if (dataDeNascimento.dia > 0 && dataDeNascimento.mes > 0 && dataDeNascimento.ano > 0)
		{
			idadeParaRetorno = diferencaEmAnos(Agora().data, dataDeNascimento);
		}
		
		return (idadeParaRetorno);
	}

	Lista<Publicacao> publicacao;

	Usuario()
	{}

	Usuario(string nome, string nomeDeUsuario, string senha, string genero, Data dataDeNascimento) :
		nome(nome), nomeDeUsuario(nomeDeUsuario), senha(senha),
		genero(genero), dataDeNascimento(dataDeNascimento)
	{}
};

struct SocialppBase
{
	Lista<Usuario> usuarios;
	Lista<Publicacao> feedDeNoticias;
	bool possuiPostagem()
	{
		return (feedDeNoticias.Contar() > 0);
	}

};

bool validarDia(int dia, int mes, int ano)
{
	return (dia > 0 && dia <= encontrarUltimoDia(mes, ano));
}

bool validarDia(Data validar)
{
	return (validarDia(validar.dia, validar.mes, validar.ano));
}

bool validarMes(int mes)
{
	return (mes > 0 && mes <= 12);
}

bool validarAno(int ano)
{
	return (ano >= 1905 && ano <= 1999);
}

bool validarGenero(int indiceGenero)
{
	return (indiceGenero == 1 || indiceGenero == 2);
}

bool validarIdade(int idade)
{
	return (idade >= 18);
}

bool usuarioJaExiste(Lista<Usuario> lista, string nomeDeUsuario)
{
	bool usuarioEncontrado = false;
	for (int indice = 0; indice < lista.quantidadeDeElementos && !usuarioEncontrado; indice++)
	{
		if (nomeDeUsuario == lista.elemento[indice].nomeDeUsuario)
		{
			usuarioEncontrado = true;
		}
	}
	return (usuarioEncontrado);
}

Usuario *pegarUsuarioPeloID(Lista<Usuario> lista, string nomeDeUsuario)
{
	Usuario *usuarioEncontrado = NULL;
	bool pararLoop = false;
	for (int indice = 0; indice < lista.quantidadeDeElementos && !pararLoop; indice++)
	{
		if (nomeDeUsuario == lista.elemento[indice].nomeDeUsuario)
		{
			usuarioEncontrado = &lista.elemento[indice];
			pararLoop = true;
		}
	}
	return (usuarioEncontrado);
}

string formatarNomeDeUsuario(string nomeDeUsuario)
{
	if (nomeDeUsuario.substr(0, 1) != "@")
		return ("@" + nomeDeUsuario);
	else
		return (nomeDeUsuario);
}

string generoPorIndice(int genero)
{
	switch (genero)
	{
	case MASCULINO:
		return "Masculino";
		break;
	case FEMININO:
		return "Feminino";
		break;
	default:
		return "";
		break;
	}
}

string erroAutenticacaoPorIndice(int indice)
{
	switch (indice)
	{
	case AUTENTICACAO_SENHA_INCORRETA:
		return ("Combinação de usuário/senha está incorreta!");
		break;
	case AUTENTICACAO_USUARIO_INEXISTE:
		return("Usuário não está cadastrado!");
		break;
	default:
		return ("");
		break;
	}
}

int autenticarUsuario(Lista<Usuario> usuarios, string usuario, string senha)
{
	int processoAutenticacao = 0;
	if (usuarioJaExiste(usuarios, usuario)) {
		if (senha == pegarUsuarioPeloID(usuarios, usuario)->senha)
		{
			processoAutenticacao = AUTENTICACAO_SUCESSO;
		}
		else {
			processoAutenticacao = AUTENTICACAO_SENHA_INCORRETA;
		}
	}
	else {
		processoAutenticacao = AUTENTICACAO_USUARIO_INEXISTE;
	}
	return (processoAutenticacao);
}

int acharFimCadeia(string texto, char eosChar)
{
	int indice = texto.find(eosChar) - 1;
	if (indice > -1)
	{
		return (texto.find(eosChar));
	}
	else {
		return (texto.length());
	}
}

bool existeUsuarioEmString(string conteudoTexto)
{
	int indiceIdentificadorUsuario = conteudoTexto.find('@');
	return (indiceIdentificadorUsuario > -1);
}

string extrairProximoUsuario(string &texto)
{
	string usuarioParaRetorno = "";

	int indiceInicio = 0, indiceFim = 0;
	indiceInicio = texto.find('@');
	indiceFim = acharFimCadeia(texto.substr(indiceInicio, texto.length()), ' ');

	usuarioParaRetorno = texto.substr(indiceInicio, indiceFim);
	texto = texto.substr(indiceFim + indiceInicio, texto.length());

	return (usuarioParaRetorno);
}

Lista<string> identificarUsuariosMarcados(string conteudoTexto)
{
	Lista<string> usuariosMarcados;
	while (existeUsuarioEmString(conteudoTexto)) {
		usuariosMarcados.AdicionarElemento(extrairProximoUsuario(conteudoTexto));
	}
	return (usuariosMarcados);
}

bool todosUsuariosExistem(Lista<Usuario> usuarios, string conteudoTexto)
{
	Lista<string> nomesDeUsuario = identificarUsuariosMarcados(conteudoTexto);
	bool todosExistem = true;
	for (int indice = 0; indice < nomesDeUsuario.Contar() && todosExistem; indice++)
		todosExistem = usuarioJaExiste(usuarios, nomesDeUsuario.elemento[indice]);
	return (todosExistem);
}

bool validarTamanhoPublicacao(string conteudoTexto)
{
	return (conteudoTexto.length() <= LIMITE_TAMANHO_PUBLICACAO);
}

bool validarPublicacao(Lista<Usuario> usuarios, string conteudoTexto)
{
	return (todosUsuariosExistem(usuarios, conteudoTexto) && validarTamanhoPublicacao(conteudoTexto) && conteudoTexto.length() > 0);
}

void carregarUsuario(Lista<Usuario> &usuario, string nome, string nomeDeUsuario, string senha, string genero, Data dataDeNascimento)
{
	Usuario usuarioBase(nome, formatarNomeDeUsuario(nomeDeUsuario), senha, genero, dataDeNascimento);
	usuario.AdicionarElemento(usuarioBase);
}

void realizarPublicacao(SocialppBase &baseSocialpp, string nomeDeUsuario, string conteudoTexto)
{
	Usuario *usuario = pegarUsuarioPeloID(baseSocialpp.usuarios, formatarNomeDeUsuario(nomeDeUsuario));
	Publicacao publicacao(usuario->nome + " (" + usuario->nomeDeUsuario + ")", conteudoTexto, identificarUsuariosMarcados(conteudoTexto), Agora());
	usuario->publicacao.AdicionarElemento(publicacao);
	baseSocialpp.feedDeNoticias.AdicionarElemento(publicacao);
}