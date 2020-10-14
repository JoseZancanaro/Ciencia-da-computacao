// CppmonGame.cpp : define o ponto de entrada para o aplicativo do console.
//
#include "stdafx.h"
#include "CppmonGame.h"

using namespace std;

//Funções de estado do jogo
void iniciar_console()
{
	bool mostrar_animacao_login = true;
	bool opcao_execucao = false;
	do {
		opcao_execucao = (!(obter_acao_usuario(mostrar_animacao_login) == OPCAO_SAIR));
		mostrar_animacao_login = false;
	} while (opcao_execucao);
}
void iniciar_novo_jogo()
{
	CppmonJogo novoJogo;
	configurar_novo_jogo(novoJogo);
	executar_novo_jogo(novoJogo);
	finalizar_jogo(novoJogo);
}
int obter_acao_usuario(bool mostrar_animacao_login)
{
	int opcao_menu = 0;
	mostrar_cabecalho_trabalho(mostrar_animacao_login);
	opcao_menu = obter_opcao_menu_inicial();
	switch (opcao_menu)
	{
	case OPCAO_NOVO_JOGO:
		iniciar_novo_jogo();
		break;
	case OPCAO_SAIR:
		break;
	case OPCAO_EASTER_EGG:
		opcao_menu = easter_egg();
		break;
	default:
		cout << endl << endl << "Opcão inválida!" << endl << endl;
		break;
	}
	return opcao_menu;
}
int obter_opcao_menu_inicial()
{
	int opcao_menu = 0;
	mostrar_menu_inicial();
	cin >> opcao_menu;
	return opcao_menu;
}
void mostrar_menu_inicial()
{
	cout << ">>Bem vindo ao Cppmon! Por favor, escolha uma opção abaixo:" << endl << endl;
	cout << "[1] - Iniciar Novo Jogo" << endl;
	cout << "[2] - Sair" << endl << endl;
	cout << "Opção desejada: ";
}
void configurar_novo_jogo(CppmonJogo& novoJogo)
{
	carregar_monstros(novoJogo.lista_imagem);
	mostrar_introducao_jogo();
	configurar_jogadores_basico(novoJogo);
	configurar_mapa_basico(novoJogo);
}
bool fim_de_jogo(CppmonJogo& jogo)
{
	return (jogo.jogadores[JOGADOR_PRINCIPAL].derrotado == true || jogo.jogadores[INDICE_LIDER].derrotado == true);
}
int determinar_motivo_fim(CppmonJogo& jogo)
{
	if (fim_de_jogo(jogo)) {
		if (jogo.jogadores[JOGADOR_PRINCIPAL].derrotado == true)
			return MOTIVO_DERROTA;
		else
			return MOTIVO_VITORIA;
	}
	else
		return MOTIVO_NAN;

}
void finalizar_jogo(CppmonJogo& jogo)
{
	switch (determinar_motivo_fim(jogo)) {
	case MOTIVO_VITORIA:
		finalizar_vitoria();
		break;
	case MOTIVO_DERROTA:
		finalizar_derrota();
		break;
	}
}
void finalizar_vitoria()
{
	system("cls");
	alterar_cor_texto(10);
	percorrer_string_com_atraso("Parabéns, peregrino!", 20);
	cout << endl << endl;
	percorrer_string_com_atraso("Você conseguiu eliminar todos os oponentes, fantástico!", 15);
	alterar_cor_texto(15);
	cout << endl << endl;
	system("pause");
}
void finalizar_derrota()
{
	system("cls");
	alterar_cor_texto(12);
	percorrer_string_com_atraso("Performance excelente, mas não foi suficiente : GAME OVER.", 20);
	cout << endl << endl;
	percorrer_string_com_atraso("A sua jornada ainda está longe de acabar, tente novamente e prove o seu valor!", 15);
	alterar_cor_texto(15);
	cout << endl << endl;
	system("pause");
}

	/*--MODO MAPA--*/
void executar_novo_jogo(CppmonJogo& jogo)
{
	bool lider_posicionado = false;
	while (!fim_de_jogo(jogo))
	{
		mostrar_mapa(jogo);
		if (!checar_possibilidade_x11(jogo.jogadores)) {
			solicitar_acao_jogador(jogo, jogo.jogadores[JOGADOR_PRINCIPAL]);
		}
		else
			confirmar_inicio_batalha(jogo.jogadores[JOGADOR_PRINCIPAL], jogo.jogadores[determinar_indice_desafiador(jogo.jogadores)]);
		realizar_acao_oponentes(jogo);
		atualizar_valores_mapa(jogo.mapa, jogo.jogadores);
		if (!lider_posicionado)
			lider_posicionado = jogador_progrediu(jogo);
	}
}
void solicitar_acao_jogador(CppmonJogo& jogo, Jogador& jogador)
{
	mostrar_opcoes_disponiveis_jogador(jogo.mapa, jogador);
	char opcao = '\0'; string mensagem = "Sua opção: ";
	do {
		cout << endl << mensagem;
		cin >> opcao;
		mensagem = "Opção inválida ou movimentação inadequada, por favor, tente novamente: ";
	} while (!opcao_jogador_valida(opcao, jogo, jogador));
}
bool checar_possibilidade_x11(Jogador jogadores[])
{
	bool aux = false;
	Posicao posicao_jogador = jogadores[JOGADOR_PRINCIPAL].posicao;
	for (int indice = 1; indice < QUANTIDADE_JOGADORES && !(aux); indice++) {
		if (jogadores[indice].ativo)
			aux = posicoes_adjacentes(posicao_jogador, jogadores[indice].posicao);
	}
	return aux;
}
int determinar_indice_desafiador(Jogador jogadores[])
{
	int tmp_indice = 0;
	for (int indice = 0; indice < QUANTIDADE_JOGADORES && tmp_indice == 0; indice++)
	{
		if (jogadores[indice].ativo)
			if (posicoes_adjacentes(jogadores[JOGADOR_PRINCIPAL].posicao, jogadores[indice].posicao))
				tmp_indice = indice;
	}
	return tmp_indice;
}
void confirmar_inicio_batalha(Jogador& jogador_principal, Jogador& jogador_oponente)
{
	cout << endl << endl << "BATTLE!" << endl << endl;
	system("pause");
	iniciar_batalha(jogador_principal, jogador_oponente);
}
string acao_no_j(CppmonMapa mapa, Jogador jogador)
{
	if (posicoes_adjacentes(mapa.centro, jogador.posicao))
		return "J - Recuperar grupo";
	else
		return "J - Esperar";
}
void mostrar_opcoes_disponiveis_jogador(CppmonMapa mapa, Jogador& jogador)
{
	cout << endl;
	cout << "É o seu turno! Hora de escolher uma opção:" << endl << endl;
	cout << "W - Subir" << endl;
	cout << "A - Mover para esquerda" << endl;
	cout << "S - Descer" << endl;
	cout << "D - Mover para direita" << endl;
	cout << acao_no_j(mapa, jogador) << endl;
}
bool opcao_jogador_valida(char opcao, CppmonJogo& jogo, Jogador& jogador)
{
	bool aux = false;
	switch (opcao)
	{
	case 'W': case 'w':
	case 'A': case 'a':
	case 'S': case 's':
	case 'D': case 'd':
		aux = movimentar_jogador(opcao, jogo.mapa, jogador);
		break;
	case 'J': case 'j':
		if (posicoes_adjacentes(jogo.mapa.centro, jogador.posicao)) {
			recuperar_grupo(jogador.deck, jogo.lista_imagem);
			cout << endl << "Seu grupo foi recuperado!!!" << endl << endl;
			system("pause");
		}
		aux = true;
		break;
	}
	return aux;
}
bool movimentar_jogador(char opcao, CppmonMapa& mapa, Jogador& jogador)
{
	bool aux = false;
	switch (opcao) {
	case 'W': case 'w':
		if (posicao_disponivel(mapa, jogador.posicao.linha - 1, jogador.posicao.coluna)) {
			posicionar_jogador(mapa, jogador, jogador.posicao.linha - 1, jogador.posicao.coluna);
			aux = true;
		}
		break;
	case 'A': case 'a':
		if (posicao_disponivel(mapa, jogador.posicao.linha, jogador.posicao.coluna - 1)) {
			posicionar_jogador(mapa, jogador, jogador.posicao.linha, jogador.posicao.coluna - 1);
			aux = true;
		}
		break;
	case 'S': case 's':
		if (posicao_disponivel(mapa, jogador.posicao.linha + 1, jogador.posicao.coluna)) {
			posicionar_jogador(mapa, jogador, jogador.posicao.linha + 1, jogador.posicao.coluna);
			aux = true;
		}
		break;
	case 'D': case 'd':
		if (posicao_disponivel(mapa, jogador.posicao.linha, jogador.posicao.coluna + 1)) {
			posicionar_jogador(mapa, jogador, jogador.posicao.linha, jogador.posicao.coluna + 1);
			aux = true;
		}
		break;
	}
	return aux;
}
void recuperar_grupo(Capsula itens[], Monster imagem[])
{
	for (int indice = 0; indice < QUANTIDADE_MONSTROS; indice++) {
		itens[indice].monstro = imagem[itens[indice].identificador];
	}
}
void realizar_acao_oponentes(CppmonJogo& jogo)
{
	for (int indice = 1; indice < INDICE_LIDER; indice++)
	{
		if (jogo.jogadores[indice].ativo && jogo.jogadores[indice].derrotado == false) {
			movimentar_jogador_oponente(jogo.mapa, jogo.jogadores[indice], indice);
		}
		atualizar_valores_mapa(jogo.mapa, jogo.jogadores);
	}
}
void movimentar_jogador_oponente(CppmonMapa& mapa, Jogador& jogador, int forcar_seed)
{
	srand(time(NULL) + forcar_seed);
	if (rand() % 2 == 1)
	{
		Posicao nova_posicao;
		do {
			int random_linha = (rand() % 3) - 1; 
			int random_coluna = 0;
			if (random_linha == 0)
				random_coluna = (rand() % 3) - 1;
			nova_posicao.linha = jogador.posicao.linha + random_linha;
			nova_posicao.coluna = jogador.posicao.coluna + random_coluna;
		} while (!(posicao_disponivel(mapa, nova_posicao)));
		posicionar_jogador(mapa, jogador, nova_posicao);
	}
}
bool jogador_progrediu(CppmonJogo& jogo)
{
	bool aux = false; int contar_oponentes_abatidos = 0;
	for (int jogador = 0; jogador < QUANTIDADE_JOGADORES; jogador++) {
		if (jogo.jogadores[jogador].tipo_jogador == OPONENTE_COMUM &&
			jogo.jogadores[jogador].derrotado == true) {
			contar_oponentes_abatidos++;
		}
	}
	if (contar_oponentes_abatidos == QUANTIDADE_JOGADORES - 2) {
		aux = true;
		posicionar_tipo_jogadores_aleatoriamente(jogo, OPONENTE_LIDER);
	}
	return (aux);
}

	/*--MODO BATALHA--*/
void iniciar_batalha(Jogador& jogador_principal, Jogador& jogador_oponente)
{
	escolher_monstros_combate(jogador_principal);
	sortear_monstros_oponente(jogador_oponente);
	system("pause");
	emular_batalha(jogador_principal, jogador_oponente);
}
void escolher_monstros_combate(Jogador& jogador)
{
	int escolha_1 = 0;
	int escolha_2 = 0;
	string mensagem = "Selecione o indice dos monstros que você escolherá:";

	system("cls");
	cout << "Você deve escolher apenas 02 monstros para este combate." << endl;
	mostrar_deck_jogador(jogador);

	do {
		cout << endl << mensagem << endl;
		cin >> escolha_1 >> escolha_2;
		mensagem = "Monstro já selecionado, escolha outro.";
	} while (escolha_1 == escolha_2);
	jogador.pocket[0] = jogador.deck[escolha_1 - 1];
	jogador.pocket[1] = jogador.deck[escolha_2 - 1];
	mostrar_pocket_jogador(jogador);
}
void sortear_monstros_oponente(Jogador& oponente)
{
	srand(time(NULL));
	do {
		oponente.pocket[0] = oponente.deck[rand() % 4];
		oponente.pocket[1] = oponente.deck[rand() % 4];
	} while (oponente.pocket[0].identificador == oponente.pocket[1].identificador);
	mostrar_pocket_jogador(oponente);
}
void emular_batalha(Jogador& jogador_principal, Jogador& jogador_oponente)
{
	int rodada = 0, auxiliar = 0;														//Regular jogador atacante
	int ativo_jogador = 0, ativo_oponente = 0;											//Regular monstro ativo
	int saldo_jogador = QUANTIDADE_MONSTROS_POCKET - 1;									//Regular quantidade monstros jogador
	int saldo_oponente = QUANTIDADE_MONSTROS_POCKET - 1;								//Regular quantidade monstros oponente

	if (jogador_tem_mais_velocidade(jogador_principal.pocket[ativo_jogador].monstro,
		jogador_oponente.pocket[ativo_oponente].monstro))
		auxiliar = 1;
	while (!batalha_finalizou(jogador_principal, jogador_oponente))
	{
		exibir_status_monstros_jogadores(jogador_principal, jogador_oponente);
		exibir_informacoes_monstros(jogador_principal, jogador_oponente, ativo_jogador, ativo_oponente, rodada + 1);
		if (auxiliar + rodada % 2 != 0)
		{
			efetuar_ataque_jogador(jogador_principal, jogador_oponente, ativo_jogador, ativo_oponente);
			validar_monstro_ativo(jogador_oponente, ativo_oponente, saldo_oponente);
		}
		else {
			efetuar_habilidade_oponente(jogador_principal, jogador_oponente, ativo_jogador, ativo_oponente);
			validar_monstro_ativo(jogador_principal, ativo_jogador, saldo_jogador);
		}
		system("pause");
		rodada++;
	}
	atualizar_estados_monstros_deck(jogador_principal);
	system("cls");
	switch (definir_vencedor_batalha(jogador_principal, jogador_oponente)) {
	case MOTIVO_VITORIA:
		cout << "Resultado da batalha:" << endl << endl;
		cout << "Parabéns, você saiu vitorioso! Pronto para retornar ao mapa?" << endl << endl;
		system("pause");
		break;
	case MOTIVO_DERROTA:
		cout << "Resultado da batalha:" << endl << endl;
		cout << "Infelizmente você foi derrotado pelo seu adversário e perdeu o jogo." << endl << endl;
		system("pause");
	}
}
bool jogador_tem_mais_velocidade(Monster monstro_jogador, Monster monstro_oponente)
{
	if (monstro_jogador.velocidade != monstro_oponente.velocidade) {
		return (monstro_jogador.velocidade > monstro_oponente.velocidade);
	}
	else {
		return sorteia_impar();
	}
}
bool sorteia_impar()
{
	srand(time(NULL));
	return (rand() % 2 != 0);
}
void validar_monstro_ativo(Jogador& jogador, int& ativo, int& saldo)
{
	if (!jogador.pocket[ativo].monstro.vivo())
	{
		jogador.pocket[ativo].monstro.vida = 0;
		anunciar_nocaute(jogador.pocket[ativo].monstro);
		if (saldo > 0) {
			ativo++;
			saldo--;
			apresentar_substituto(jogador.pocket[ativo].monstro);
		}
	}
}
void anunciar_nocaute(Monster monstro)
{
	cout << monstro.nome << " caiu em batalha." << endl;
}
void apresentar_substituto(Monster monstro)
{
	cout << monstro.nome << " entrará no combate." << endl << endl;
}
bool batalha_finalizou(Jogador jogador_principal, Jogador jogador_oponente)
{
	return (contar_monstros_vivos_pocket(jogador_principal.pocket) == 0 ||
		contar_monstros_vivos_pocket(jogador_oponente.pocket) == 0);
}
void atualizar_estados_monstros_deck(Jogador& jogador)
{
	for (int indice = 0; indice < QUANTIDADE_MONSTROS_POCKET; indice++) {
		bool encontrou = false;
		for (int indice_deck = 0; indice_deck < QUANTIDADE_MONSTROS && !(encontrou); indice_deck++) {
			if (jogador.pocket[indice].identificador == jogador.deck[indice_deck].identificador) {
				jogador.deck[indice_deck] = jogador.pocket[indice];
				for (int indice_skill = 0; indice_skill < QUANTIDADE_HABILIDADES; indice_skill++)
					jogador.deck[indice_deck].monstro.habilidade[indice_skill].utilizou = 0;
			}
		}
	}
}
int definir_vencedor_batalha(Jogador& jogador_principal, Jogador& jogador_oponente)
{
	int motivo = MOTIVO_NAN;
	if (batalha_finalizou(jogador_principal, jogador_oponente)) {
		if (contar_monstros_vivos_pocket(jogador_principal.pocket) == 0) {
			jogador_principal.derrotado = true;
			jogador_principal.ativo = false;
			motivo = MOTIVO_DERROTA;
		}
		else {
			jogador_oponente.derrotado = true;
			jogador_oponente.ativo = false;
			motivo = MOTIVO_VITORIA;
		}
	}
	return motivo;
}
int contar_monstros_vivos(Capsula lista[], int tamanho)
{
	int monstros_vivos = 0;
	for (int indice = 0; indice < tamanho; indice++) {
		if (lista[indice].monstro.vivo())
			monstros_vivos++;
	}
	return monstros_vivos;
}
int contar_monstros_vivos_pocket(Capsula lista[])
{
	return (contar_monstros_vivos(lista, QUANTIDADE_MONSTROS_POCKET));
}
string reportar_monstros_vivos(Capsula pocket[])
{
	int monstros_vivos = contar_monstros_vivos(pocket, QUANTIDADE_MONSTROS_POCKET);
	string auxiliar = "Possui " + se_plural(monstros_vivos, " monstros", " monstro");
	return (auxiliar);
}
void exibir_status_monstros(Jogador jogador)
{
	cout << jogador.nome << ": " << reportar_monstros_vivos(jogador.pocket) << endl;
}
void exibir_status_monstros_jogadores(Jogador jogador_principal, Jogador jogador_oponente)
{
	system("cls");
	exibir_status_monstros(jogador_principal);
	exibir_status_monstros(jogador_oponente);
}
void exibir_informacoes_monstros(Jogador& jogador_principal, Jogador& jogador_oponente, int ativo_jogador, int ativo_oponente, int turno)
{
	cout << endl;

	string texto = "Turno " + to_string(turno) + ": ";

	texto += jogador_principal.pocket[ativo_jogador].monstro.nome + " (LV" + to_string(jogador_principal.pocket[ativo_jogador].monstro.level) + ") ";
	texto += to_string(jogador_principal.pocket[ativo_jogador].monstro.vida) + "/200";

	texto += " VS " + jogador_oponente.pocket[ativo_oponente].monstro.nome + " (LV" + to_string(jogador_oponente.pocket[ativo_oponente].monstro.level) + ") ";
	texto += to_string(jogador_oponente.pocket[ativo_oponente].monstro.vida) + "/200";

	cout << texto << endl << endl;
}
void listar_habilidades_monstro(Monster monstro)
{
	cout << "Qual ataque seu " << monstro.nome << " deve utilizar?" << endl << endl;
	cout << "[1] - " << monstro.habilidade[ATAQUE_ELEMENTAR].nome << " - " << monstro.habilidade[ATAQUE_ELEMENTAR].utilizou << "/" << monstro.habilidade[ATAQUE_ELEMENTAR].limite << endl;
	cout << "[2] - " << monstro.habilidade[ATAQUE_COMUM].nome << " - " << monstro.habilidade[ATAQUE_COMUM].utilizou << "/" << monstro.habilidade[ATAQUE_COMUM].limite << endl;
	cout << "[3] - " << monstro.habilidade[ATAQUE_RAPIDO].nome << " - " << monstro.habilidade[ATAQUE_RAPIDO].utilizou << "/" << monstro.habilidade[ATAQUE_RAPIDO].limite << endl;
	cout << "[4] - " << monstro.habilidade[SUPER_ATAQUE].nome << " - " << monstro.habilidade[SUPER_ATAQUE].utilizou << "/" << monstro.habilidade[SUPER_ATAQUE].limite << endl;
}
void efetuar_ataque_jogador(Jogador& jogador_principal, Jogador& jogador_oponente, int ativo_jogador, int ativo_oponente)
{
	int habilidade = solicitar_habilidade_jogador(jogador_principal.pocket[ativo_jogador].monstro);
	float dano = quantificar_dano(jogador_principal.pocket[ativo_jogador].monstro, jogador_oponente.pocket[ativo_oponente].monstro, habilidade);
	infligir_dano(jogador_oponente.pocket[ativo_oponente].monstro, dano);
	registrar_uso_habilidade(jogador_principal.pocket[ativo_jogador].monstro.habilidade[habilidade]);
	reportar_acao_ataque(jogador_principal.pocket[ativo_jogador].monstro.nome, jogador_oponente.pocket[ativo_oponente].monstro.nome, dano);
}
int solicitar_habilidade_jogador(Monster monstro_jogador)
{
	listar_habilidades_monstro(monstro_jogador);
	int escolha_habilidade = 0;

	string aviso = "Escolha sua habilidade: ";

	do {
		cout << endl << aviso;
		cin >> escolha_habilidade;
		escolha_habilidade--;
		aviso = "Opção inválida, tente novamente: ";
	} while (!validar_habilidade(monstro_jogador, escolha_habilidade));

	return escolha_habilidade;
}
bool validar_habilidade(Monster monstro, int habilidade)
{
	if (habilidade == ATAQUE_ELEMENTAR || habilidade == ATAQUE_COMUM ||
		habilidade == ATAQUE_RAPIDO || habilidade == SUPER_ATAQUE)
		return (monstro.habilidade[habilidade].disponivel());
	else
		return (false);
}
int quantificar_dano(Monster monstro_atacante, Monster monstro_defensor, int habilidade)
{
	srand(time(NULL));
	int sorteio_dano = rand() % 16;

	float modificador = definir_modificador(monstro_atacante, monstro_defensor);
	int ataque = monstro_atacante.ataque;
	int poder_atacante = monstro_atacante.habilidade[habilidade].poder * modificador_level_monstro(monstro_atacante.level);
	int defesa_oponente = monstro_defensor.defesa;

	int dano = (sorteio_dano + (((ataque)+(poder_atacante)) - defesa_oponente) * modificador);
	if (dano < 0)
		dano = 0;
	return dano;
}
float definir_modificador(Monster monstro_atacante, Monster monstro_defensor)
{
	if (monstro_atacante.tipo_vantagem == monstro_defensor.tipo)
		return 1.5;
	else if (monstro_atacante.tipo_desvantagem == monstro_defensor.tipo)
		return 0.5;
	else
		return 1.0;
}
float modificador_level_monstro(int level)
{
	if (level == 75)
	{
		return 1.25;
	}
	else
		return 1.0;
}
void infligir_dano(Monster& monstro_defensor, int dano)
{
	monstro_defensor.vida -= dano;
}
void registrar_uso_habilidade(Habilidade& habilidade)
{
	habilidade.utilizou++;
}
void reportar_acao_ataque(string nome_monstro, string nome_monstro_defensor, float dano)
{
	cout << endl << endl;
	cout << nome_monstro << " infligiu dolorosos " << dano << " pontos de em " << nome_monstro_defensor;
	cout << endl << endl;
}
void efetuar_habilidade_oponente(Jogador& jogador_principal, Jogador& jogador_oponente, int ativo_jogador, int ativo_oponente)
{
	int habilidade = sortear_habilidade_oponente(jogador_oponente.tipo_jogador);
	float dano = quantificar_dano(jogador_oponente.pocket[ativo_oponente].monstro, jogador_principal.pocket[ativo_jogador].monstro, habilidade);
	infligir_dano(jogador_principal.pocket[ativo_jogador].monstro, dano);
	registrar_uso_habilidade(jogador_oponente.pocket[ativo_oponente].monstro.habilidade[habilidade]);
	escrever_escolha_habilidade(jogador_oponente.pocket[ativo_oponente].monstro.nome, jogador_oponente.pocket[ativo_oponente].monstro.habilidade[habilidade].nome);
	reportar_acao_ataque(jogador_oponente.pocket[ativo_oponente].monstro.nome, jogador_principal.pocket[ativo_jogador].monstro.nome, dano);
}
int sortear_habilidade_oponente(int tipo_jogador)
{
	int habilidade = 0;
	switch (tipo_jogador) {
	case OPONENTE_COMUM:
		habilidade = rand() % (4);
		break;
	case OPONENTE_LIDER:
		habilidade = rand() % (3) + 1;
		break;
	}
	return habilidade;
}
void escrever_escolha_habilidade(string nome_monstro, string nome_habilidade)
{
	cout << nome_monstro << " escolheu a habilidade " << nome_habilidade << ".";
}

//Funções de mapa
int conferir_posicao_mapa(CppmonMapa mapa, int linha, int coluna)
{
	int valor_retorno = POSICAO_INEXISTENTE;
	if (linha >= 0 && linha < DIMENSAO_ALTURA
		&& coluna >= 0 && coluna < DIMENSAO_LARGURA
		)
	{
		valor_retorno = mapa.regiao[linha][coluna];
	}
	return (valor_retorno);
}
int conferir_posicao_mapa(CppmonMapa mapa, Posicao posicao)
{
	return (conferir_posicao_mapa(mapa, posicao.linha, posicao.coluna));
}
void definir_valor_no_mapa(CppmonMapa& mapa, int valor, int linha, int coluna, bool ignorar_validacao)
{
	if (mapa.regiao[linha][coluna] == POSICAO_VAZIA || ignorar_validacao) {
		mapa.regiao[linha][coluna] = valor;
	}
}
void definir_valor_no_mapa(CppmonMapa& mapa, int valor, Posicao posicao, bool ignorar_validacao)
{
	definir_valor_no_mapa(mapa, valor, posicao.linha, posicao.coluna, ignorar_validacao);
}
bool posicao_disponivel(CppmonMapa mapa, int linha, int coluna)
{
	return (conferir_posicao_mapa(mapa, linha, coluna) == POSICAO_VAZIA);
}
bool posicao_disponivel(CppmonMapa mapa, Posicao posicao)
{
	return posicao_disponivel(mapa, posicao.linha, posicao.coluna);
}
Posicao posicao_disponivel_aleatorio(CppmonMapa mapa)
{
	Posicao nova_posicao;
	do {
		nova_posicao.linha = rand() % DIMENSAO_ALTURA;
		nova_posicao.coluna = rand() % DIMENSAO_LARGURA;
	} while (conferir_posicao_mapa(mapa, nova_posicao) != POSICAO_VAZIA);
	return (nova_posicao);
}
void posicionar_cercas(CppmonMapa& mapa, int indice)
{
	if (indice > 0) {
		Posicao nova_posicao = posicao_disponivel_aleatorio(mapa);
		mapa.regiao[nova_posicao.linha][nova_posicao.coluna] = POSICAO_CERCA;
		posicionar_cercas(mapa, indice - 1);
	}
}
void posicionar_arena(CppmonMapa& mapa)
{
	Posicao nova_posicao = posicao_disponivel_aleatorio(mapa);
	mapa.centro = nova_posicao;
	definir_valor_no_mapa(mapa, POSICAO_ARENA, mapa.centro);
}
void posicionar_jogador(CppmonMapa& mapa, Jogador& jogador, int linha, int coluna)
{
	if (mapa.regiao[linha][coluna] == POSICAO_VAZIA) {
		mapa.regiao[linha][coluna] = jogador.id;
		jogador.posicao.linha = linha;
		jogador.posicao.coluna = coluna;
		jogador.ativo = true;
	}
}
void posicionar_jogador(CppmonMapa& mapa, Jogador& jogador, Posicao posicao)
{
	posicionar_jogador(mapa, jogador, posicao.linha, posicao.coluna);
}
void posicionar_jogador_principal(CppmonJogo& novoJogo)
{
	posicionar_jogador(novoJogo.mapa, novoJogo.jogadores[JOGADOR_PRINCIPAL], 7, 7);
}
void posicionar_tipo_jogadores_aleatoriamente(CppmonJogo& novoJogo, int tipo)
{
	for (int indice = 0; indice < QUANTIDADE_JOGADORES; indice++) {
		if (novoJogo.jogadores[indice].tipo_jogador == tipo) {
			Posicao posicao_random = posicao_disponivel_aleatorio(novoJogo.mapa);
			posicionar_jogador(novoJogo.mapa, novoJogo.jogadores[indice], posicao_random);
		}
	}
}
void escrever_linha_separadora_mapa(int tamanho)
{
	for (int indice = 0; indice < tamanho; indice++)
		cout << "-";
}
void escrever_linha_separadora_mapa(int tamanho, int indice_separativo)
{
	for (int indice = 0; indice < tamanho; indice++)
		cout << ((indice != 0 && (indice + 1) % indice_separativo == 0) ? "+" : "-");
}
void mostrar_mapa(CppmonJogo novoJogo)
{
	system("cls");

	cout << endl << endl << "#   ";
	for (int coluna = 0; coluna < DIMENSAO_LARGURA; coluna++) {
		cout << coluna + 1 << string(4 - to_string(coluna + 1).length(), ' ');
	}
	cout << endl;

	for (int linha = 0; linha < DIMENSAO_ALTURA; linha++) {
		escrever_linha_separadora_mapa(DIMENSAO_LARGURA * 4 + 4, 4);
		cout << endl << linha + 1 << string(3 - to_string(linha + 1).length(), ' ') << "|";
		for (int coluna = 0; coluna < DIMENSAO_LARGURA; coluna++) {
			switch (novoJogo.mapa.regiao[linha][coluna])
			{
			case POSICAO_VAZIA:
				cout << "   ";
				break;
			case POSICAO_ARENA:
				cout << STR_CENTRO;
				break;
			case POSICAO_CERCA:
				cout << STR_CERCA;
				break;
			default:
				if (novoJogo.mapa.regiao[linha][coluna] < 0 && novoJogo.mapa.regiao[linha][coluna] > ((QUANTIDADE_JOGADORES + 1)* -1))
				{
					cout << achar_jogador_por_id(novoJogo.jogadores, QUANTIDADE_JOGADORES, novoJogo.mapa.regiao[linha][coluna]).cod;
				}
				else {
					cout << "   ";
				}
			}
			cout << "|";
		}
		cout << endl;
	}
	escrever_linha_separadora_mapa(DIMENSAO_LARGURA * 4 + 4);
	cout << endl << endl;
}
void configurar_mapa_basico(CppmonJogo& novoJogo)
{
	posicionar_jogador_principal(novoJogo);
	posicionar_cercas(novoJogo.mapa, QUANTIDADE_CERCAS);
	posicionar_tipo_jogadores_aleatoriamente(novoJogo, OPONENTE_COMUM);
	posicionar_arena(novoJogo.mapa);
}
void atualizar_valores_mapa(CppmonMapa& mapa, Jogador jogadores[])
{
	for (int linha = 0; linha < DIMENSAO_ALTURA; linha++)
	{
		for (int coluna = 0; coluna < DIMENSAO_LARGURA; coluna++)
		{
			if (mapa.regiao[linha][coluna] < 0 && mapa.regiao[linha][coluna] > (QUANTIDADE_JOGADORES + 1) * -1)
			{
				Jogador jogador_id = achar_jogador_por_id(jogadores, QUANTIDADE_JOGADORES, mapa.regiao[linha][coluna]);
				if (linha != jogador_id.posicao.linha || coluna != jogador_id.posicao.coluna || (jogador_id.ativo == false))
					definir_valor_no_mapa(mapa, POSICAO_VAZIA, linha, coluna, true);
			}
		}
	}
}
bool posicoes_adjacentes(Posicao ponto1, Posicao ponto2)
{
	bool aux = false;
	if (ponto1.coluna == ponto2.coluna) {
		if (ponto1.linha - 1 == ponto2.linha)
			aux = true;
		else if (ponto1.linha + 1 == ponto2.linha)
			aux = true;
	}
	else if (ponto1.linha == ponto2.linha)
	{
		if (ponto1.coluna - 1 == ponto2.coluna)
			aux = true;
		else if (ponto1.coluna + 1 == ponto2.coluna)
			aux = true;
	}
	return aux;
}

//Funções de deck e pocket
void carregar_monstros(Monster array[])
{
	//Monstro numero 0:
	array[0].nome = "Demon Skeleton";
	array[0].tipo = FOGO;
	array[0].tipo_vantagem = ELETRICO;
	array[0].tipo_desvantagem = AGUA;
	array[0].vida = 200;
	array[0].ataque = 40;
	array[0].defesa = 60;
	array[0].velocidade = 75;
	array[0].habilidade[0].nome = "Ataque de Fogo";
	array[0].habilidade[0].poder = 40;
	array[0].habilidade[0].tipo = FOGO;
	array[0].habilidade[0].limite = 3;
	array[0].habilidade[1].nome = "Ataque Comum";
	array[0].habilidade[1].poder = 20;
	array[0].habilidade[1].tipo = FOGO;
	array[0].habilidade[1].limite = 10;
	array[0].habilidade[2].nome = "Ataque Rápido";
	array[0].habilidade[2].poder = 30;
	array[0].habilidade[2].tipo = FOGO;
	array[0].habilidade[2].limite = 7;
	array[0].habilidade[3].nome = "Super Ataque";
	array[0].habilidade[3].poder = 50;
	array[0].habilidade[3].tipo = FOGO;
	array[0].habilidade[3].limite = 2;


	//Monstro numero 1:

	array[1].nome = "Aquaman";
	array[1].tipo = AGUA;
	array[1].tipo_vantagem = FOGO;
	array[1].tipo_desvantagem = GRAMA;
	array[1].vida = 200;
	array[1].ataque = 35;
	array[1].defesa = 55;
	array[1].velocidade = 70;
	array[1].habilidade[0].nome = "Ataque de Água";
	array[1].habilidade[0].poder = 35;
	array[1].habilidade[0].tipo = AGUA;
	array[1].habilidade[0].limite = 3;
	array[1].habilidade[1].nome = "Ataque Comum";
	array[1].habilidade[1].poder = 20;
	array[1].habilidade[1].tipo = AGUA;
	array[1].habilidade[1].limite = 10;
	array[1].habilidade[2].nome = "Ataque Rápido";
	array[1].habilidade[2].poder = 25;
	array[1].habilidade[2].tipo = AGUA;
	array[1].habilidade[2].limite = 7;
	array[1].habilidade[3].nome = "Super Ataque";
	array[1].habilidade[3].poder = 50;
	array[1].habilidade[3].tipo = AGUA;
	array[1].habilidade[3].limite = 2;

	//Monstro numero 2:

	array[2].nome = "Landstriker";
	array[2].tipo = GRAMA;
	array[2].tipo_vantagem = AGUA;
	array[2].tipo_desvantagem = VOADOR;
	array[2].vida = 200;
	array[2].ataque = 55;
	array[2].defesa = 50;
	array[2].velocidade = 100;
	array[2].habilidade[0].nome = "Ataque de Grama";
	array[2].habilidade[0].poder = 35;
	array[2].habilidade[0].tipo = GRAMA;
	array[2].habilidade[0].limite = 3;
	array[2].habilidade[1].nome = "Ataque Comum";
	array[2].habilidade[1].poder = 20;
	array[2].habilidade[1].tipo = GRAMA;
	array[2].habilidade[1].limite = 10;
	array[2].habilidade[2].nome = "Ataque Rápido";
	array[2].habilidade[2].poder = 25;
	array[2].habilidade[2].tipo = GRAMA;
	array[2].habilidade[2].limite = 6;
	array[2].habilidade[3].nome = "Super Ataque";
	array[2].habilidade[3].poder = 50;
	array[2].habilidade[3].tipo = GRAMA;
	array[2].habilidade[3].limite = 2;

	//Monstro numero 3:

	array[3].nome = "Sparkles";
	array[3].tipo = ELETRICO;
	array[3].tipo_vantagem = VOADOR;
	array[3].tipo_desvantagem = FOGO;
	array[3].vida = 200;
	array[3].ataque = 60;
	array[3].defesa = 75;
	array[3].velocidade = 90;
	array[3].habilidade[0].nome = "Ataque Eletrico";
	array[3].habilidade[0].poder = 30;
	array[3].habilidade[0].tipo = ELETRICO;
	array[3].habilidade[0].limite = 3;
	array[3].habilidade[1].nome = "Ataque Comum";
	array[3].habilidade[1].poder = 15;
	array[3].habilidade[1].tipo = ELETRICO;
	array[3].habilidade[1].limite = 10;
	array[3].habilidade[2].nome = "Ataque Rápido";
	array[3].habilidade[2].poder = 25;
	array[3].habilidade[2].tipo = ELETRICO;
	array[3].habilidade[2].limite = 5;
	array[3].habilidade[3].nome = "Super Ataque";
	array[3].habilidade[3].poder = 50;
	array[3].habilidade[3].tipo = ELETRICO;
	array[3].habilidade[3].limite = 2;

	//Mostro numero 4:

	array[4].nome = "Swift";
	array[4].tipo = VOADOR;
	array[4].tipo_vantagem = GRAMA;
	array[4].tipo_desvantagem = ELETRICO;
	array[4].vida = 200;
	array[4].ataque = 45;
	array[4].defesa = 45;
	array[4].velocidade = 100;
	array[4].habilidade[0].nome = "Ataque VOADOR";
	array[4].habilidade[0].poder = 30;
	array[4].habilidade[0].tipo = VOADOR;
	array[4].habilidade[0].limite = 4;
	array[4].habilidade[1].nome = "Ataque Comum";
	array[4].habilidade[1].poder = 15;
	array[4].habilidade[1].tipo = VOADOR;
	array[4].habilidade[1].limite = 10;
	array[4].habilidade[2].nome = "Ataque Rápido";
	array[4].habilidade[2].poder = 25;
	array[4].habilidade[2].tipo = VOADOR;
	array[4].habilidade[2].limite = 7;
	array[4].habilidade[3].nome = "Super Ataque";
	array[4].habilidade[3].poder = 50;
	array[4].habilidade[3].tipo = VOADOR;
	array[4].habilidade[3].limite = 3;

	//Monstro numero 5:

	array[5].nome = "Dragon Lord";
	array[5].tipo = FOGO;
	array[5].tipo_vantagem = ELETRICO;
	array[5].tipo_desvantagem = AGUA;
	array[5].vida = 200;
	array[5].ataque = 85;
	array[5].defesa = 25;
	array[5].velocidade = 100;
	array[5].habilidade[0].nome = "Ataque de Fogo";
	array[5].habilidade[0].poder = 40;
	array[5].habilidade[0].tipo = FOGO;
	array[5].habilidade[0].limite = 3;
	array[5].habilidade[1].nome = "Ataque Comum";
	array[5].habilidade[1].poder = 25;
	array[5].habilidade[1].tipo = FOGO;
	array[5].habilidade[1].limite = 10;
	array[5].habilidade[2].nome = "Ataque Rápido";
	array[5].habilidade[2].poder = 30;
	array[5].habilidade[2].tipo = FOGO;
	array[5].habilidade[2].limite = 5;
	array[5].habilidade[3].nome = "Super Ataque";
	array[5].habilidade[3].poder = 50;
	array[5].habilidade[3].tipo = FOGO;
	array[5].habilidade[3].limite = 2;

	//Monstro numero 6:

	array[6].nome = "Kraken";
	array[6].tipo = AGUA;
	array[6].tipo_vantagem = FOGO;
	array[6].tipo_desvantagem = GRAMA;
	array[6].vida = 200;
	array[6].ataque = 62;
	array[6].defesa = 40;
	array[6].velocidade = 100;
	array[6].habilidade[0].nome = "Ataque de Água";
	array[6].habilidade[0].poder = 35;
	array[6].habilidade[0].tipo = AGUA;
	array[6].habilidade[0].limite = 4;
	array[6].habilidade[1].nome = "Ataque Comum";
	array[6].habilidade[1].poder = 10;
	array[6].habilidade[1].tipo = AGUA;
	array[6].habilidade[1].limite = 10;
	array[6].habilidade[2].nome = "Ataque Rápido";
	array[6].habilidade[2].poder = 25;
	array[6].habilidade[2].tipo = AGUA;
	array[6].habilidade[2].limite = 5;
	array[6].habilidade[3].nome = "Super Ataque";
	array[6].habilidade[3].poder = 50;
	array[6].habilidade[3].tipo = AGUA;
	array[6].habilidade[3].limite = 4;

	//Mosntro numero 7:

	array[7].nome = "Nature Will";
	array[7].tipo = GRAMA;
	array[7].tipo_vantagem = AGUA;
	array[7].tipo_desvantagem = VOADOR;
	array[7].vida = 200;
	array[7].ataque = 70;
	array[7].defesa = 35;
	array[7].velocidade = 100;
	array[7].habilidade[0].nome = "Ataque de Grama";
	array[7].habilidade[0].poder = 30;
	array[7].habilidade[0].tipo = GRAMA;
	array[7].habilidade[0].limite = 3;
	array[7].habilidade[1].nome = "Ataque Comum";
	array[7].habilidade[1].poder = 15;
	array[7].habilidade[1].tipo = GRAMA;
	array[7].habilidade[1].limite = 10;
	array[7].habilidade[2].nome = "Ataque Rápido";
	array[7].habilidade[2].poder = 20;
	array[7].habilidade[2].tipo = GRAMA;
	array[7].habilidade[2].limite = 6;
	array[7].habilidade[3].nome = "Super Ataque";
	array[7].habilidade[3].poder = 50;
	array[7].habilidade[3].tipo = GRAMA;
	array[7].habilidade[3].limite = 2;

	// Monstro numero 8:

	array[8].nome = "Zeus";
	array[8].tipo = ELETRICO;
	array[8].tipo_vantagem = VOADOR;
	array[8].tipo_desvantagem = FOGO;
	array[8].vida = 200;
	array[8].ataque = 90;
	array[8].defesa = 20;
	array[8].velocidade = 100;
	array[8].habilidade[0].nome = "Ataque Eletrico";
	array[8].habilidade[0].poder = 35;
	array[8].habilidade[0].tipo = ELETRICO;
	array[8].habilidade[0].limite = 2;
	array[8].habilidade[1].nome = "Ataque Comum";
	array[8].habilidade[1].poder = 20;
	array[8].habilidade[1].tipo = ELETRICO;
	array[8].habilidade[1].limite = 10;
	array[8].habilidade[2].nome = "Ataque Rápido";
	array[8].habilidade[2].poder = 30;
	array[8].habilidade[2].tipo = ELETRICO;
	array[8].habilidade[2].limite = 5;
	array[8].habilidade[3].nome = "Super Ataque";
	array[8].habilidade[3].poder = 50;
	array[8].habilidade[3].tipo = ELETRICO;
	array[8].habilidade[3].limite = 1;

	//Monstro numero 9:

	array[9].nome = "Night Fury";
	array[9].tipo = VOADOR;
	array[9].tipo_vantagem = GRAMA;
	array[9].tipo_desvantagem = ELETRICO;
	array[9].vida = 200;
	array[9].ataque = 60;
	array[9].defesa = 45;
	array[9].velocidade = 100;
	array[9].habilidade[0].nome = "Ataque VOADOR";
	array[9].habilidade[0].poder = 30;
	array[9].habilidade[0].tipo = VOADOR;
	array[9].habilidade[0].limite = 4;
	array[9].habilidade[1].nome = "Ataque Comum";
	array[9].habilidade[1].poder = 15;
	array[9].habilidade[1].tipo = VOADOR;
	array[9].habilidade[1].limite = 10;
	array[9].habilidade[2].nome = "Ataque Rápido";
	array[9].habilidade[2].poder = 25;
	array[9].habilidade[2].tipo = VOADOR;
	array[9].habilidade[2].limite = 7;
	array[9].habilidade[3].nome = "Super Ataque";
	array[9].habilidade[3].poder = 50;
	array[9].habilidade[3].tipo = VOADOR;
	array[9].habilidade[3].limite = 2;

	//Monstro numero 10:

	array[10].nome = "Thunderbolt";
	array[10].tipo = ELETRICO;
	array[10].tipo_vantagem = VOADOR;
	array[10].tipo_desvantagem = FOGO;
	array[10].vida = 200;
	array[10].ataque = 55;
	array[10].defesa = 80;
	array[10].velocidade = 100;
	array[10].habilidade[0].nome = "Ataque Eletrico";
	array[10].habilidade[0].poder = 25;
	array[10].habilidade[0].tipo = ELETRICO;
	array[10].habilidade[0].limite = 5;
	array[10].habilidade[1].nome = "Ataque Comum";
	array[10].habilidade[1].poder = 5;
	array[10].habilidade[1].tipo = ELETRICO;
	array[10].habilidade[1].limite = 10;
	array[10].habilidade[2].nome = "Ataque Rápido";
	array[10].habilidade[2].poder = 15;
	array[10].habilidade[2].tipo = ELETRICO;
	array[10].habilidade[2].limite = 6;
	array[10].habilidade[3].nome = "Super Ataque";
	array[10].habilidade[3].poder = 50;
	array[10].habilidade[3].tipo = ELETRICO;
	array[10].habilidade[3].limite = 3;

	//Monstro numero 11:

	array[11].nome = "Cthulhu";
	array[11].tipo = AGUA;
	array[11].tipo_vantagem = FOGO;
	array[11].tipo_desvantagem = GRAMA;
	array[11].vida = 200;
	array[11].ataque = 95;
	array[11].defesa = 80;
	array[11].velocidade = 100;
	array[11].habilidade[0].nome = "Ataque de Água";
	array[11].habilidade[0].poder = 35;
	array[11].habilidade[0].tipo = AGUA;
	array[11].habilidade[0].limite = 3;
	array[11].habilidade[1].nome = "Ataque Comum";
	array[11].habilidade[1].poder = 15;
	array[11].habilidade[1].tipo = AGUA;
	array[11].habilidade[1].limite = 10;
	array[11].habilidade[2].nome = "Ataque Rápido";
	array[11].habilidade[2].poder = 20;
	array[11].habilidade[2].tipo = AGUA;
	array[11].habilidade[2].limite = 8;
	array[11].habilidade[3].nome = "Super Ataque";
	array[11].habilidade[3].poder = 50;
	array[11].habilidade[3].tipo = AGUA;
	array[11].habilidade[3].limite = 1;
}
bool indice_monstro_existe(int indice)
{
	return (indice >= 0 && indice < QUANTIDADE_MONSTRO_DISP);
}
void mostrar_monstros(Monster lista_monstros[], int tamanho_lista)
{
	cout << endl << endl << "Monstros disponíveis: " << endl << endl;
	cout << preencher_ate_extensao("Monstro", 22) << "| ";
	cout << preencher_ate_extensao("Vida", 7) << "| ";
	cout << preencher_ate_extensao("Ataque",8) << "| ";
	cout << preencher_ate_extensao("Defesa", 8) << "| ";
	cout << preencher_ate_extensao("Velocidade", 12) << "| ";
	cout << preencher_ate_extensao("Tipo", 10) << endl;
	for (int i = 0; i < tamanho_lista; i++) {
		string indice = (i + 1 < 10) ? "0" : "";
		indice += to_string(i + 1);
		cout << preencher_ate_extensao("[" + indice + "] " + lista_monstros[i].nome, 22) << "| ";
		cout << preencher_ate_extensao(to_string(lista_monstros[i].vida), 7) << "| ";
		cout << preencher_ate_extensao(to_string(lista_monstros[i].ataque), 8) << "| ";
		cout << preencher_ate_extensao(to_string(lista_monstros[i].defesa), 8) << "| ";
		cout << preencher_ate_extensao(to_string(lista_monstros[i].velocidade), 10) << "| ";
		alterar_cor_texto(elemento_para_cor(lista_monstros[i].tipo));
		cout << preencher_ate_extensao(elemento_correspondente(lista_monstros[i].tipo), 12);
		alterar_cor_texto(15);
		cout << endl;
	}
}
void mostrar_todos_monstros(Monster lista_monstros[])
{
	mostrar_monstros(lista_monstros, QUANTIDADE_MONSTRO_DISP);
}
void mostrar_deck_jogador(Jogador jogador)
{
	cout << endl << "Deck de " << jogador.nome << ":" << endl << endl;
	cout << preencher_ate_extensao("Monstro", 30) << "| " << preencher_ate_extensao("Tipo", 30) << endl;
	for (int y = 0; y < QUANTIDADE_MONSTROS; y++) {
		cout << preencher_ate_extensao("[" + to_string(y+1) + "] " + jogador.deck[y].monstro.nome, 30) << "| ";
		cout << preencher_ate_extensao(elemento_correspondente(jogador.deck[y].monstro.tipo), 30) << endl;
	}
}
void mostrar_pocket_jogador(Jogador jogador)
{
	cout << endl << "Pocket de " << jogador.nome << ":" << endl << endl;
	cout << preencher_ate_extensao("Monstro", 30) << "| " << preencher_ate_extensao("Tipo", 30) << endl;
	for (int y = 0; y < QUANTIDADE_MONSTROS_POCKET; y++) {
		cout << preencher_ate_extensao("[" + to_string(y + 1) + "] " + jogador.pocket[y].monstro.nome, 30) << "| ";
		cout << preencher_ate_extensao(elemento_correspondente(jogador.pocket[y].monstro.tipo), 30) << endl;
	}
	cout << endl;
}
bool verificar_integridade_deck(Capsula deck_monstro[], int comparar_monstro)
{
	bool deck_integro = true;
	for (int indice = 0; indice < 4 && deck_integro; indice++) {
		if (deck_monstro[indice].identificador == comparar_monstro) {
			deck_integro = false;
		}
	}
	return deck_integro;
}
int solicitar_monstro_usuario(Capsula deck_monstros[], Monster lista_monstros[])
{
	string mensagem = "Por favor, selecione um índice de monstro: ";
	int escolha_monstro = 0;
	do {
		cout << endl << mensagem;
		cin >> escolha_monstro;
		escolha_monstro--;
		mensagem = "Opção inválida / Monstro já adicionado ao deck, tente novamente: ";
	} while (!(verificar_integridade_deck(deck_monstros, escolha_monstro)) || !(indice_monstro_existe(escolha_monstro)));
	return (escolha_monstro);
}
void escolher_monstros(Capsula deck_monstros[], Monster lista_monstros[])
{
	mostrar_todos_monstros(lista_monstros);
	for (int indice = 0; indice < QUANTIDADE_MONSTROS; indice++)
	{
		int escolha_monstro = solicitar_monstro_usuario(deck_monstros, lista_monstros);
		deck_monstros[indice].identificador = escolha_monstro;
		deck_monstros[indice].monstro = lista_monstros[escolha_monstro];
		cout << "Você adicionou " << lista_monstros[escolha_monstro].nome << " ao seu deck." << endl << endl;
	}
}
void sortear_monstros(Capsula deck_monstros[], Monster lista_monstros[], int seed)
{
	srand(time(NULL) + seed);
	for (int indice = 0; indice < QUANTIDADE_MONSTROS; indice++) {
		int novo_monstro = 0;
		do
		{
			novo_monstro = rand() % 12;

		} while (!verificar_integridade_deck(deck_monstros, novo_monstro));
		deck_monstros[indice].identificador = novo_monstro;
		deck_monstros[indice].monstro = lista_monstros[novo_monstro];
	}
}
void definir_level_monstros(Capsula lista_monstros[], int tamanho, int level)
{
	for (int indice = 0; indice < tamanho; indice++) {
		lista_monstros[indice].monstro.level = 75;
	}
}
void configurar_deck_jogador(Jogador& jogador, Monster lista_monstros[], int indice_seed)
{
	switch (solicitar_metodo_preenchimento_deck(jogador))
	{
	case METODO_ESCOLHA:
		escolher_monstros(jogador.deck, lista_monstros);
		break;
	case METODO_SORTEIO:
		sortear_monstros(jogador.deck, lista_monstros, indice_seed);
		break;
	}
	mostrar_deck_jogador(jogador);
	cin.ignore();
	cin.get();
}
void ordernar_pocket(Capsula pocket[])
{
	if (pocket[0].monstro.velocidade < pocket[1].monstro.velocidade)
	{
		Capsula swap = pocket[0];
		pocket[0] = pocket[1];
		pocket[1] = swap;
	}
}
void ordernar_pocket_jogadores(Jogador& jogador_principal, Jogador& jogador_oponente)
{
	ordernar_pocket(jogador_principal.pocket);
	ordernar_pocket(jogador_oponente.pocket);
}

//Funções de jogadores
string solicitar_nome_jogador() {
	string nome;
	cout << "Caro desbravador aventureiro, informe-nos o seu nome: ";
	cin.ignore();
	getline(cin, nome);
	return nome;
}
int solicitar_metodo_preenchimento_deck(Jogador jogador)
{
	int escolha = 0;
	string mensagem = "Sua escolha: ";

	system("cls");
	cout << "Escolhendo monstros para: " + jogador.nome << endl << endl;
	cout << "  __________________________________" << endl;
	cout << " |Escolher monstros ou sortea-los ? |" << endl;
	cout << " |----------------------------------|" << endl;
	cout << " | 1 - Escolher.                    |" << endl;
	cout << " | 2 - Sortear.                     |" << endl;
	cout << " |__________________________________|" << endl;

	do {
		cout << endl << mensagem;
		cin >> escolha;
		mensagem = "Opção inválida, tente novamente: ";
	} while (escolha != 1 && escolha != 2);

	return escolha;
}
void configurar_jogadores_basico(CppmonJogo& novoJogo)
{
	int indice_oponentes_comuns = 1;
	for (int indice = 0; indice < QUANTIDADE_JOGADORES; indice++)
	{
		switch (indice)
		{
		case INDICE_JOGADOR:
			novoJogo.jogadores[indice].id = (indice + 1) * -1;
			novoJogo.jogadores[indice].cod = " P ";
			novoJogo.jogadores[indice].tipo_jogador = JOGADOR_PRINCIPAL;
			novoJogo.jogadores[indice].nome = solicitar_nome_jogador();
			configurar_deck_jogador(novoJogo.jogadores[indice], novoJogo.lista_imagem, indice);
			break;
		case INDICE_LIDER:
			novoJogo.jogadores[indice].id = (indice + 1) * -1;
			novoJogo.jogadores[indice].cod = " L ";
			novoJogo.jogadores[indice].tipo_jogador = OPONENTE_LIDER;
			novoJogo.jogadores[indice].nome = "Líder do Ginásio";
			configurar_deck_jogador(novoJogo.jogadores[indice], novoJogo.lista_imagem, indice);
			definir_level_monstros(novoJogo.jogadores[indice].deck, QUANTIDADE_MONSTROS, 75);
			break;
		default:
			novoJogo.jogadores[indice].id = (indice + 1) * -1;
			novoJogo.jogadores[indice].cod = "E" + to_string(indice_oponentes_comuns) + " ";
			novoJogo.jogadores[indice].tipo_jogador = OPONENTE_COMUM;
			novoJogo.jogadores[indice].nome = "Oponente " + to_string(indice_oponentes_comuns);
			configurar_deck_jogador(novoJogo.jogadores[indice], novoJogo.lista_imagem, indice);
			indice_oponentes_comuns++;
			break;
		}
	}
}
Jogador achar_jogador_por_id(Jogador jogadores[], int tamanho, int id)
{
	Jogador novo_jogador;
	bool nao_encontrou = true;
	for (int indice = 0; indice < tamanho && nao_encontrou; indice++)
	{
		if (jogadores[indice].id == id)
		{
			novo_jogador = jogadores[indice];
			nao_encontrou = false;
		}
	}
	return novo_jogador;
}
void mostrar_jogadores(Jogador jogadores[])
{
	cout << endl;
	for (int indice = 0; indice < QUANTIDADE_JOGADORES; indice++) {
		cout << jogadores[indice].id << endl;
		cout << jogadores[indice].cod << endl;
		cout << jogadores[indice].nome << endl << endl;
	}
}

//Funções visuais
void alterar_cor_texto(int cor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}
void percorrer_string_com_atraso(string mensagem, int tempo)
{
	for (int indice = 0; indice < mensagem.length(); indice++) {
		cout << mensagem.substr(indice, 1);
		Sleep(tempo);
	}
}
void animacao_login()
{
	string usuario = "Gabriel Schade\n";
	string senha = "*****************\n\n";
	string mensagem2 = "AUTENTICANDO USUÁRIO, POR FAVOR AGUARDE... ";

	alterar_cor_texto(10);

	cout << "USUÁRIO: ";
	percorrer_string_com_atraso(usuario, 100);

	cout << "SENHA: ";
	percorrer_string_com_atraso(senha, 100);
	percorrer_string_com_atraso(mensagem2, 25);

	Sleep(2000);
	cout << endl << endl;
}
void mostrar_cabecalho_trabalho(bool mostrar_animacao_login)
{
	alterar_cor_texto(15);

	system("cls");

	cout << "/*" << endl;
	cout << " * VERSÃO 1.1" << endl;
	cout << " * ALGORITMOS E PROGRAMAÇÃO 02" << endl;
	cout << " * PROFESSOR: GABRIEL SCHADE " << endl;
	cout << " * PROGRAMADORES: " << endl;
	cout << " * JOSÉ CARLOS ZANCANARO " << endl;
	cout << " * LUCAS CARDONE " << endl;
	cout << " */";
	cout << endl << endl;

	if (mostrar_animacao_login) animacao_login();

	alterar_cor_texto(15);
}
void mostrar_introducao_jogo()
{
	system("cls");

	alterar_cor_texto(10);
	percorrer_string_com_atraso("Peregrino, seja BEM VINDO ao CPPMON!", 30);
	cout << endl << endl;

	alterar_cor_texto(15);
	percorrer_string_com_atraso("Uma jornada de bravura espera por você!", 50);
	cout << endl << endl;
}
int elemento_para_cor(int elemento)
{
	int cor = 0;
	switch (elemento) {
	case FOGO:		cor = 12;		break;
	case AGUA:		cor = 11;		break;
	case GRAMA:		cor = 10;		break;
	case ELETRICO:	cor = 14;		break;
	case VOADOR:	cor = 7;		break;
	}
	return cor;
}
string elemento_correspondente(int indice)
{
	string elemento = "";
	switch (indice) {
	case FOGO:		elemento = "Fogo";		break;
	case AGUA:		elemento = "Água";		break;
	case GRAMA:		elemento = "Grama";		break;
	case ELETRICO:	elemento = "Elétrico";	break;
	case VOADOR:	elemento = "Voador";	break;
	}
	return (elemento);
}
string preencher_ate_extensao(string inicial, int tamanho, char opcao_preenchimento)
{
	return (inicial + string(tamanho - inicial.length(), opcao_preenchimento));
}
string se_plural(int quantidade, string verdadeiro, string falso)
{
	if (quantidade > 0)
		return (to_string(quantidade) + verdadeiro);
	else
		return (to_string(quantidade) + falso);
}

//Expecto patronum
int easter_egg()
{
	string anomalous_msg1 = "\n\nSYSTEM ALERT:\n\nWe are anomalous!\n\nWe are a region, forgive and forget. Expecto Patronum!\nWait, what is that?\n\nIs that a Monster?? What the f@&*?";
	string anomalous_msg2 = "\n\nYOU HAVE BEEN INVADED ONCE AGAIN...";

	alterar_cor_texto(10);
	srand(time(NULL));

	clock_t inicio = clock();

	while (double(clock() - inicio) / CLOCKS_PER_SEC < 5) {
		cout << rand() % 2 << "\t";
	}

	alterar_cor_texto(12);
	percorrer_string_com_atraso(anomalous_msg1, 50);
	Sleep(2000);

	percorrer_string_com_atraso(anomalous_msg2, 50);
	Sleep(2000);

	return OPCAO_SAIR;
}