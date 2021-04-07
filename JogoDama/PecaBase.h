#pragma once
#include "CoreDama.h"
#include "Tabuleiro.h"

class PecaBase {     

public:     

	int		globalLinhaPecaSelecionada = 0,		
			globalColunaPecaSelecionada = 0;											
	char	globalPecaSelecionada = VAZIO;	

	int		globalLinhaPonteiro = 0,								
			globalColunaPonteiro = 0;								
	char	globalPecaBackupDoPonteiro = VAZIO;						

	static PecaBase* getInstance(char** tabuleiroBackEnd);
	~PecaBase();
	void moveParaDireita(char** tabuleiroBackEnd);
	void moveParaEsquerda(char** tabuleiroBackEnd);
	void moveParaCima(char** tabuleiroBackEnd);
	void moveParaBaixo(char** tabuleiroBackEnd);
	void pegaPeca(char** tabuleiroBackEnd);
	void soltaPeca(char** tabuleiroBackEnd);
	void cancelaJogada(char** tabuleiroBackEnd);

private:
	PecaBase(char** tabuleiroBackEnd);
	void verificaSeVirouDama(char** tabuleiroBackEnd);
	void validarMovimentoPecaSimples(char** tabuleiroBackEnd);
	void validarJogadaPecaComumParaEliminarPecaInimiga(char** tabuleiroBackEnd);
	void soltaPecaAposValidacoes(char** tabuleiroBackEnd);
	void validarJogadaDama(char** tabuleiroBackEnd);
};