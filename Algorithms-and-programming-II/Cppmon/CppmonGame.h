#pragma once
#ifndef CppmonGame_h

#include <Windows.h>
#include <iostream>
#include <string>

#include <cstdlib>
#include <ctime>

#include <math.h>

using namespace std;

/*
Opções menu principal
*/
const int OPCAO_NOVO_JOGO = 1, OPCAO_SAIR = 2, OPCAO_EASTER_EGG = 666;

/*
Método de escolha dos monstros
*/
const int METODO_ANALISE = 1, METODO_SORTE = 2;													//Seleção geral
const int METODO_ESCOLHA = 1, METODO_SORTEIO = 2;												//Cada jogador

/*
Motivos de fim de jogo
*/

const int  MOTIVO_DERROTA = -1, MOTIVO_NAN = 0, MOTIVO_VITORIA = 1;

/*
Constantes para definição do mapa
*/
const int DIMENSAO_LARGURA = 15, DIMENSAO_ALTURA = 15;
const int POSICAO_VAZIA = 0, POSICAO_JOGADOR = 1, POSICAO_CERCA = 2, POSICAO_ARENA = 3, POSICAO_INEXISTENTE = 999;
const int QUANTIDADE_CERCAS = 10;
const string STR_CERCA = " # ", STR_CENTRO = "CP ";

/*
Constantes para determinar parâmetros do jogo
*/
const int QUANTIDADE_JOGADORES = 6;																//Detalhes de JOGADORES
const int JOGADOR_PRINCIPAL = 0, OPONENTE_COMUM = 1, OPONENTE_LIDER = 2;
const int INDICE_JOGADOR = 0, INDICE_LIDER = QUANTIDADE_JOGADORES - 1;

const int QUANTIDADE_MONSTRO_DISP = 12;															//Detalhes de RECURSOS
const int QUANTIDADE_MONSTROS = 4;
const int QUANTIDADE_MONSTROS_POCKET = 2;
const int QUANTIDADE_HABILIDADES = 4;

/*
Constantes para realizar tipagem dos monstros
*/
const int FOGO = 0, AGUA = 1, GRAMA = 2, ELETRICO = 3, VOADOR = 4;								//Tipos
const int ATAQUE_ELEMENTAR = 0, ATAQUE_COMUM = 1, ATAQUE_RAPIDO = 2, SUPER_ATAQUE = 3;			//Habilidades

//Todas as Structs utilizadas.

struct Habilidade
{
	string nome;
	int poder;
	int tipo;
	int limite;
	int utilizou = 0;
	int saldo()
	{
		return (limite - utilizou);
	}
	bool disponivel()
	{
		return (limite > utilizou);
	}
};

struct Monster
{
	string nome;
	int tipo;
	int tipo_vantagem;
	int tipo_desvantagem;
	int vida;
	int ataque;
	int defesa;
	int velocidade;
	int level = 50;
	bool vivo()
	{
		return (vida > 0);
	}
	Habilidade habilidade[QUANTIDADE_HABILIDADES];
};

struct Capsula
{
	int identificador = -1;
	Monster monstro;
};

struct Posicao
{
	int linha = -1;
	int coluna = -1;
};

struct Jogador
{
	int tipo_jogador;
	int id;
	string cod;
	string nome;
	Capsula deck[4];
	Capsula pocket[2];
	Posicao posicao;
	bool derrotado = false;
	bool ativo = false;
};

struct CppmonMapa
{
	int regiao[DIMENSAO_ALTURA][DIMENSAO_LARGURA] = { POSICAO_VAZIA };
	Posicao centro;
};

struct CppmonJogo
{
	CppmonMapa mapa;
	Jogador jogadores[QUANTIDADE_JOGADORES];
	Monster lista_imagem[QUANTIDADE_MONSTRO_DISP] = {};
};

//Funções de estado do jogo

void iniciar_console();
void iniciar_novo_jogo();
int obter_acao_usuario(bool mostrar_animacao_login);
int obter_opcao_menu_inicial();
void mostrar_menu_inicial();
void configurar_novo_jogo(CppmonJogo& novoJogo);
bool fim_de_jogo(CppmonJogo& jogo);
int determinar_motivo_fim(CppmonJogo& jogo);
void finalizar_jogo(CppmonJogo& jogo);
void finalizar_vitoria();
void finalizar_derrota();

	/*--MODO MAPA--*/
void executar_novo_jogo(CppmonJogo& jogo);
void solicitar_acao_jogador(CppmonJogo& jogo, Jogador& jogador);
bool checar_possibilidade_x11(Jogador jogadores[]);
int determinar_indice_desafiador(Jogador jogadores[]);
void confirmar_inicio_batalha(Jogador& jogador_principal, Jogador& jogador_oponente);
string acao_no_j(CppmonMapa mapa, Jogador jogador);
void mostrar_opcoes_disponiveis_jogador(CppmonMapa mapa, Jogador& jogador);
bool opcao_jogador_valida(char opcao, CppmonJogo& jogo, Jogador& jogador);
bool movimentar_jogador(char opcao, CppmonMapa& mapa, Jogador& jogador);
void recuperar_grupo(Capsula itens[], Monster imagem[]);
void realizar_acao_oponentes(CppmonJogo& jogo);
void movimentar_jogador_oponente(CppmonMapa& mapa, Jogador& jogador, int forcar_seed = 0);
bool jogador_progrediu(CppmonJogo& jogo);

	/*--MODO BATALHA--*/
void iniciar_batalha(Jogador& jogador_principal, Jogador& jogador_oponente);
void emular_batalha(Jogador& jogador_principal, Jogador& jogador_oponente);
bool jogador_tem_mais_velocidade(Monster monstro_jogador, Monster monstro_oponente);
bool sorteia_impar();
void validar_monstro_ativo(Jogador& jogador, int& ativo, int& saldo);
void anunciar_nocaute(Monster monstro);
void apresentar_substituto(Monster monstro);
void atualizar_estados_monstros_deck(Jogador& jogador);
bool batalha_finalizou(Jogador jogador_principal, Jogador jogador_oponente);
int definir_vencedor_batalha(Jogador& jogador_principal, Jogador& jogador_oponente);
void escolher_monstros_combate(Jogador& jogador);
void sortear_monstros_oponente(Jogador& oponente);
int contar_monstros_vivos(Capsula lista[], int tamanho);
int contar_monstros_vivos_pocket(Capsula lista[]);
string reportar_monstros_vivos(Capsula pocket[]);
void exibir_status_monstros(Jogador jogador);
void exibir_status_monstros_jogadores(Jogador jogador_principal, Jogador jogador_oponente);
void exibir_informacoes_monstros(Jogador& jogador_principal, Jogador& jogador_oponente, int ativo_jogador, int ativo_oponente, int turno);
void listar_habilidades_monstro(Monster monstro);
void efetuar_ataque_jogador(Jogador& jogador_principal, Jogador& jogador_oponente, int ativo_jogador, int ativo_oponente);
int solicitar_habilidade_jogador(Monster monstro_jogador);
bool validar_habilidade(Monster monstro, int habilidade);
float definir_modificador(Monster monstro_atacante, Monster monstro_defensor);
float modificador_level_monstro(int level);
int quantificar_dano(Monster monstro_atacante, Monster monstro_defensor, int habilidade);
void infligir_dano(Monster& monstro_defensor, int dano);
void registrar_uso_habilidade(Habilidade& habilidade);
void reportar_acao_ataque(string nome_monstro, string nome_monstro_defensor, float dano);
void efetuar_habilidade_oponente(Jogador& jogador_principal, Jogador& jogador_oponente, int ativo_jogador, int ativo_oponente);
int sortear_habilidade_oponente(int tipo_jogador);
void escrever_escolha_habilidade(string nome_monstro, string nome_habilidade);

//Funções de mapa
int conferir_posicao_mapa(CppmonMapa mapa, int linha, int coluna);
int conferir_posicao_mapa(CppmonMapa mapa, Posicao posicao);
void definir_valor_no_mapa(CppmonMapa& mapa, int valor, int linha, int coluna, bool ignorar_validacao = false);
void definir_valor_no_mapa(CppmonMapa& mapa, int valor, Posicao posicao, bool ignorar_validacao = false);
bool posicao_disponivel(CppmonMapa mapa, int linha, int coluna);
bool posicao_disponivel(CppmonMapa mapa, Posicao posicao);
Posicao posicao_disponivel_aleatorio(CppmonMapa mapa);
void posicionar_cercas(CppmonMapa& mapa, int indice);
void posicionar_arena(CppmonMapa& mapa);
void posicionar_jogador(CppmonMapa& mapa, Jogador& jogador, int linha, int coluna);
void posicionar_jogador(CppmonMapa& mapa, Jogador& jogador, Posicao posicao);
void posicionar_tipo_jogadores_aleatoriamente(CppmonJogo& novoJogo, int tipo);
void escrever_linha_separadora_mapa(int tamanho);
void escrever_linha_separadora_mapa(int tamanho, int indice_separativo);
void mostrar_mapa(CppmonJogo novoJogo);
void configurar_mapa_basico(CppmonJogo& novoJogo);
void atualizar_valores_mapa(CppmonMapa& mapa, Jogador jogadores[]);
bool posicoes_adjacentes(Posicao ponto1, Posicao ponto2);

//Funções de deck e pocket
void carregar_monstros(Monster array[]);
void mostrar_monstros(Monster lista_monstros[], int tamanho_lista);
void mostrar_todos_monstros(Monster lista_monstros[]);
void mostrar_deck_jogador(Jogador jogador);
void mostrar_pocket_jogador(Jogador jogador);
bool indice_monstro_existe(int indice);
bool verificar_integridade_deck(Capsula deck_monstro[], int comparar_monstro);
void escolher_monstros(Capsula deck_monstros[], Monster lista_monstros[]);
void sortear_monstros(Capsula deck_monstros[], Monster lista_monstros[], int seed);
void definir_level_monstros(Capsula lista_monstros[], int tamanho, int level);
void configurar_deck_jogador(Jogador& jogador, Monster lista_monstros[], int indice_seed);
void ordernar_pocket(Capsula pocket[]);
void ordernar_pocket_jogadores(Jogador& jogador_principal, Jogador& jogador_oponente);

//Funções de jogadores
string solicitar_nome_jogador();
int solicitar_metodo_preenchimento_deck(Jogador jogador);
int solicitar_monstro_usuario(Capsula deck_monstros[], Monster lista_monstros[]);
void configurar_jogadores_basico(CppmonJogo& novoJogo);
Jogador achar_jogador_por_id(Jogador jogadores[], int tamanho, int id);
void mostrar_jogadores(Jogador jogadores[]);

//Funções visuais
void alterar_cor_texto(int cor);
void percorrer_string_com_atraso(string mensagem, int tempo);
void animacao_login();
void mostrar_cabecalho_trabalho(bool mostrar_animacao_login);
void mostrar_introducao_jogo();
int elemento_para_cor(int elemento);
string elemento_correspondente(int indice);
string preencher_ate_extensao(string inicial, int tamanho, char opcao_preenchimento = ' ');
string se_plural(int quantidade, string verdadeiro, string falso);


//Secret.
int easter_egg(); // anomalous 4G41N.

#endif