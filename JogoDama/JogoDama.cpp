#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define linhas 8
#define colunas 8

#define tamLinhasInterface 15
#define tamColunasInterface 8

struct dados_jogador
{
	char nome[50];
	char pecaJogador;
	bool vencedor = false;
};

int globalLinhaPonteiro = 0, globalColunaPonteiro = 0;
char globalPecaBackupDoPonteiro;

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
	
	//TECLAS DE MENU
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x61);//FUNCAO NUMERO 1
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x62);//FUNCAO NUMERO 2
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x63);//FUNCAO NUMERO 3
}

void intro() {

	printf("############ Bem vindo ao jogo DamaBreuva!!! ############\n\n");
	printf("Pressione a tecla numero 1 para Comecar a jogar\n");
	printf("Pressione a tecla numero 2 para acessar o tutorial do jogo\n");
	printf("Pressione a tecla numero 3 para Sair\n");
}

void ImprimeTutorial()
{
	printf("##### Tutorial DamaBreuva ######");

	printf("\n\nControles do Jogo:\n");
	printf("Direcional para cima.\n");
	printf("Direcional para baixo.\n");
	printf("Direcional para esquerda.\n");
	printf("Direcional para direita.\n");
	printf("F1 Seleciona Peca.\n");
	printf("F2 Solta Peca.\n");

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
	printf("T = Ponteiro onde o jogador esta localizado na movimentacão.\n\n");
}

void tabuleiroDamaUserIterface(char** matrizJogoPreenchida) {
	int descontoLinhasInterfaceMatriz = 0;
	system("cls");

	for (int linhasInterface = 1; linhasInterface <= tamLinhasInterface; linhasInterface++) {
		printf("\n");

		if (linhasInterface % 2 == 0)
		{
			printf("________________________________________________________________________________\n");
		}
		else {

			descontoLinhasInterfaceMatriz++;

			for (int colunasInterface = 0; colunasInterface < tamColunasInterface; colunasInterface++)
			{
				if (linhasInterface == 1) {
						printf("    %c    ", matrizJogoPreenchida[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}
				else if (linhasInterface == 3) {
						printf("    %c    ", matrizJogoPreenchida[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}
				else if (linhasInterface == 5) {
						printf("    %c    ", matrizJogoPreenchida[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}
				else if (linhasInterface == 11) {

						printf("    %c    ", matrizJogoPreenchida[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}
				else if (linhasInterface == 13) {

						printf("    %c    ", matrizJogoPreenchida[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}
				else if (linhasInterface == 15) {

						printf("    %c    ", matrizJogoPreenchida[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}
				else {
					printf("    %c    ", matrizJogoPreenchida[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}

				if (colunasInterface < 8) {
					printf("|");
				}
			}
		}
	}
	printf("\n\n\n");
}

char** organizaTabuleiroBackEndIncial() {
	char** matriz = NULL;

	matriz = (char**)malloc(linhas * sizeof(char*));

	for (int i = 0; i < linhas; ++i)
		matriz[i] = (char*)malloc(colunas * sizeof(char));


	for (int l = 0; l < linhas; l++)
	{
		for (int c = 0; c < colunas; c++)
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

void movimentacaoNoTabuleiroBackEnd(char** matriz, int movimento) {

	if (movimento == 0)
	{
		globalPecaBackupDoPonteiro = matriz[globalLinhaPonteiro][globalColunaPonteiro];
		matriz[globalLinhaPonteiro][globalColunaPonteiro] = 'T';
	}

	if (movimento == 6)
	{
		if (globalColunaPonteiro >= 0 && globalColunaPonteiro < 7)
		{
			matriz[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
			globalColunaPonteiro++;
			globalPecaBackupDoPonteiro = matriz[globalLinhaPonteiro][globalColunaPonteiro];
			matriz[globalLinhaPonteiro][globalColunaPonteiro] = 'T';
		}
	}


	if (movimento == 4)
	{
		if (globalColunaPonteiro > 0 && globalColunaPonteiro <= 7)
		{
			matriz[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
			globalColunaPonteiro--;
			globalPecaBackupDoPonteiro = matriz[globalLinhaPonteiro][globalColunaPonteiro];
			matriz[globalLinhaPonteiro][globalColunaPonteiro] = 'T';
		}
	}


	if (movimento == 8)
	{
		if (globalLinhaPonteiro > 0 && globalLinhaPonteiro <= 7)
		{
			matriz[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
			globalLinhaPonteiro--;
			globalPecaBackupDoPonteiro = matriz[globalLinhaPonteiro][globalColunaPonteiro];
			matriz[globalLinhaPonteiro][globalColunaPonteiro] = 'T';
		}
	}


	if (movimento == 2)
	{
		if (globalLinhaPonteiro >= 0 && globalLinhaPonteiro < 7)
		{
			matriz[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
			globalLinhaPonteiro++;
			globalPecaBackupDoPonteiro = matriz[globalLinhaPonteiro][globalColunaPonteiro];
			matriz[globalLinhaPonteiro][globalColunaPonteiro] = 'T';
		}
	}
}

int CapturaTeclado() {
	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, 0, 0) != 0)
	{
		if (msg.message == WM_HOTKEY)
		{
			//DIRECIONAIS
			if (msg.lParam == 2490368)
				return 8;
			if (msg.lParam == 2621440)
				return 2;
			if (msg.lParam == 2424832)
				return 4;
			if (msg.lParam == 2555904)
				return 6;

			//ACOES
			if (msg.lParam == 7340032)//CAPTURAR 
				return 5;
			if (msg.lParam == 7405568)//SOLTAR
				return 3;

			//TECLA MENU
			if (msg.lParam == 6356992)//OPCAO JOGAR 
				return 1;
			if (msg.lParam == 6422528)//OPCAO TUTORIAL
				return 2;
			if (msg.lParam == 6488064)//OPCAO SAIR
				return 3;
		}
	}
}

int main() {
	char** matriz; 
	int teclaDirecional = 0;
	bool sair = false;

	registraTeclasDoJogo();
	matriz = organizaTabuleiroBackEndIncial();

	while (sair == false) {
		intro();

		teclaDirecional = CapturaTeclado();

		switch (teclaDirecional) {

			case 1:
				system("cls");

				//inicio ponteiro em 0,0
				movimentacaoNoTabuleiroBackEnd(matriz, 0);

				while (true) {
					tabuleiroDamaUserIterface(matriz);
					teclaDirecional = CapturaTeclado();
					movimentacaoNoTabuleiroBackEnd(matriz, teclaDirecional);
				}
				system("pause");
			break;

			case 2:
				system("cls");
				ImprimeTutorial();
				system("pause");
				system("cls");
			break;

			case 3:
				sair = true;
			break;
		}
	}

	system("pause");
}

