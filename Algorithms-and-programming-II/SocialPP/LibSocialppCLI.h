#pragma once
#include "LibCLI.h"
#include "LibSocialppEngine.h"
#include "LibSecret.h"
#include <Windows.h>
#include <string>
#include <iostream>

using namespace std;

const string TITULO_PROJETO = "--==[ SOCIAL++ ]==--";
const string ICONES_JANELA = "_ [] X";
const string IDENTIFICADOR_ABANDONO_PUBLICACAO = "!sair!";

const int ENTRAR = 1, CADASTRAR = 2, CADASTRO_AUTOMATICO = 3, LIMPAR_DADOS = 4, SAIR = 5;

const int NOVA_PUBLICACAO = 1, RETORNAR = 2;

void escreverEspacos(int quantidade)
{
	preencherQuantidadeDeCaracteres(' ', quantidade);
}

string marcarOpcaoDeGenero(string texto, bool marcar)
{
	string substituto;
	if (marcar)
		substituto = "X";
	else
		substituto = " ";
	return (texto.replace(texto.find('?'), 1, substituto));
}

void mostrarTituloProjeto()
{
	alterarCorTexto(COR_BRANCO);
	alinharTextoCentro(TITULO_PROJETO);
}

void mostrarIconesJanela()
{
	redefinirCorTexto();
	alinharTextoDireita(ICONES_JANELA, 'X', COR_VERMELHO);
}

void mostrarCabecalhoProjeto()
{
	alterarCorTexto(COR_PADRAO);
	escreverLinhaContinua();
	mostrarTituloProjeto();
	mostrarIconesJanela();
	escreverLinhaEspessa();
}

void escreverTextoDestacado(string texto, int cor)
{
	alterarCorTexto(cor);
	cout << texto;
	redefinirCorTexto();
}

void escreverTituloTela(string titulo, bool mostrarHorario = true)
{
	cout << endl;
	escreverTextoDestacado(titulo, COR_VERDE_CLARO);
	if (mostrarHorario)
		alinharTextoDireita(Agora().ParaTexto());
	redefinirCorTexto();
}

void escreverIdentificadorCadastro(string identificador)
{
	cout << endl;

	alterarCorTexto(COR_BRANCO);
	cout << identificador;

	redefinirCorTexto();
}

void mostrarCadastroNomeCompleto(Usuario usuario)
{
	escreverIdentificadorCadastro("+[Nome completo] :: ");
	cout << usuario.nome << endl;
}

void mostrarCadastroNomeUsuario(Usuario usuario)
{
	escreverIdentificadorCadastro("+[Usuário]       :: ");
	cout << usuario.nomeDeUsuario << endl;
}

void mostrarCadastroSenha(Usuario usuario)
{
	escreverIdentificadorCadastro("+[Senha]         :: ");
	cout << string(usuario.senha.size(), '*') << endl;
}

void mostrarCadastroNascimento(Usuario usuario)
{
	escreverIdentificadorCadastro("+[Nascimento]    :: ");
	cout << formatarTextoDeData(usuario.dataDeNascimento.dia, 'd', 2) + "/";
	cout << formatarTextoDeData(usuario.dataDeNascimento.mes , 'm', 2) + "/";
	cout << formatarTextoDeData(usuario.dataDeNascimento.ano, 'a', 4);
	if (usuario.idade() > 0) {
		cout << "  (" << usuario.idade() << " anos de idade)";
	}
	cout << endl;
}

void mostrarCadastroGenero(Usuario usuario)
{
	escreverIdentificadorCadastro("+[Gênero]        :: ");
	cout << marcarOpcaoDeGenero("[1] Masculino (?)", usuario.genero == "Masculino") << endl << string(20, ' ');
	cout << marcarOpcaoDeGenero("[2] Feminino  (?)", usuario.genero == "Feminino") << endl;
}

void mostrarRodapeTelaCadastro()
{
	cout << endl;
	escreverLinhaEspessa();
}

void mostrarSolicitacaoDeDados(string textoAuxiliar = "")
{
	alterarCorTexto(COR_VERDE_CLARO);
	cout << ">>Entrada de Dados";
	redefinirCorTexto();

	pularLinha(2);
	escreverTextoDestacado(textoAuxiliar, COR_BRANCO);
}

void mostrarTelaCadastro(Usuario usuario)
{
	limparConteudo();
	mostrarCabecalhoProjeto();
	escreverTituloTela("[+] Cadastrar Usuário");
	mostrarCadastroNomeCompleto(usuario);
	mostrarCadastroNomeUsuario(usuario);
	mostrarCadastroSenha(usuario);
	mostrarCadastroNascimento(usuario);
	mostrarCadastroGenero(usuario);
	mostrarRodapeTelaCadastro();
	pularLinha(1);
}

void solicitarNomeCompleto(Usuario &usuario)
{
	mostrarTelaCadastro(usuario);
	mostrarSolicitacaoDeDados("Nome completo -> ");
	cin.ignore();
	getline(cin, usuario.nome);
}

void solicitarNomeUsuario(Lista <Usuario> usuarios, Usuario &usuario)
{
	string mensagemErro = "";
	string nomeUsuarioTemporario = "";

	do {
		mostrarTelaCadastro(usuario);
		mostrarSolicitacaoDeDados();
		if (mensagemErro != "")
		{
			escreverTextoDestacado(mensagemErro, COR_VERMELHO);
			cout << endl << endl;
		}
		escreverTextoDestacado("Nome de Usuário -> ", COR_BRANCO);
		cin >> nomeUsuarioTemporario;
		nomeUsuarioTemporario = formatarNomeDeUsuario(nomeUsuarioTemporario);
		limparBuffer();
		mensagemErro = "Usuário já existente, informe outro! ";
	} while (usuarioJaExiste(usuarios, nomeUsuarioTemporario));
		
	usuario.nomeDeUsuario = nomeUsuarioTemporario;
}

bool solicitarSenhaUsuarioConfirmacao(string senha)
{
	escreverTextoDestacado("Confirme sua senha -> ", COR_BRANCO);

	string aux;
	getline(cin, aux);

	return (senha == aux);
}

void solicitarSenhaUsuario(Usuario &usuario)
{
	string senha = "";
	string mensagemErro = "";

	do {
		mostrarTelaCadastro(usuario);
		mostrarSolicitacaoDeDados();
		if (mensagemErro != "")
		{
			escreverTextoDestacado(mensagemErro, COR_VERMELHO);
			cout << endl << endl;
		}
		escreverTextoDestacado("Insira uma senha -> ", COR_BRANCO);
		getline(cin, senha);
		mensagemErro = "Senhas não correspondem! Tente novamente.";
	} while (!solicitarSenhaUsuarioConfirmacao(senha));

	usuario.senha = senha;
}

void solicitarGenero(Usuario &usuario)
{
	int genero = 0;
	string mensagemErro = "";

	while (!validarGenero(genero)) {
		mostrarTelaCadastro(usuario);
		mostrarSolicitacaoDeDados();
		if (mensagemErro != "")
		{
			escreverTextoDestacado(mensagemErro, COR_VERMELHO);
			cout << endl << endl;
		}
		escreverTextoDestacado("Índice do gênero -> ", COR_BRANCO);
		cin >> genero;
		mensagemErro = "Gênero inválido! Tente novamente.";
	}

	usuario.genero = generoPorIndice(genero);
}

void solicitarAno(Usuario &usuario)
{
	int ano = 0;
	string mensagemErro = "";

	while (!validarAno(ano)) {
		mostrarTelaCadastro(usuario);
		mostrarSolicitacaoDeDados();
		if (mensagemErro != "")
		{
			escreverTextoDestacado(mensagemErro, COR_VERMELHO);
			cout << endl << endl;
		}
		escreverTextoDestacado("Data de Nascimento :: Ano -> ", COR_BRANCO);
		cin >> ano;
		mensagemErro = "Ano inválido! Tente novamente.";
	}
	usuario.dataDeNascimento.ano = ano;
}

void solicitarMes(Usuario &usuario)
{
	int mes = 0;
	string mensagemErro = "";

	while (!validarMes(mes)) {
		mostrarTelaCadastro(usuario);
		mostrarSolicitacaoDeDados();
		if (mensagemErro != "")
		{
			escreverTextoDestacado(mensagemErro, COR_VERMELHO);
			cout << endl << endl;
		}
		escreverTextoDestacado("Data de Nascimento :: Mês -> ", COR_BRANCO);
		cin >> mes;
		mensagemErro = "Mês inválido! Tente novamente.";
	}
	usuario.dataDeNascimento.mes = mes;
}

void solicitarDia(Usuario &usuario)
{
	int dia = 0;
	string mensagemErro = "";

	while (!validarDia(dia, usuario.dataDeNascimento.mes, usuario.dataDeNascimento.ano)) {
		mostrarTelaCadastro(usuario);
		mostrarSolicitacaoDeDados();
		if (mensagemErro != "")
		{
			escreverTextoDestacado(mensagemErro, COR_VERMELHO);
			cout << endl << endl;
		}
		escreverTextoDestacado("Data de Nascimento :: Dia -> ", COR_BRANCO);
		cin >> dia;
		mensagemErro = "Dia inválido! Tente novamente.";
	}
	usuario.dataDeNascimento.dia = dia;
}

void cadastrarDataDeNascimento(Usuario &usuario)
{
	string mensagemDeErro = "";
	while(!validarIdade(usuario.idade()))
	{
		if (mensagemDeErro != "")
		{
			mostrarTelaCadastro(usuario);
			mostrarSolicitacaoDeDados();
			escreverTextoDestacado(mensagemDeErro, COR_VERMELHO);
			usuario.dataDeNascimento.redefinir();
			pausar();
		}
		solicitarAno(usuario);
		solicitarMes(usuario);
		solicitarDia(usuario);
		mensagemDeErro = "Você não pode cadastrar-se sendo menor de idade, por favor, insira uma data válida.";
	}
}

void alertarUsuarioSobreCadastro(Usuario &usuario)
{
	mostrarTelaCadastro(usuario);
	escreverTextoDestacado(">>Processo concluído!!! O usuário está cadastrado em nosso sistema. Aproveite!", COR_AZUL_CLARO);
	pausar();
}

void mostrarCadastroNovoUsuario(Lista<Usuario> &usuarios)
{
	Usuario novoUsuario;

	solicitarNomeCompleto(novoUsuario);
	solicitarNomeUsuario(usuarios, novoUsuario);
	solicitarSenhaUsuario(novoUsuario);
	cadastrarDataDeNascimento(novoUsuario);
	solicitarGenero(novoUsuario);
	usuarios.AdicionarElemento(novoUsuario);
	alertarUsuarioSobreCadastro(novoUsuario);
}

void mostrarUsuarioAutenticado(Usuario usuario)
{
	escreverTextoDestacado("[Usuário] : ", COR_BRANCO);
	cout << usuario.nome << " (" << usuario.nomeDeUsuario << ")" << endl << endl;
}

void mostrarAvisoFeedNoticias(string textoAviso)
{
	escreverTextoDestacado("[Aviso] ", COR_AMARELO);
	escreverTextoDestacado(textoAviso, COR_BRANCO);
	pularLinha(1);
}

void mostrarTituloFeedNoticias()
{
	mostrarCabecalhoProjeto();
	escreverTituloTela("[+] Feed de Notícias");
	pularLinha(1);
}

void mostrarMarcacoesFeedNoticias(Lista<string> usuarios)
{
	int maximoUsuarioPorLinha = 3, contarUsuarioPorLinha = 0;
	if (usuarios.Contar() > 0) {
		for (int indice = 0; indice < usuarios.Contar(); indice++) {
			cout << usuarios.elemento[indice] << "; ";
			if (contarUsuarioPorLinha == maximoUsuarioPorLinha && usuarios.Contar() > maximoUsuarioPorLinha) {
				cout << endl << "              ";
			}
		}
	}
	else {
		cout << "Nenhuma marcação";
	}
	
	pularLinha(1);
}

void mostrarMarcacaoFeedNoticias(Publicacao publicacao)
{
	escreverTextoDestacado("  [Marcações] ", COR_BRANCO);
	mostrarMarcacoesFeedNoticias(publicacao.marcacoes);
}

void mostrarConteudoPublicacaoFeedNoticias(Publicacao publicacao)
{
	escreverTextoDestacado("  [Conteúdo]  ", COR_BRANCO);
	cout << publicacao.conteudo << endl;
}

void mostrarPublicacaoFeedNoticias(Publicacao publicacao)
{
	//escreverLinhaContinua();
	escreverTextoDestacado("::" + publicacao.autor, COR_AZUL_CLARO);
	alinharTextoDireita("> " + publicacao.dataDeRegistro.ParaTexto());
	mostrarMarcacaoFeedNoticias(publicacao);
	mostrarConteudoPublicacaoFeedNoticias(publicacao);
	//pularLinha(1);
	//escreverLinhaContinua();
	pularLinha(1);
}

void mostrarRodapeFeedNoticias()
{
	pularLinha(1);
	escreverLinhaEspessa();
}

void mostrarPublicacoesFeedNoticias(SocialppBase baseSocialpp)
{
	if (baseSocialpp.possuiPostagem()) {
		for (int indice = baseSocialpp.feedDeNoticias.Contar() - 1; indice >= 0; indice--)
			mostrarPublicacaoFeedNoticias(baseSocialpp.feedDeNoticias.elemento[indice]);
		mostrarAvisoFeedNoticias("Não há mais publicações disponíveis =)");
	}
	else {
		mostrarAvisoFeedNoticias("Ainda não há nenhuma publicação disponível :-(");
	}
}

void mostrarTelaFeedNoticias(SocialppBase baseSocialpp, Usuario usuarioAtivo)
{
	limparConteudo();
	mostrarTituloFeedNoticias();
	mostrarUsuarioAutenticado(usuarioAtivo);
	mostrarPublicacoesFeedNoticias(baseSocialpp);
	mostrarRodapeFeedNoticias();
}

void escreverOpcaoFeedNoticias(string opcaoNome)
{
	escreverTextoDestacado(opcaoNome, COR_BRANCO);
	pularLinha(1);
}

void escreverOpcoesFeedNoticias()
{
	pularLinha(1);
	escreverTextoDestacado(">>Escolha uma opção de interação.", COR_VERDE_CLARO);
	pularLinha(2);
	escreverOpcaoFeedNoticias("[1] - Nova publicação.");
	escreverOpcaoFeedNoticias("[2] - Efetuar logout.");
	pularLinha(1);
}

int lerOpcaoFeedNoticias(SocialppBase &baseSocialpp, Usuario *usuarioAtivo)
{
	int opcao = 0;
	string mensagemErro = "";
	do {
		mostrarTelaFeedNoticias(baseSocialpp, *usuarioAtivo);
		if (mensagemErro != "")
		{
			pularLinha(1);
			escreverTextoDestacado(mensagemErro, COR_VERMELHO);
			pularLinha(1);
		}
		escreverOpcoesFeedNoticias();
		escreverTextoDestacado("Sua opção -> ", COR_BRANCO);
		cin >> opcao;
		limparBuffer();
		mensagemErro = "Opção inválida!";
	} while (opcao != NOVA_PUBLICACAO && opcao != RETORNAR);
	return (opcao);
}

void mostrarTituloNovaPublicacao()
{
	mostrarCabecalhoProjeto();
	escreverTituloTela("[+] Escrever nova publicação");
	pularLinha(1);
}

void mostrarRequisitosPublicacao()
{
	escreverTextoDestacado("[1] > Sua publicação pode conter até 280 caracteres.", COR_AMARELO);
	pularLinha(2);
	escreverTextoDestacado("[2] > Você pode marcar usuários utilizando @nomeDeUsuario.", COR_AMARELO);
	pularLinha(2);
	escreverTextoDestacado("[3] > Todos os usuários marcados devem existir.", COR_AMARELO);
	pularLinha(2);
	escreverTextoDestacado("[4] > Você pode inserir !sair! em seu texto para cancelar a publicação.", COR_AMARELO);
	pularLinha(2);
}

void mostrarTelaNovaPublicacao(Usuario usuarioAtivo)
{
	limparConteudo();
	mostrarTituloNovaPublicacao();
	mostrarUsuarioAutenticado(usuarioAtivo);
	mostrarRequisitosPublicacao();
}

bool usuarioSolicitouSaida(string conteudoTexto)
{
	bool solicitacao = false;
	if (conteudoTexto.length() >= IDENTIFICADOR_ABANDONO_PUBLICACAO.length()){
		int indice = conteudoTexto.find(IDENTIFICADOR_ABANDONO_PUBLICACAO);
		if (indice > -1) {
			solicitacao = true;
		}
	}
	return (solicitacao);
}

string solicitarNovaPublicacao(SocialppBase &baseSocialpp, Usuario *usuarioAtivo, bool mostrarErro280Caracteres, bool mostrarErroMarcacao)
{
	string conteudoPublicacao = "";

	mostrarTelaNovaPublicacao(*usuarioAtivo);

	if (mostrarErro280Caracteres)
	{
		escreverTextoDestacado("Você inseriu mais do que 280 caracteres!", COR_VERMELHO);
		pularLinha(1);
	}
	if (mostrarErroMarcacao)
	{
		escreverTextoDestacado("Algum usuário marcado não existe!", COR_VERMELHO);
		pularLinha(1);
	}
	
	pularLinha(1);
	escreverTextoDestacado("Texto da publicação -> ", COR_AZUL_CLARO);

	getline(cin, conteudoPublicacao);
	return (conteudoPublicacao);
}

void iniciarNovaPublicacao(SocialppBase &baseSocialpp, Usuario *usuarioAtivo)
{
	string novaPublicacao = "";
	bool erroContemAte280 = false, erroTodosUsuariosExistem = false, usuarioCancelouInsercao = false;
	do {
		novaPublicacao = solicitarNovaPublicacao(baseSocialpp, usuarioAtivo, erroContemAte280, erroTodosUsuariosExistem);
		erroContemAte280 = !validarTamanhoPublicacao(novaPublicacao);
		erroTodosUsuariosExistem = !todosUsuariosExistem(baseSocialpp.usuarios, novaPublicacao);
		usuarioCancelouInsercao = usuarioSolicitouSaida(novaPublicacao);
	} while (!validarPublicacao(baseSocialpp.usuarios, novaPublicacao) && !usuarioCancelouInsercao);
	if (!usuarioCancelouInsercao) {
		Publicacao publicacao(usuarioAtivo->nome + " (" + usuarioAtivo->nomeDeUsuario + ")", novaPublicacao, identificarUsuariosMarcados(novaPublicacao), Agora());
		baseSocialpp.feedDeNoticias.AdicionarElemento(publicacao);
		usuarioAtivo->publicacao.AdicionarElemento(publicacao);
		pularLinha(1);
		escreverTextoDestacado("A sua publicação foi realizada com sucesso!", COR_VERDE_CLARO);
		Sleep(500);
	}
	else {
		pularLinha(1);
		escreverTextoDestacado("Operação abortada!", COR_VERMELHO);
		Sleep(500);
	}
}

int solicitarOpcaoFeedNoticias(SocialppBase &baseSocialpp, Usuario* usuarioAtivo)
{
	int opcao = lerOpcaoFeedNoticias(baseSocialpp, usuarioAtivo);
	switch (opcao) {
	case NOVA_PUBLICACAO:
		iniciarNovaPublicacao(baseSocialpp, usuarioAtivo);
		break;
	case RETORNAR:
		break;
	}
	return (opcao);
}

void iniciarFeedNoticias(SocialppBase &baseSocialpp, Usuario* usuario)
{
	int opcao = 0;
	do {
		opcao = solicitarOpcaoFeedNoticias(baseSocialpp, usuario);
	} while (opcao != RETORNAR);
}

void mostrarSubtituloTelaAutenticacao()
{
	cout << endl;
	escreverTextoDestacado(">>Utilize suas credenciais para realizar login.", COR_AZUL_CLARO);
	cout << endl << endl;
}

void escreverIndiceTelaAutenticacao(string nomeDoIndice)
{
	escreverTextoDestacado(nomeDoIndice, COR_BRANCO);
}

void mostrarTelaAutenticacao()
{
	limparConteudo();
	mostrarCabecalhoProjeto();
	escreverTituloTela("[+] Entrar na sua conta / Autentificar");
	mostrarSubtituloTelaAutenticacao();
}

void solicitarCredenciais(string &nome, string &senha)
{
	escreverIndiceTelaAutenticacao("[!] USUÁRIO -> ");
	cin >> nome;
	nome = formatarNomeDeUsuario(nome);
	limparBuffer();
	escreverIndiceTelaAutenticacao("[!] SENHA   -> ");
	getline(cin, senha);
}

void iniciarProcessoAutenticacao(SocialppBase &baseSocialpp)
{
	string usuarioNome = "", usuarioSenha = "", mensagemErro = "";
	int quantidadeDeTentativa = 3, processoAutenticacao = 0;

	do {
		mostrarTelaAutenticacao();
		if (mensagemErro != "") {
			escreverTextoDestacado(mensagemErro, COR_VERMELHO);
			pularLinha(2);
			escreverTextoDestacado("Tentativas restantes : " + to_string(quantidadeDeTentativa), COR_CINZA);
			pularLinha(2);
		}
		solicitarCredenciais(usuarioNome, usuarioSenha);
		processoAutenticacao = autenticarUsuario(baseSocialpp.usuarios, usuarioNome, usuarioSenha);
		mensagemErro = erroAutenticacaoPorIndice(processoAutenticacao);
		if (processoAutenticacao == AUTENTICACAO_SUCESSO) {
			if (usuarioNome == nomeUsuarioAnomalous)
				mostrarEasterEgg();
			iniciarFeedNoticias(baseSocialpp, pegarUsuarioPeloID(baseSocialpp.usuarios, usuarioNome));
		}
		quantidadeDeTentativa--;
	} while (quantidadeDeTentativa > 0 && (processoAutenticacao != AUTENTICACAO_SUCESSO));
}

void carregarPessoasPreDefinidas(SocialppBase &baseSocialpp)
{
	carregarUsuario(baseSocialpp.usuarios, "Jose Carlos Zancanaro", "Jose", "1234jose", "Masculino", valorData(23, 6, 1999));
	carregarUsuario(baseSocialpp.usuarios, "Lucas Cardone", "Luca", "1234luca", "Masculino", valorData(02, 12, 1996));
	carregarUsuario(baseSocialpp.usuarios, "Gabriel Schade Cardoso", "Schade", "1234schade", "Masculino", valorData(12, 11, 1990));
	carregarUsuario(baseSocialpp.usuarios, "Anomalous", "avaliacao", "123", "Masculino", valorData(27, 8, 1999));
	realizarPublicacao(baseSocialpp, "Jose", "Boa noite, professor @Schade ! Poderias acessar com o usuário @avaliacao ?");
	realizarPublicacao(baseSocialpp, "Luca", "Usuário @avaliacao e senha: 123");
	realizarPublicacao(baseSocialpp, "Schade", "@Luca @Jose Ok, acessarei de acordo.");
}

void carregarBasePreDefinida(SocialppBase &baseSocialpp)
{
	carregarPessoasPreDefinidas(baseSocialpp);
	Usuario *usuarioParaAutenticar = pegarUsuarioPeloID(baseSocialpp.usuarios, "@Schade");
	iniciarFeedNoticias(baseSocialpp, usuarioParaAutenticar);
}

void redefinirBaseDeDados(SocialppBase &baseSocialpp)
{
	baseSocialpp.usuarios.Redefinir();
	baseSocialpp.feedDeNoticias.Redefinir();
	pularLinha(1);
	escreverTextoDestacado("Os dados foram redefinidos!", COR_AZUL_CLARO);
	Sleep(1000);
}

void escreverIndiceMenuPrincipal(string nomeDaOpcao)
{
	escreverTextoDestacado(nomeDaOpcao, COR_BRANCO);
	cout << endl;
}

void escreverSubtituloMenuPrincipal()
{
	cout << endl;
	escreverTextoDestacado(">>Bem vindo! Escolha uma das opções abaixo:", COR_AZUL_CLARO);
	cout << endl << endl;
}

void escreverOpcoesMenuPrincipal()
{
	escreverIndiceMenuPrincipal("[1] - Entrar.");
	escreverIndiceMenuPrincipal("[2] - Cadastrar.");
	escreverIndiceMenuPrincipal("[3] - Carregar cadastro automático.");
	escreverIndiceMenuPrincipal("[4] - Limpar base de dados.");
	escreverIndiceMenuPrincipal("[5] - Sair.");
}

int opcaoEscolhida()
{
	int valor = 0;
	escreverTextoDestacado("\n>>Escolha uma opção -> ", COR_AZUL_CLARO);
	cin >> valor;
	return valor;
}

void mostrarMenuPrincipal()
{
	limparConteudo();
	mostrarCabecalhoProjeto();
	escreverTituloTela("[+] Menu Principal");
	escreverSubtituloMenuPrincipal();
	escreverOpcoesMenuPrincipal();
}

int solicitarOpcaoAoUsuario(SocialppBase &baseSocialpp)
{
	int opcao = 0;
	mostrarMenuPrincipal();
	opcao = opcaoEscolhida();
	switch (opcao)
	{
	case ENTRAR:
		iniciarProcessoAutenticacao(baseSocialpp);
		break;
	case CADASTRAR:
		mostrarCadastroNovoUsuario(baseSocialpp.usuarios);
		break;
	case CADASTRO_AUTOMATICO:
		carregarBasePreDefinida(baseSocialpp);
		break;
	case LIMPAR_DADOS:
		redefinirBaseDeDados(baseSocialpp);
		break;
	case SAIR:
		break;
	default:
		break;
	}
	return opcao;
}

void mostrarOpcoes(SocialppBase &baseSocialpp)
{
	int escolha = 0;
	do {
		escolha = solicitarOpcaoAoUsuario(baseSocialpp);
	} while (escolha != SAIR);
}

void executarRedeSocialCLI()
{
	SocialppBase baseSocialpp;
	mostrarOpcoes(baseSocialpp);
}