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

#define TABULEIRO_PONTEIRO_INICIAL 0

#define ANSI_COLOR_RED      "\x1b[31m" //cores em ANSI utilizadas 
#define ANSI_COLOR_GRAY     "\e[0;37m"

struct dados_jogador
{
	char nome[50];
	char pecaJogador;
	bool vencedor = false;
};

//Variavel global do ponteiro do jogo comandado pelo direcional
int globalLinhaPonteiro = 0, 
	globalColunaPonteiro = 0;
char globalPecaBackupDoPonteiro = ' ';

//Variavel global da peca selecionada pelo player
int globalLinhaPecaCapturada = 0, 
	globalColunaPecaCapturada = 0;

char globalPecaCapturada = ' ';

//Variavel global do placar do jogo
int globalPlacarPretas = 0, 
	globalPlacarBrancas = 0;

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

void intro() {
	system("cls");
	printf("\x1b[37m ############ Bem vindo ao jogo \x1b[31m DamaBreuva\x1b[37m !!! ############\n\n");
	printf("Pressione a tecla numero 1 para Comecar a jogar\n");
	printf("Pressione a tecla numero 2 para acessar o tutorial do jogo\n");
	printf("Pressione a tecla numero 3 para Sair\n");
	
}

void ImprimeTutorial()
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
				if (linhasInterface == 1) {
						printf("\x1b[37m    %c    ", tabuleiroBackEnd[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}
				else if (linhasInterface == 3) {
						printf("\x1b[37m    %c    ", tabuleiroBackEnd[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}
				else if (linhasInterface == 5) {
						printf("\x1b[37m    %c    ", tabuleiroBackEnd[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}
				else if (linhasInterface == 11) {

						printf("\x1b[37m    %c    ", tabuleiroBackEnd[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}
				else if (linhasInterface == 13) {

						printf("\x1b[37m    %c    ", tabuleiroBackEnd[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}
				else if (linhasInterface == 15) {

						printf("\x1b[37m    %c    ", tabuleiroBackEnd[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
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
	printf("\n\x1b[32mPlacar PRETAS:\x1b[37m %d", globalPlacarPretas);
	printf("\n\x1b[32mPlacar BRANCAS:\x1b[37m %d\n", globalPlacarBrancas);
}

char** organizaTabuleiroBackEndIncial() {
	char** matriz = NULL;


	globalLinhaPonteiro = 0,
	globalColunaPonteiro = 0;
	globalPecaBackupDoPonteiro = ' ';
	globalLinhaPecaCapturada = 0,
	globalColunaPecaCapturada = 0;
	globalPecaCapturada = ' ';
	globalPlacarPretas = 0,
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
					matriz[l][c] = 'P';
				else
					matriz[l][c] = ' ';
			}
			else if (l == 1) {
				if (c % 2 == 0)
					matriz[l][c] = ' ';
				else
					matriz[l][c] = 'P';
			}
			else if (l == 2) {
				if (c % 2 == 0)
					matriz[l][c] = 'P';
				else
					matriz[l][c] = ' ';
			}
			else if (l == 5) {

				if (c % 2 == 0)
					matriz[l][c] = ' ';
				else
					matriz[l][c] = 'B';
			}
			else if (l == 6) {
				if (c % 2 == 0)
					matriz[l][c] = 'B';
				else
					matriz[l][c] = ' ';
			}
			else if (l == 7) {
				if (c % 2 == 0)
					matriz[l][c] = ' ';
				else
					matriz[l][c] = 'B';
			}
			else {
				matriz[l][c] = ' ';
			}
		}
	}
	return matriz;
}

void PegaPeca(char** tabuleiroBackEnd) {

	if (globalPecaBackupDoPonteiro != ' ' && globalPecaCapturada == ' ')
	{
		//CAPTURO PECA
		globalPecaCapturada = globalPecaBackupDoPonteiro;

		//ADICIONO O NO LOCAL 
		globalPecaBackupDoPonteiro = 'C';

		//GUARDO A LOCALIZACAO DA PECA ANTERIOR
		globalLinhaPecaCapturada = globalLinhaPonteiro;
		globalColunaPecaCapturada = globalColunaPonteiro;
	}
}

void validarMovimentoPecaPreta(char** tabuleiroBackEnd) {

	//VERIFICO SE O lOCAL ATUAL PARA SOLTAR PECA TEM QUE ESTAR VAZIO
	if (globalPecaBackupDoPonteiro == ' ')
	{
		//VERIFICO SE AS JOGADAS ESTAO SENDO NAS DIAGONAIS
		if ((globalLinhaPecaCapturada + 1) == globalLinhaPonteiro && (globalColunaPecaCapturada + 1) == globalColunaPonteiro ||
			(globalLinhaPecaCapturada + 1) == globalLinhaPonteiro && (globalColunaPecaCapturada - 1) == globalColunaPonteiro) {

			//RETIRO A PECA DO LOCAL ANTERIOR 
			tabuleiroBackEnd[globalLinhaPecaCapturada][globalColunaPecaCapturada] = ' ';

			//SOLTO A PECA NO NOVO LOCAL
			tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaCapturada;

			//VOLTO O BACKUP DE PECA ONDE O PONTEIRO ESTA LOCALIZADO
			globalPecaBackupDoPonteiro = globalPecaCapturada;

			globalPecaCapturada = ' ';
		}

		//VERIFICO SE AS JOGADAS ESTAO SENDO PARA CAPTURAR PECA INIMIGA A DIREITA, AVANÇANDO O TABULEIRO
		if ((globalLinhaPecaCapturada + 2) == globalLinhaPonteiro && (globalColunaPecaCapturada + 2) == globalColunaPonteiro) {

			if (tabuleiroBackEnd[globalLinhaPecaCapturada + 1][globalColunaPecaCapturada + 1] == 'B') {

				//ELIMINO PECA INIMIGA (BRANCA), 'TO DO' FAZER UM PLACAR
				tabuleiroBackEnd[globalLinhaPecaCapturada + 1][globalColunaPecaCapturada + 1] = ' ';
				globalPlacarPretas++;

				//RETIRO A PECA DO LOCAL ANTERIOR 
				tabuleiroBackEnd[globalLinhaPecaCapturada][globalColunaPecaCapturada] = ' ';

				//SOLTO A PECA NO NOVO LOCAL
				tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaCapturada;

				//VOLTO O BACKUP DE PECA ONDE O PONTEIRO ESTA LOCALIZADO
				globalPecaBackupDoPonteiro = globalPecaCapturada;

				globalPecaCapturada = ' ';
			}

		}

		//VERIFICO SE AS JOGADAS ESTAO SENDO PARA CAPTURAR PECA INIMIGA A ESQUERDA, AVANÇANDO O TABULEIRO
		if ((globalLinhaPecaCapturada + 2) == globalLinhaPonteiro && (globalColunaPecaCapturada - 2) == globalColunaPonteiro) {

			if (tabuleiroBackEnd[globalLinhaPecaCapturada + 1][globalColunaPecaCapturada - 1] == 'B') {

				//ELIMINO PECA INIMIGA (BRANCA), 'TO DO' FAZER UM PLACAR
				tabuleiroBackEnd[globalLinhaPecaCapturada + 1][globalColunaPecaCapturada - 1] = ' ';
				globalPlacarPretas++;

				//RETIRO A PECA DO LOCAL ANTERIOR 
				tabuleiroBackEnd[globalLinhaPecaCapturada][globalColunaPecaCapturada] = ' ';

				//SOLTO A PECA NO NOVO LOCAL
				tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaCapturada;

				//VOLTO O BACKUP DE PECA ONDE O PONTEIRO ESTA LOCALIZADO
				globalPecaBackupDoPonteiro = globalPecaCapturada;

				globalPecaCapturada = ' ';
			}
		}


		//VERIFICO SE AS JOGADAS ESTAO SENDO PARA CAPTURAR PECA INIMIGA A ESQUERDA, RETROCEDENDO O TABULEIRO
		if ((globalLinhaPecaCapturada - 2) == globalLinhaPonteiro && (globalColunaPecaCapturada -2) == globalColunaPonteiro) {

			if (tabuleiroBackEnd[globalLinhaPecaCapturada - 1][globalColunaPecaCapturada - 1] == 'B') {

				//ELIMINO PECA INIMIGA (BRANCA), 'TO DO' FAZER UM PLACAR
				tabuleiroBackEnd[globalLinhaPecaCapturada - 1][globalColunaPecaCapturada - 1] = ' ';
				globalPlacarPretas++;

				//RETIRO A PECA DO LOCAL ANTERIOR 
				tabuleiroBackEnd[globalLinhaPecaCapturada][globalColunaPecaCapturada] = ' ';

				//SOLTO A PECA NO NOVO LOCAL
				tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaCapturada;

				//VOLTO O BACKUP DE PECA ONDE O PONTEIRO ESTA LOCALIZADO
				globalPecaBackupDoPonteiro = globalPecaCapturada;

				globalPecaCapturada = ' ';
			}
		}

		//VERIFICO SE AS JOGADAS ESTAO SENDO PARA CAPTURAR PECA INIMIGA A DIREITA, RETROCEDENDO O TABULEIRO
		if ((globalLinhaPecaCapturada - 2) == globalLinhaPonteiro && (globalColunaPecaCapturada + 2) == globalColunaPonteiro) {

			if (tabuleiroBackEnd[globalLinhaPecaCapturada - 1][globalColunaPecaCapturada + 1] == 'B') {

				//ELIMINO PECA INIMIGA (BRANCA), 'TO DO' FAZER UM PLACAR
				tabuleiroBackEnd[globalLinhaPecaCapturada - 1][globalColunaPecaCapturada + 1] = ' ';
				globalPlacarPretas++;

				//RETIRO A PECA DO LOCAL ANTERIOR 
				tabuleiroBackEnd[globalLinhaPecaCapturada][globalColunaPecaCapturada] = ' ';

				//SOLTO A PECA NO NOVO LOCAL
				tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaCapturada;

				//VOLTO O BACKUP DE PECA ONDE O PONTEIRO ESTA LOCALIZADO
				globalPecaBackupDoPonteiro = globalPecaCapturada;

				globalPecaCapturada = ' ';
			}
		}

	}

}

void validarMovimentoPecaBranca(char** tabuleiroBackEnd) {

	//VERIFICO SE O lOCAL ATUAL PARA SOLTAR PECA TEM QUE ESTAR VAZIO
	if (globalPecaBackupDoPonteiro == ' ')
	{
		//VERIFICO SE AS JOGADAS ESTAO SENDO NAS DIAGONAIS
		if ((globalLinhaPecaCapturada - 1) == globalLinhaPonteiro && (globalColunaPecaCapturada + 1) == globalColunaPonteiro ||
			(globalLinhaPecaCapturada - 1) == globalLinhaPonteiro && (globalColunaPecaCapturada - 1) == globalColunaPonteiro) {

			//RETIRO A PECA DO LOCAL ANTERIOR 
			tabuleiroBackEnd[globalLinhaPecaCapturada][globalColunaPecaCapturada] = ' ';

			//SOLTO A PECA NO NOVO LOCAL
			tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaCapturada;

			//VOLTO O BACKUP DE PECA ONDE O PONTEIRO ESTA LOCALIZADO
			globalPecaBackupDoPonteiro = globalPecaCapturada;

			globalPecaCapturada = ' ';
		}
	}

	//VERIFICO SE AS JOGADAS ESTAO SENDO PARA CAPTURAR PECA INIMIGA A DIREITA, AVANCANDO O TABULEIRO
	if ((globalLinhaPecaCapturada - 2) == globalLinhaPonteiro && (globalColunaPecaCapturada + 2) == globalColunaPonteiro) {

		if (tabuleiroBackEnd[globalLinhaPecaCapturada - 1][globalColunaPecaCapturada + 1] == 'P') {

			//ELIMINO PECA INIMIGA (PRETA), 'TO DO' FAZER UM PLACAR
			tabuleiroBackEnd[globalLinhaPecaCapturada - 1][globalColunaPecaCapturada + 1] = ' ';
			globalPlacarBrancas++;

			//RETIRO A PECA DO LOCAL ANTERIOR 
			tabuleiroBackEnd[globalLinhaPecaCapturada][globalColunaPecaCapturada] = ' ';

			//SOLTO A PECA NO NOVO LOCAL
			tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaCapturada;

			//VOLTO O BACKUP DE PECA ONDE O PONTEIRO ESTA LOCALIZADO
			globalPecaBackupDoPonteiro = globalPecaCapturada;

			globalPecaCapturada = ' ';
		}
	}


	//VERIFICO SE AS JOGADAS ESTAO SENDO PARA CAPTURAR PECA INIMIGA A ESQUERDA, AVANCANDO O TABULEIRO
	if ((globalLinhaPecaCapturada - 2) == globalLinhaPonteiro && (globalColunaPecaCapturada - 2) == globalColunaPonteiro) {

		if (tabuleiroBackEnd[globalLinhaPecaCapturada - 1][globalColunaPecaCapturada - 1] == 'P') {

			//ELIMINO PECA INIMIGA (PRETA), 'TO DO' FAZER UM PLACAR
			tabuleiroBackEnd[globalLinhaPecaCapturada - 1][globalColunaPecaCapturada - 1] = ' ';
			globalPlacarBrancas++;

			//RETIRO A PECA DO LOCAL ANTERIOR 
			tabuleiroBackEnd[globalLinhaPecaCapturada][globalColunaPecaCapturada] = ' ';

			//SOLTO A PECA NO NOVO LOCAL
			tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaCapturada;

			//VOLTO O BACKUP DE PECA ONDE O PONTEIRO ESTA LOCALIZADO
			globalPecaBackupDoPonteiro = globalPecaCapturada;

			globalPecaCapturada = ' ';
		}
	}


	//VERIFICO SE AS JOGADAS ESTAO SENDO PARA CAPTURAR PECA INIMIGA A ESQUERDA, RETROCEDENDO O TABULEIRO
	if ((globalLinhaPecaCapturada + 2) == globalLinhaPonteiro && (globalColunaPecaCapturada - 2) == globalColunaPonteiro) {

		if (tabuleiroBackEnd[globalLinhaPecaCapturada + 1][globalColunaPecaCapturada - 1] == 'P') {

			//ELIMINO PECA INIMIGA (PRETA), 'TO DO' FAZER UM PLACAR
			tabuleiroBackEnd[globalLinhaPecaCapturada + 1][globalColunaPecaCapturada - 1] = ' ';
			globalPlacarBrancas++;

			//RETIRO A PECA DO LOCAL ANTERIOR 
			tabuleiroBackEnd[globalLinhaPecaCapturada][globalColunaPecaCapturada] = ' ';

			//SOLTO A PECA NO NOVO LOCAL
			tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaCapturada;

			//VOLTO O BACKUP DE PECA ONDE O PONTEIRO ESTA LOCALIZADO
			globalPecaBackupDoPonteiro = globalPecaCapturada;

			globalPecaCapturada = ' ';
		}
	}

	//VERIFICO SE AS JOGADAS ESTAO SENDO PARA CAPTURAR PECA INIMIGA A DIREITA, AVANÇANDO O TABULEIRO
	if ((globalLinhaPecaCapturada + 2) == globalLinhaPonteiro && (globalColunaPecaCapturada + 2) == globalColunaPonteiro) {

		if (tabuleiroBackEnd[globalLinhaPecaCapturada + 1][globalColunaPecaCapturada + 1] == 'P') {

			//ELIMINO PECA INIMIGA (PRETA), 'TO DO' FAZER UM PLACAR
			tabuleiroBackEnd[globalLinhaPecaCapturada + 1][globalColunaPecaCapturada + 1] = ' ';
			globalPlacarBrancas++;

			//RETIRO A PECA DO LOCAL ANTERIOR 
			tabuleiroBackEnd[globalLinhaPecaCapturada][globalColunaPecaCapturada] = ' ';

			//SOLTO A PECA NO NOVO LOCAL
			tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaCapturada;

			//VOLTO O BACKUP DE PECA ONDE O PONTEIRO ESTA LOCALIZADO
			globalPecaBackupDoPonteiro = globalPecaCapturada;

			globalPecaCapturada = ' ';
		}

	}

}

void soltaPecaJogador(char** tabuleiroBackEnd) {

	if (globalPecaCapturada == 'P')
		validarMovimentoPecaPreta(tabuleiroBackEnd);

	if (globalPecaCapturada == 'B')
		validarMovimentoPecaBranca(tabuleiroBackEnd);

	/*TO DO, PECAS RAINHAS*/
}

void moveParaDireita(char** tabuleiroBackEnd) {

	if (globalColunaPonteiro >= 0 && globalColunaPonteiro < 7)
	{
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
		globalColunaPonteiro++;
		globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = '*';
	}
}

void moveParaEsquerda(char** tabuleiroBackEnd) {
	if (globalColunaPonteiro > 0 && globalColunaPonteiro <= 7)
	{
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
		globalColunaPonteiro--;
		globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = '*';
	}
}

void moveParaCima(char** tabuleiroBackEnd) {
	if (globalLinhaPonteiro > 0 && globalLinhaPonteiro <= 7)
	{
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
		globalLinhaPonteiro--;
		globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = '*';
	}
}

void moveParaBaixo(char** tabuleiroBackEnd) {
	if (globalLinhaPonteiro >= 0 && globalLinhaPonteiro < 7)
	{
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
		globalLinhaPonteiro++;
		globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = '*';
	}
}

void cancelaJogada(char** tabuleiroBackEnd) {

	if (globalPecaCapturada != ' '){
		tabuleiroBackEnd[globalLinhaPecaCapturada][globalColunaPecaCapturada] = globalPecaCapturada;
		globalPecaCapturada = ' ';
	}
}

void movimentacaoNoTabuleiroBackEnd(char** tabuleiroBackEnd, int movimento) {


	if (movimento == TABULEIRO_PONTEIRO_INICIAL)
	{
		globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = '*';
	}

	if (movimento == TECLA_GAMEPLAY_ACAO_CAPTURAR)
		PegaPeca(tabuleiroBackEnd);
	
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

int CapturaTeclado() {
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
}

int main() {
	char** tabuleiroBackEnd; 
	int teclaDirecional = 0;

	registraTeclasDoJogo();

	while (teclaDirecional != TECLA_MENU_OPCAO_SAIR) {
		//system("color A");
		intro();
		teclaDirecional = CapturaTeclado();

		switch (teclaDirecional) {

			case TECLA_MENU_OPCAO_JOGAR:

				tabuleiroBackEnd = organizaTabuleiroBackEndIncial();
				movimentacaoNoTabuleiroBackEnd(tabuleiroBackEnd, TABULEIRO_PONTEIRO_INICIAL);

				while (teclaDirecional != TECLA_GAMEPLAY_ACAO_SAIR_DO_JOGO) {
					tabuleiroUserIterface(tabuleiroBackEnd);
					teclaDirecional = CapturaTeclado();
					movimentacaoNoTabuleiroBackEnd(tabuleiroBackEnd, teclaDirecional);
				}

			break;

			case TECLA_MENU_OPCAO_TUTORIAL:
				ImprimeTutorial();
			break;

			default:
				break;
		}

		system("pause");
	}
}

