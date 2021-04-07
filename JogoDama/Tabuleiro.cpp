#include "Tabuleiro.h"

char** Tabuleiro::organizaTabuleiroBackEndIncial() {
	char** matriz = NULL;

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

void Tabuleiro::tabuleiroUserIterface(char** tabuleiroBackEnd) {
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
	printf("\x1b[32mPlacar \x1b[34m%s: %d", globalPlayer2.nome, globalPlacarPretas);
	printf("\n\x1b[32mPlacar \x1b[37m%s: %d\n", globalPlayer1.nome, globalPlacarBrancas);
	printf("\x1b[32mAVISOS:\x1b[31m %s", globalAvisos);

}

void Tabuleiro::movimentacaoNoTabuleiroBackEnd(char** tabuleiroBackEnd, int eventoDeTecla) {

	PecaBase* pecaBase = PecaBase::getInstance(tabuleiroBackEnd);

	if (eventoDeTecla == TECLA_GAMEPLAY_ACAO_CAPTURAR)
		pecaBase->pegaPeca(tabuleiroBackEnd);

	if (eventoDeTecla == TECLA_GAMEPLAY_ACAO_SOLTAR)
		pecaBase->soltaPeca(tabuleiroBackEnd);

	if (eventoDeTecla == TECLA_GAMEPLAY_ACAO_CANCELAR_JOGADA)
		pecaBase->cancelaJogada(tabuleiroBackEnd);

	if (eventoDeTecla == TECLA_GAMEPLAY_DIRECIONAL_RIGHT)
		pecaBase->moveParaDireita(tabuleiroBackEnd);

	if (eventoDeTecla == TECLA_GAMEPLAY_DIRECIONAL_LEFT)
		pecaBase->moveParaEsquerda(tabuleiroBackEnd);

	if (eventoDeTecla == TECLA_GAMEPLAY_DIRECIONAL_UP)
		pecaBase->moveParaCima(tabuleiroBackEnd);

	if (eventoDeTecla == TECLA_GAMEPLAY_DIRECIONAL_DOWN)
		pecaBase->moveParaBaixo(tabuleiroBackEnd);

	if (eventoDeTecla == TECLA_GAMEPLAY_ACAO_SAIR_DO_JOGO)
		pecaBase->~PecaBase();

		
}