#include "CoreDama.h"
#include "JogoDama.h"
#include "Tabuleiro.h"
#include "PecaBase.h"
#include "TecladoJogo.h"

extern int				globalPlacarPretas = 0,		
						globalPlacarBrancas = 0;	

extern char				globalAvisos[1000] = {' '};					
				
extern char				globalPecaDeveJogarAgora = PECA_BRANCA;		
extern dados_jogador	globalPlayer1 = { " ", PECA_BRANCA, false },						
						globalPlayer2 = { " ", PECA_BRANCA, false };						


void JogoDama::intro() {
	system("cls");
	printf("\x1b[37m ############ Bem vindo ao jogo \x1b[31m DamaBreuva\x1b[37m !!! ############\n\n");
	printf("Pressione a tecla numero 1 para Comecar a jogar\n");
	printf("Pressione a tecla numero 2 para acessar o tutorial do jogo\n");
	printf("Pressione a tecla numero 3 para Sair\n");
}

void JogoDama::imprimeTutorial()
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

void JogoDama::capturaDadosJogador() {
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

bool JogoDama::ehGanhador() {
	
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

int main() {
	char** tabuleiroBackEnd; 
	int teclaDirecional = 0;
	JogoDama jogo;
	Tabuleiro tabuleiro;
	TecladoJogo* TecladoJogo = TecladoJogo::getInstance();

	while (teclaDirecional != TECLA_MENU_OPCAO_SAIR) {

		jogo.intro();

		teclaDirecional = TecladoJogo->capturaTeclado();

		switch (teclaDirecional) {

			case TECLA_MENU_OPCAO_JOGAR:

				jogo.capturaDadosJogador();
				tabuleiroBackEnd = tabuleiro.organizaTabuleiroBackEndIncial();
				tabuleiro.movimentacaoNoTabuleiroBackEnd(tabuleiroBackEnd, TABULEIRO_PONTEIRO_INICIAL);

				while (teclaDirecional != TECLA_GAMEPLAY_ACAO_SAIR_DO_JOGO && jogo.ehGanhador() == false) {
					tabuleiro.tabuleiroUserIterface(tabuleiroBackEnd);
					teclaDirecional = TecladoJogo->capturaTeclado();
					tabuleiro.movimentacaoNoTabuleiroBackEnd(tabuleiroBackEnd, teclaDirecional);
				}

			break;

			case TECLA_MENU_OPCAO_TUTORIAL:
				jogo.imprimeTutorial();
			break;

			default:
				break;
		}

		system("pause");
	}
}

