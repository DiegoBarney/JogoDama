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

void TabuleiroDamaUserIterface(char** matrizJogoPreenchida) {
	int descontoLinhasInterfaceMatriz = 0;
	system("cls");

	for (int linhasInterface = 1; linhasInterface <= tamLinhasInterface; linhasInterface++) {

		printf("\n");

		if (linhasInterface % 2 == 0)
		{
			printf("______________________________________________________________________________\n");
		}
		else {
			descontoLinhasInterfaceMatriz++;
			for (int colunasInterface = 0; colunasInterface < tamColunasInterface; colunasInterface++)
			{

				if (linhasInterface == 1) {

					if (colunasInterface % 2 == 0)
						printf("  %c   ", matrizJogoPreenchida[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
					else
						printf("      ");

				}
				else if (linhasInterface == 3) {

					if (colunasInterface % 2 != 0)
						printf("  %c   ", matrizJogoPreenchida[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
					else
						printf("      ");

				}
				else if (linhasInterface == 5) {

					if (colunasInterface % 2 == 0)
						printf("  %c   ", matrizJogoPreenchida[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
					else
						printf("      ");

				}
				else if (linhasInterface == 11) {

					if (colunasInterface % 2 != 0)
						printf("  %c   ", matrizJogoPreenchida[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
					else
						printf("      ");

				}
				else if (linhasInterface == 13) {

					if (colunasInterface % 2 == 0)
						printf("  %c   ", matrizJogoPreenchida[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
					else
						printf("      ");

				}
				else if (linhasInterface == 15) {

					if (colunasInterface % 2 != 0)
						printf("  %c   ", matrizJogoPreenchida[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
					else
						printf("      ");

				}
				else {

					printf("    %c ", matrizJogoPreenchida[linhasInterface - descontoLinhasInterfaceMatriz][colunasInterface]);
				}

				/*
				//xadrez
				if (linhasInterface == 1 ) {
					printf("  PB  ");
				}
				else if (linhasInterface == 3) {
					printf("  PB  ");
				}else if (linhasInterface == 13) {
					printf("  PP  ");
				}
				else if (linhasInterface == 15) {
					printf("  PP  ");
				}
				else {
					printf("      ");
				}*/

				if (colunasInterface < 8) {
					printf("|");
				}

				printf("   ");
			}
		}
	}
	printf("\n\n\n");
}

void registraTeclasDirecionais()
{
	//DOC teclas virtuais https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	//DOC registro de teclas https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-registerhotkey
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x26);//DIRECIONAL PARA CIMA
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x28);//DIRECIONAL PARA BAIXO
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x27);//DIRECIONAL PARA DIREITA
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x25);//DIRECIONAL PARA ESQUERDA
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x70);//F1 = CAPTURA A PECA
	RegisterHotKey(NULL, 1, MOD_NOREPEAT, 0x71);//F2 = SOLTA A PECA

}

char** iniciaJogada() {
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

	registraTeclasDirecionais();

	return matriz;
}

int CapturaTecladoDirecional() {
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

		}
	}
}

int main() {
	//char** matriz; 

	//matriz = iniciaJogada();

	//XadrezUserIterface(matriz);
	registraTeclasDirecionais();
	int teclaDirecional;

	while (true) {
		printf("Digite uma tecla direcional, ex: ALT+8, ALT+4, ALT+6, ALT+2 \n");
		teclaDirecional = CapturaTecladoDirecional();
		printf("Tecla Capturada = %d\n", teclaDirecional);
	}

	system("pause");
}

