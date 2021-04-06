#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define LINHAS 8
#define COLUNAS 8

#define TAM_LINHAS_INTERFACE 15
#define TAM_COLUNAS_INTERFACE 8

#define TECLA_MENU_OPCAO_JOGAR 1
#define TECLA_MENU_OPCAO_TUTORIAL 2
#define TECLA_MENU_OPCAO_SAIR 3

#define TECLA_GAMEPLAY_DIRECIONAL_UP 88
#define TECLA_GAMEPLAY_DIRECIONAL_DOWN 22
#define TECLA_GAMEPLAY_DIRECIONAL_RIGHT 66
#define TECLA_GAMEPLAY_DIRECIONAL_LEFT 44
#define TECLA_GAMEPLAY_ACAO_CAPTURAR 55
#define TECLA_GAMEPLAY_ACAO_SOLTAR 33
#define TECLA_GAMEPLAY_ACAO_CANCELAR_JOGADA 11
#define TECLA_GAMEPLAY_ACAO_SAIR_DO_JOGO 118

#define TECLA_INVALIDA 999

#define TABULEIRO_PONTEIRO_INICIAL 0

#define AVISOS_MOVIMENTO_INVALIDO_POSICAO_OCUPADA " MOVIMENTO DE PECA INVALIDO, ESTA POSICAO JA ESTA OCUPADA."
#define AVISOS_MOVIMENTO_INVALIDO_POSICAO_ERRADA  " MOVIMENTO DE PECA INVALIDO, ESTA PECA NAO PODE FAZER ESTE MOVIMENTO."
#define AVISOS_MOVIMENTAR_PECA_BRANCA " MOVIMENTO DE PECA INVALIDO, VOCE DEVE MOVIMENTAR AS PECAS BRANCAS."
#define AVISOS_MOVIMENTAR_PECA_PRETA " MOVIMENTO DE PECA INVALIDO, VOCE DEVE MOVIMENTAR AS PECAS PRETAS."
#define AVISOS_MOVIMENTAR_SEM_PECA " MOVIMENTO DE PECA INVALIDO, VOCE ESTA TENTANDO CAPTURAR UMA CASA SEM PECA."
#define AVISOS_MOVIMENTAR_CAPTURA_INCORRETA1 " MOVIMENTO DE PECA INVALIDO, VOCE ESTA TENTANDO CAPTURAR MAIS DE UMA PECA POR VEZ."
#define AVISOS_SEM_AVISOS " "


#define PECA_BRANCA 'B'
#define PECA_PRETA 'P'
#define PECA_BRANCA_DAMA 'Q'
#define PECA_PRETA_DAMA 'K'
#define PECA_SELECIONADA 'S'
#define VAZIO ' '
#define PONTEIRO_DIRECIONAL '*'

struct dados_jogador
{
	char nome[50];
	char pecaJogador;
	bool vencedor = false;
};

//Variavel global do ponteiro do jogo comandado pelo direcional --- //
int		globalLinhaPonteiro = 0,									//
		globalColunaPonteiro = 0;									//
char	globalPecaBackupDoPonteiro = ' ';							//
//------------------------------------------------------------------//

//Variavel global da peca selecionada pelo player --//
int		globalLinhaPecaSelecionada = 0,				//
		globalColunaPecaSelecionada = 0;			//
													//
char	globalPecaSelecionada = ' ';				//
//--------------------------------------------------//

//Variavel global do placar do jogo	 ---//
int		globalPlacarPretas = 0,			//
		globalPlacarBrancas = 0;		//
//--------------------------------------//

//Variavel global adicionais do jogo ---------------//
char	globalAvisos[1000] = {' '};					//
													//		
char	globalPecaDeveJogarAgora = PECA_BRANCA;		//
													//
dados_jogador	globalPlayer1,						//
				globalPlayer2;						//
//--------------------------------------------------//


void registraTeclasDoJogo()
{
	//DOC teclas virtuais https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	//DOC registro de teclas https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerhotkey

	//TECLAS DE GAMEPLAY
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x26);//DIRECIONAL PARA CIMA
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x28);//DIRECIONAL PARA BAIXO
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x27);//DIRECIONAL PARA DIREITA
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x25);//DIRECIONAL PARA ESQUERDA
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x70);//F1 = CAPTURA A PECA
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x71);//F2 = SOLTA A PECA
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x72);//F3 = CANCELAR JOGADA
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x78);//F9 = SAIR DO JOGO

	//TECLAS DE MENU
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x61);//FUNCAO NUMERO 1
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x62);//FUNCAO NUMERO 2
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x63);//FUNCAO NUMERO 3
}

void verificaSeVirouRainhaOuRei(char** tabuleiroBackEnd) {

	for (int coluna = 0; coluna < COLUNAS; coluna++)
	{
		if (tabuleiroBackEnd[0][coluna] == PECA_BRANCA)
		{
			tabuleiroBackEnd[0][coluna] = PECA_BRANCA_DAMA;
			globalPecaBackupDoPonteiro = PECA_BRANCA_DAMA;
		}

		if (tabuleiroBackEnd[7][coluna] == PECA_PRETA)
		{
			tabuleiroBackEnd[7][coluna] = PECA_PRETA_DAMA;
			globalPecaBackupDoPonteiro = PECA_PRETA_DAMA;
		}
	}
}

void soltaPecaAposValidacoes(char** tabuleiroBackEnd) {

	//RETIRO A PECA DO LOCAL ANTERIOR 
	tabuleiroBackEnd[globalLinhaPecaSelecionada][globalColunaPecaSelecionada] = VAZIO;

	//SOLTO A PECA NO NOVO LOCAL
	tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaSelecionada;

	//VOLTO O BACKUP DE PECA ONDE O PONTEIRO ESTA LOCALIZADO
	globalPecaBackupDoPonteiro = globalPecaSelecionada;

	globalPecaSelecionada = VAZIO;

}

void intro() {
	system("cls");
	printf("\x1b[37m ############ Bem vindo ao jogo \x1b[31m DamaBreuva\x1b[37m !!! ############\n\n");
	printf("Pressione a tecla numero 1 para Comecar a jogar\n");
	printf("Pressione a tecla numero 2 para acessar o tutorial do jogo\n");
	printf("Pressione a tecla numero 3 para Sair\n");
}

void imprimeTutorial()
{
	system("cls");
	printf("##### Tutorial DamaBreuva ######");

	printf("\n\nControles do Jogo:\n");
	printf("Direcional para cima.\n");
	printf("Direcional para baixo.\n");
	printf("Direcional para esquerda.\n");
	printf("Direcional para direita.\n");
	printf("F1 Seleciona Peca.\n");
	printf("F2 Solta Peca.\n");
	printf("F3 Cancelar Jogada, volta a peca que estava movimentando para sua posicao original.\n");
	printf("F9 Sair do jogo\n");

	printf("\n\nMovimentacao no tabuleiro:\n");
	printf("Direcional para cima.\n");
	printf("Direcional para baixo.\n");
	printf("Direcional para esquerda.\n");
	printf("Direcional para direita.\n");

	printf("\n\nMovimentacao das pecas no tabuleiro:\n");
	printf("Passo 1: Selecionar peca pressionando F1.\n");
	printf("Passo 2: Usar os direcionais para escolher uma casa onde a peca vai ficar.\n");
	printf("Passo 3: Soltar a peca pressionando F2.\n");
	printf("Passo 4: Repetir o processo para todas as jogadas.\n");

	printf("\n\nSignificados de siglas do jogo:\n");
	printf("P = Peca Preta.\n");
	printf("B = Peca Branca.\n");
	printf("W = Peca Branca Dama.\n");
	printf("X = Peca Preta Dama.\n");
	printf("C = Posicao onde foi capturada a Peca.\n");
	printf("T = Ponteiro onde o jogador esta localizado na movimentacão.\n\n");
}

void tabuleiroUserIterface(char** tabuleiroBackEnd) {
	int descontoLinhasInterfaceMatriz = 0;

	system("cls");

	printf("\x1b[37mF1 - \x1b[32mPEGA A PECA  ||  \x1b[37mF2 - \x1b[32mSOLTA A PECA || \x1b[37mF3 - \x1b[32mCANCELA JOGADA || \x1b[37mF9 - \x1b[32mSAIR DO JOGO || \x1b[37mDirecionais - \x1b[32mMovimenta \n");

	printf("\x1b[31m________________________________________________________________________________\n");
	for (int linhasInterface = 1; linhasInterface <= TAM_LINHAS_INTERFACE; linhasInterface++) {
		printf("\n");

		if (linhasInterface % 2 == 0)
		{
			printf("\x1b[31m________________________________________________________________________________\n");
		}
		else {

			descontoLinhasInterfaceMatriz++;

			for (int colunasInterface = 0; colunasInterface < TAM_COLUNAS_INTERFACE; colunasInterface++)
			{
				if (tabuleiroBackEnd[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface] == PECA_BRANCA) {
						printf("\x1b[37m    O    ");
				}
				else if (tabuleiroBackEnd[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface] == PECA_PRETA) {
						printf("\x1b[34m    O    ");
				}
				else if (tabuleiroBackEnd[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface] == PECA_BRANCA_DAMA) {
						printf("\x1b[37m    O+   ");
				}
				else if (tabuleiroBackEnd[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface] == PECA_PRETA_DAMA) {

						printf("\x1b[34m    O+   ");
				}
				else if (tabuleiroBackEnd[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface] == PONTEIRO_DIRECIONAL) {
					printf("\x1b[32m    %c    ", tabuleiroBackEnd[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}
				else {

					printf("\x1b[37m    %c    ", tabuleiroBackEnd[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}

				if (colunasInterface < 8) {
					printf("\x1b[31m|");
				}
			}
		}
	}
	printf("\n\x1b[31m________________________________________________________________________________\n");
	printf("\x1b[32mPlacar \x1b[34m%s: %d",globalPlayer2.nome, globalPlacarPretas);
	printf("\n\x1b[32mPlacar \x1b[37m%s: %d\n", globalPlayer1.nome, globalPlacarBrancas);
	printf("\x1b[32mAVISOS:\x1b[31m %s", globalAvisos);
}

char** organizaTabuleiroBackEndIncial() {
	char** matriz = NULL;

	globalLinhaPonteiro = 0;
	globalColunaPonteiro = 0;
	globalPecaBackupDoPonteiro = VAZIO;
	globalLinhaPecaSelecionada = 0;
	globalColunaPecaSelecionada = 0;
	globalPecaSelecionada = VAZIO;
	globalPlacarPretas = 0;
	globalPlacarBrancas = 0;

	matriz = (char**)malloc(LINHAS * sizeof(char*));

	for (int i = 0; i < LINHAS; ++i)
		matriz[i] = (char*)malloc(COLUNAS * sizeof(char));


	for (int l = 0; l < LINHAS; l++)
	{
		for (int c = 0; c < COLUNAS; c++)
		{
			if (l == 0) {

				if (c % 2 == 0)
					matriz[l][c] = PECA_PRETA;
				else
					matriz[l][c] = VAZIO;
			}
			else if (l == 1) {
				if (c % 2 == 0)
					matriz[l][c] = VAZIO;
				else
					matriz[l][c] = PECA_PRETA;
			}
			else if (l == 2) {
				if (c % 2 == 0)
					matriz[l][c] = PECA_PRETA;
				else
					matriz[l][c] = VAZIO;
			}
			else if (l == 5) {

				if (c % 2 == 0)
					matriz[l][c] = VAZIO;
				else
					matriz[l][c] = PECA_BRANCA;
			}
			else if (l == 6) {
				if (c % 2 == 0)
					matriz[l][c] = PECA_BRANCA;
				else
					matriz[l][c] = VAZIO;
			}
			else if (l == 7) {
				if (c % 2 == 0)
					matriz[l][c] = VAZIO;
				else
					matriz[l][c] = PECA_BRANCA;
			}
			else {
				matriz[l][c] = VAZIO;
			}
		}
	}
	return matriz;
}

void pegaPeca(char** tabuleiroBackEnd) {

	if (globalPecaBackupDoPonteiro != VAZIO && globalPecaSelecionada == VAZIO)
	{
		//CAPTURO PECA
		globalPecaSelecionada = globalPecaBackupDoPonteiro;

		//ADICIONO O NO LOCAL 
		globalPecaBackupDoPonteiro = PECA_SELECIONADA;

		//GUARDO A LOCALIZACAO DA PECA ANTERIOR
		globalLinhaPecaSelecionada = globalLinhaPonteiro;
		globalColunaPecaSelecionada = globalColunaPonteiro;
	}
}

void validarJogadaPecaComumParaEliminarPecaInimiga(char** tabuleiroBackEnd) {

	//VERIFICO SE AS JOGADAS ESTAO SENDO PARA CAPTURAR PECA INIMIGA A DIREITA, AVANÇANDO O TABULEIRO
	if ((globalLinhaPecaSelecionada + 2) == globalLinhaPonteiro && (globalColunaPecaSelecionada + 2) == globalColunaPonteiro) {

		if ( ( (tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada + 1] == PECA_BRANCA ||
			    tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada + 1] == PECA_BRANCA_DAMA) && globalPecaSelecionada == PECA_PRETA) ||
			 ( (tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada + 1] == PECA_PRETA ||
				tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada + 1] == PECA_PRETA_DAMA) && globalPecaSelecionada == PECA_BRANCA) ) {

			//ELIMINO PECA INIMIGA
			tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada + 1] = VAZIO;

			if (globalPecaSelecionada == PECA_PRETA)
				globalPlacarPretas++;
			else
				globalPlacarBrancas++;

			soltaPecaAposValidacoes(tabuleiroBackEnd);

			return;
		}
	}

	//VERIFICO SE AS JOGADAS ESTAO SENDO PARA CAPTURAR PECA INIMIGA A ESQUERDA, AVANÇANDO O TABULEIRO
	if ((globalLinhaPecaSelecionada + 2) == globalLinhaPonteiro && (globalColunaPecaSelecionada - 2) == globalColunaPonteiro) {

		if ( ( (tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada - 1] == PECA_BRANCA ||
				tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada - 1] == PECA_BRANCA_DAMA) && globalPecaSelecionada == PECA_PRETA) ||
			 ( (tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada - 1] == PECA_PRETA ||
				tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada - 1] == PECA_PRETA_DAMA) && globalPecaSelecionada == PECA_BRANCA) ) {

			//ELIMINO PECA INIMIGA
			tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada - 1] = VAZIO;

			if (globalPecaSelecionada == PECA_PRETA)
				globalPlacarPretas++;
			else
				globalPlacarBrancas++;

			soltaPecaAposValidacoes(tabuleiroBackEnd);

			return;
		}
	}

	//VERIFICO SE AS JOGADAS ESTAO SENDO PARA CAPTURAR PECA INIMIGA A ESQUERDA, RETROCEDENDO O TABULEIRO
	if ((globalLinhaPecaSelecionada - 2) == globalLinhaPonteiro && (globalColunaPecaSelecionada - 2) == globalColunaPonteiro) {


		if ( ( (tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada - 1] == PECA_BRANCA ||
			    tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada - 1] == PECA_BRANCA_DAMA) && globalPecaSelecionada == PECA_PRETA) ||
			( ( tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada - 1] == PECA_PRETA ||
			    tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada - 1] == PECA_PRETA_DAMA) && globalPecaSelecionada == PECA_BRANCA)) {

			//ELIMINO PECA INIMIGA
			tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada - 1] = VAZIO;

			if (globalPecaSelecionada == PECA_PRETA)
				globalPlacarPretas++;
			else
				globalPlacarBrancas++;

			soltaPecaAposValidacoes(tabuleiroBackEnd);

			return;
		}
	}

	//VERIFICO SE AS JOGADAS ESTAO SENDO PARA CAPTURAR PECA INIMIGA A DIREITA, RETROCEDENDO O TABULEIRO
	if ((globalLinhaPecaSelecionada - 2) == globalLinhaPonteiro && (globalColunaPecaSelecionada + 2) == globalColunaPonteiro) {

		if ( ( (tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada + 1] == PECA_BRANCA ||
			    tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada + 1] == PECA_BRANCA_DAMA) && globalPecaSelecionada == PECA_PRETA) ||
			( ( tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada + 1] == PECA_PRETA ||
				tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada + 1] == PECA_PRETA_DAMA) && globalPecaSelecionada == PECA_BRANCA)) {

			//ELIMINO PECA INIMIGA
			tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada + 1] = VAZIO;
			
			if (globalPecaSelecionada == PECA_PRETA)
				globalPlacarPretas++;
			else
				globalPlacarBrancas++;

			soltaPecaAposValidacoes(tabuleiroBackEnd);

			return;
		}
	}

	memcpy(globalAvisos, AVISOS_MOVIMENTO_INVALIDO_POSICAO_ERRADA, strlen(AVISOS_MOVIMENTO_INVALIDO_POSICAO_ERRADA) + 1);
}

void validarMovimentoPecaSimples(char** tabuleiroBackEnd) {

	//VERIFICO SE O lOCAL ATUAL PARA SOLTAR PECA TEM QUE ESTAR VAZIO
	if (globalPecaBackupDoPonteiro == VAZIO)
	{
		if (globalPecaSelecionada == PECA_BRANCA)
		{
			//VERIFICO SE AS JOGADAS ESTAO SENDO NAS DIAGONAIS
			if ((globalLinhaPecaSelecionada - 1) == globalLinhaPonteiro && (globalColunaPecaSelecionada + 1) == globalColunaPonteiro ||
				(globalLinhaPecaSelecionada - 1) == globalLinhaPonteiro && (globalColunaPecaSelecionada - 1) == globalColunaPonteiro) {

				soltaPecaAposValidacoes(tabuleiroBackEnd);

				return;
			}
		}

		if (globalPecaSelecionada == PECA_PRETA) {
			//VERIFICO SE AS JOGADAS ESTAO SENDO NAS DIAGONAIS
			if ((globalLinhaPecaSelecionada + 1) == globalLinhaPonteiro && (globalColunaPecaSelecionada + 1) == globalColunaPonteiro ||
				(globalLinhaPecaSelecionada + 1) == globalLinhaPonteiro && (globalColunaPecaSelecionada - 1) == globalColunaPonteiro) {

				soltaPecaAposValidacoes(tabuleiroBackEnd);

				return;
			}
		}

		validarJogadaPecaComumParaEliminarPecaInimiga(tabuleiroBackEnd);
	}
	else {
		memcpy(globalAvisos, AVISOS_MOVIMENTO_INVALIDO_POSICAO_OCUPADA, strlen(AVISOS_MOVIMENTO_INVALIDO_POSICAO_OCUPADA) + 1);
	}
}

void validarJogadaDama(char** tabuleiroBackEnd) {
	int linhaPecaInimiga = 0, 
		colunaPecaInimiga = 0;
	bool sairLoopEncadeado = false;

	//VALIDACAO DIAGONAL DIREITA A BAIXO
	for (int linha = globalLinhaPonteiro, coluna = globalColunaPonteiro, sairLoopEncadeado = false; linha < LINHAS  && coluna < COLUNAS && sairLoopEncadeado == false; linha++, coluna++) {

		//MOVIMENTO SEM CAPTURA
		if (tabuleiroBackEnd[linha][coluna] != VAZIO && globalPecaBackupDoPonteiro == VAZIO) {

			if (tabuleiroBackEnd[linha][coluna] == PECA_SELECIONADA)
			{
				soltaPecaAposValidacoes(tabuleiroBackEnd);
				return;
			}
			else {
				//MOVIMENTO COM CAPTURA
				if (((tabuleiroBackEnd[linha][coluna] == PECA_PRETA || tabuleiroBackEnd[linha][coluna] == PECA_PRETA_DAMA) && globalPecaSelecionada == PECA_BRANCA_DAMA) ||
					((tabuleiroBackEnd[linha][coluna] == PECA_BRANCA || tabuleiroBackEnd[linha][coluna] == PECA_BRANCA_DAMA) && globalPecaSelecionada == PECA_PRETA_DAMA)) {

					linhaPecaInimiga = linha;
					colunaPecaInimiga = coluna;

					linha++;
					coluna++;

					for (linha, coluna; linha < LINHAS && coluna < COLUNAS && sairLoopEncadeado == false; linha++, coluna++) {

						if (tabuleiroBackEnd[linha][coluna] != VAZIO) {

							if (tabuleiroBackEnd[linha][coluna] == PECA_SELECIONADA)
							{
								//ELIMINO PECA INIMIGA
								tabuleiroBackEnd[linhaPecaInimiga][colunaPecaInimiga] = VAZIO;

								if (globalPecaSelecionada == PECA_PRETA_DAMA)
									globalPlacarPretas++;
								else
									globalPlacarBrancas++;

								soltaPecaAposValidacoes(tabuleiroBackEnd);
								return;
							}
							else
							{
								memcpy(globalAvisos, AVISOS_MOVIMENTAR_CAPTURA_INCORRETA1, strlen(AVISOS_MOVIMENTAR_CAPTURA_INCORRETA1) + 1);
								sairLoopEncadeado = true;
							}
						}

					}
				}
				else {
					if(tabuleiroBackEnd[linha][coluna] != PONTEIRO_DIRECIONAL)
						break;
				}
			}
		}
	}
	
	//VALIDACAO DIAGONAL ESQUERDA A BAIXO
	for (int linha = globalLinhaPonteiro, coluna = globalColunaPonteiro, sairLoopEncadeado = false; linha < LINHAS && coluna >= 0 && sairLoopEncadeado == false; linha++, coluna--) {

		//MOVIMENTO SEM CAPTURA
		if (tabuleiroBackEnd[linha][coluna] != VAZIO && globalPecaBackupDoPonteiro == VAZIO) {

			if (tabuleiroBackEnd[linha][coluna] == PECA_SELECIONADA)
			{
				soltaPecaAposValidacoes(tabuleiroBackEnd);
				return;
			}
			else {
				//MOVIMENTO COM CAPTURA
				if (((tabuleiroBackEnd[linha][coluna] == PECA_PRETA || tabuleiroBackEnd[linha][coluna] == PECA_PRETA_DAMA) && globalPecaSelecionada == PECA_BRANCA_DAMA) ||
					((tabuleiroBackEnd[linha][coluna] == PECA_BRANCA || tabuleiroBackEnd[linha][coluna] == PECA_BRANCA_DAMA) && globalPecaSelecionada == PECA_PRETA_DAMA)) {

					linhaPecaInimiga = linha;
					colunaPecaInimiga = coluna;

					linha++;
					coluna--;

					for (linha, coluna; linha < LINHAS && coluna >= 0 && sairLoopEncadeado == false; linha++, coluna--) {

						if (tabuleiroBackEnd[linha][coluna] != VAZIO) {

							if (tabuleiroBackEnd[linha][coluna] == PECA_SELECIONADA)
							{
								//ELIMINO PECA INIMIGA
								tabuleiroBackEnd[linhaPecaInimiga][colunaPecaInimiga] = VAZIO;

								if (globalPecaSelecionada == PECA_PRETA_DAMA)
									globalPlacarPretas++;
								else
									globalPlacarBrancas++;

								soltaPecaAposValidacoes(tabuleiroBackEnd);
								return;
							}
							else
							{
								memcpy(globalAvisos, AVISOS_MOVIMENTAR_CAPTURA_INCORRETA1, strlen(AVISOS_MOVIMENTAR_CAPTURA_INCORRETA1) + 1);
								sairLoopEncadeado = true;
							}
						}

					}
				}
				else
				{
					if (tabuleiroBackEnd[linha][coluna] != PONTEIRO_DIRECIONAL)
						break;
				}
			}
		}
	}

	//VALIDACAO DIAGONAL DIREITA ACIMA
	for (int linha = globalLinhaPonteiro, coluna = globalColunaPonteiro, sairLoopEncadeado = false; linha >= 0 && coluna < COLUNAS && sairLoopEncadeado == false; linha--, coluna++) {

		//MOVIMENTO SEM CAPTURA
		if (tabuleiroBackEnd[linha][coluna] != VAZIO && globalPecaBackupDoPonteiro == VAZIO) {

			if (tabuleiroBackEnd[linha][coluna] == PECA_SELECIONADA)
			{
				soltaPecaAposValidacoes(tabuleiroBackEnd);
				return;
			}
			else {
				//MOVIMENTO COM CAPTURA
				if (((tabuleiroBackEnd[linha][coluna] == PECA_PRETA || tabuleiroBackEnd[linha][coluna] == PECA_PRETA_DAMA) && globalPecaSelecionada == PECA_BRANCA_DAMA) ||
					((tabuleiroBackEnd[linha][coluna] == PECA_BRANCA || tabuleiroBackEnd[linha][coluna] == PECA_BRANCA_DAMA) && globalPecaSelecionada == PECA_PRETA_DAMA)) {

					linhaPecaInimiga = linha;
					colunaPecaInimiga = coluna;

					linha--;
					coluna++;

					for (linha, coluna; linha >= 0 && coluna < COLUNAS && sairLoopEncadeado == false; linha--, coluna++) {

						if (tabuleiroBackEnd[linha][coluna] != VAZIO) {

							if (tabuleiroBackEnd[linha][coluna] == PECA_SELECIONADA)
							{
								//ELIMINO PECA INIMIGA
								tabuleiroBackEnd[linhaPecaInimiga][colunaPecaInimiga] = VAZIO;

								if (globalPecaSelecionada == PECA_PRETA_DAMA)
									globalPlacarPretas++;
								else
									globalPlacarBrancas++;

								soltaPecaAposValidacoes(tabuleiroBackEnd);

								return;
							}
							else
							{
								memcpy(globalAvisos, AVISOS_MOVIMENTAR_CAPTURA_INCORRETA1, strlen(AVISOS_MOVIMENTAR_CAPTURA_INCORRETA1) + 1);
								sairLoopEncadeado = true;
							}
						}

					}
				}
				else {
					if (tabuleiroBackEnd[linha][coluna] != PONTEIRO_DIRECIONAL)
						break;
				}
			}
		}
	}

	//VALIDACAO DIAGONAL ESQUERDA ACIMA
	for (int linha = globalLinhaPonteiro, coluna = globalColunaPonteiro, sairLoopEncadeado = false; linha >= 0 && coluna >= 0 && sairLoopEncadeado == false; linha--, coluna--) {

		//MOVIMENTO SEM CAPTURA
		if (tabuleiroBackEnd[linha][coluna] != VAZIO && globalPecaBackupDoPonteiro == VAZIO) {

			if (tabuleiroBackEnd[linha][coluna] == PECA_SELECIONADA)
			{
				soltaPecaAposValidacoes(tabuleiroBackEnd);
			}
			else {
				//MOVIMENTO COM CAPTURA
				if (((tabuleiroBackEnd[linha][coluna] == PECA_PRETA || tabuleiroBackEnd[linha][coluna] == PECA_PRETA_DAMA) && globalPecaSelecionada == PECA_BRANCA_DAMA) ||
					((tabuleiroBackEnd[linha][coluna] == PECA_BRANCA || tabuleiroBackEnd[linha][coluna] == PECA_BRANCA_DAMA) && globalPecaSelecionada == PECA_PRETA_DAMA)) {

					linhaPecaInimiga = linha;
					colunaPecaInimiga = coluna;

					linha--;
					coluna--;

					for (linha, coluna; linha >= 0 && coluna >= 0 && sairLoopEncadeado == false; linha--, coluna--) {

						if (tabuleiroBackEnd[linha][coluna] != VAZIO) {

							if (tabuleiroBackEnd[linha][coluna] == PECA_SELECIONADA)
							{
								//ELIMINO PECA INIMIGA
								tabuleiroBackEnd[linhaPecaInimiga][colunaPecaInimiga] = VAZIO;

								if (globalPecaSelecionada == PECA_PRETA_DAMA)
									globalPlacarPretas++;
								else
									globalPlacarBrancas++;

								soltaPecaAposValidacoes(tabuleiroBackEnd);

								return;
							}
							else
							{
								memcpy(globalAvisos, AVISOS_MOVIMENTAR_CAPTURA_INCORRETA1, strlen(AVISOS_MOVIMENTAR_CAPTURA_INCORRETA1) + 1);
								sairLoopEncadeado = true;
							}
						}

					}
				}
				else {
					if (tabuleiroBackEnd[linha][coluna] != PONTEIRO_DIRECIONAL)
						break;
				}
			}
		}
	}
}

void soltaPecaJogador(char** tabuleiroBackEnd) {

	if (globalPecaSelecionada == PECA_PRETA || globalPecaSelecionada == PECA_BRANCA)
	{
		validarMovimentoPecaSimples(tabuleiroBackEnd);
	}

	if (globalPecaSelecionada == PECA_BRANCA_DAMA || globalPecaSelecionada == PECA_PRETA_DAMA)
	{
		validarJogadaDama(tabuleiroBackEnd);
	}

	verificaSeVirouRainhaOuRei(tabuleiroBackEnd);
}

void moveParaDireita(char** tabuleiroBackEnd) {

	if (globalColunaPonteiro >= 0 && globalColunaPonteiro < 7)
	{
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
		globalColunaPonteiro++;
		globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = PONTEIRO_DIRECIONAL;
	}
}

void moveParaEsquerda(char** tabuleiroBackEnd) {
	if (globalColunaPonteiro > 0 && globalColunaPonteiro <= 7)
	{
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
		globalColunaPonteiro--;
		globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = PONTEIRO_DIRECIONAL;
	}
}

void moveParaCima(char** tabuleiroBackEnd) {
	if (globalLinhaPonteiro > 0 && globalLinhaPonteiro <= 7)
	{
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
		globalLinhaPonteiro--;
		globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = PONTEIRO_DIRECIONAL;
	}
}

void moveParaBaixo(char** tabuleiroBackEnd) {
	if (globalLinhaPonteiro >= 0 && globalLinhaPonteiro < 7)
	{
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
		globalLinhaPonteiro++;
		globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = PONTEIRO_DIRECIONAL;
	}
}

void cancelaJogada(char** tabuleiroBackEnd) {

	if (globalPecaSelecionada != VAZIO){
		tabuleiroBackEnd[globalLinhaPecaSelecionada][globalColunaPecaSelecionada] = globalPecaSelecionada;

		if (globalPecaBackupDoPonteiro == PECA_SELECIONADA)
		{
			globalPecaBackupDoPonteiro = globalPecaSelecionada;
		}

		globalPecaSelecionada = VAZIO;
	}
}

void movimentacaoNoTabuleiroBackEnd(char** tabuleiroBackEnd, int movimento) {

	if (movimento == TABULEIRO_PONTEIRO_INICIAL)
	{
		globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = PONTEIRO_DIRECIONAL;
	}

	if (movimento == TECLA_GAMEPLAY_ACAO_CAPTURAR)
		pegaPeca(tabuleiroBackEnd);
	
	if (movimento == TECLA_GAMEPLAY_ACAO_SOLTAR)
		soltaPecaJogador(tabuleiroBackEnd);

	if (movimento == TECLA_GAMEPLAY_ACAO_CANCELAR_JOGADA)
		cancelaJogada(tabuleiroBackEnd);

	if (movimento == TECLA_GAMEPLAY_DIRECIONAL_RIGHT)
		moveParaDireita(tabuleiroBackEnd);

	if (movimento == TECLA_GAMEPLAY_DIRECIONAL_LEFT)
		moveParaEsquerda(tabuleiroBackEnd);

	if (movimento == TECLA_GAMEPLAY_DIRECIONAL_UP)
		moveParaCima(tabuleiroBackEnd);

	if (movimento == TECLA_GAMEPLAY_DIRECIONAL_DOWN)
		moveParaBaixo(tabuleiroBackEnd);
}

bool ehGanhador() {

	if (globalPlacarPretas == 12) {

		system("cls");
		printf("\x1b[37m ############ Parabens \x1b[31m %s, voce venceu o Jogo\x1b[37m !!! ############\n\n", globalPlayer2.nome);
		return true;
	}

	if (globalPlacarBrancas == 12) {

		system("cls");
		printf("\x1b[37m ############ Parabens \x1b[31m %s, voce venceu o Jogo\x1b[37m !!! ############\n\n", globalPlayer1.nome);
		return true;
	}

	return false;

}

void capturaDadosJogador() {
	system("cls");
	size_t tam;
	printf("\x1b[37mDigite o nome do jogador que vai jogar com a peca BRANCA:");
	fgets(globalPlayer1.nome, 40, stdin);
	globalPlayer1.pecaJogador = 'B';

	tam = strlen(globalPlayer1.nome);
	globalPlayer1.nome[tam-1] = '\0';

	printf("\n\x1b[34mDigite o nome do jogador que vai jogar com a peca PRETA:");
	fgets(globalPlayer2.nome, 40, stdin);
	globalPlayer2.pecaJogador = 'P';
	tam = strlen(globalPlayer2.nome);
	globalPlayer2.nome[tam-1] = '\0';
}

int capturaTeclado() {
	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.message == WM_HOTKEY)
		{
			//DIRECIONAIS
			if (msg.lParam == 2490368)
				return TECLA_GAMEPLAY_DIRECIONAL_UP;
			if (msg.lParam == 2621440)
				return TECLA_GAMEPLAY_DIRECIONAL_DOWN;
			if (msg.lParam == 2424832)
				return TECLA_GAMEPLAY_DIRECIONAL_LEFT;
			if (msg.lParam == 2555904)
				return TECLA_GAMEPLAY_DIRECIONAL_RIGHT;

			//ACOES
			if (msg.lParam == 7340032)
				return TECLA_GAMEPLAY_ACAO_CAPTURAR;
			if (msg.lParam == 7405568)
				return TECLA_GAMEPLAY_ACAO_SOLTAR;
			if (msg.lParam == 7471104)
				return TECLA_GAMEPLAY_ACAO_CANCELAR_JOGADA;
			if (msg.lParam == 7864320)
				return TECLA_GAMEPLAY_ACAO_SAIR_DO_JOGO;

			//TECLA MENU
			if (msg.lParam == 6356992)
				return TECLA_MENU_OPCAO_JOGAR;
			if (msg.lParam == 6422528)
				return TECLA_MENU_OPCAO_TUTORIAL;
			if (msg.lParam == 6488064)
				return TECLA_MENU_OPCAO_SAIR;
		}
	}

	return TECLA_INVALIDA;
}

int main() {
	char** tabuleiroBackEnd; 
	int teclaDirecional = 0;

	registraTeclasDoJogo();

	while (teclaDirecional != TECLA_MENU_OPCAO_SAIR) {

		intro();
		teclaDirecional = capturaTeclado();

		switch (teclaDirecional) {

			case TECLA_MENU_OPCAO_JOGAR:

				capturaDadosJogador();
				tabuleiroBackEnd = organizaTabuleiroBackEndIncial();
				movimentacaoNoTabuleiroBackEnd(tabuleiroBackEnd, TABULEIRO_PONTEIRO_INICIAL);

				while (teclaDirecional != TECLA_GAMEPLAY_ACAO_SAIR_DO_JOGO && ehGanhador() == false) {
					tabuleiroUserIterface(tabuleiroBackEnd);
					teclaDirecional = capturaTeclado();
					movimentacaoNoTabuleiroBackEnd(tabuleiroBackEnd, teclaDirecional);
				}

			break;

			case TECLA_MENU_OPCAO_TUTORIAL:
				imprimeTutorial();
			break;

			default:
				break;
		}

		system("pause");
	}
}

