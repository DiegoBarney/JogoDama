#pragma once
#include "CoreDama.h"
#include "PecaBase.h"

struct dados_jogador
{
	char nome[50];
	char pecaJogador;
	bool vencedor = false;
};

//Variavel global do placar do jogo	 ---//
extern int	globalPlacarPretas,		//
			globalPlacarBrancas;	//
//--------------------------------------//

//Variavel global adicionais do jogo -----------------------//
extern char		globalAvisos[1000];							//
															//		
extern char		globalPecaDeveJogarAgora;					//
															//
extern dados_jogador	globalPlayer1,						//
						globalPlayer2;						//
//----------------------------------------------------------//



class Tabuleiro {

public:
	char** organizaTabuleiroBackEndIncial();
	void tabuleiroUserIterface(char** tabuleiroBackEnd);
	void movimentacaoNoTabuleiroBackEnd(char** tabuleiroBackEnd, int eventoDeTecla);

};
