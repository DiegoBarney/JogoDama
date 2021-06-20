#include "PecaBase.h"

extern int	globalPlacarPretas,		
			globalPlacarBrancas;	
extern char	globalAvisos[1000];


static PecaBase* _instance;

PecaBase* PecaBase::getInstance(char** tabuleiroBackEnd)
{
	if (_instance == nullptr) {

		_instance = new PecaBase(tabuleiroBackEnd);
	}

	return _instance;
}

PecaBase::PecaBase(char** tabuleiroBackEnd) {

	globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
	tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = PONTEIRO_DIRECIONAL;
}

PecaBase::~PecaBase() {
	globalLinhaPecaSelecionada = 0;
	globalColunaPecaSelecionada = 0;									
	globalPecaSelecionada = VAZIO;
	globalLinhaPonteiro = 0;							
	globalColunaPonteiro = 0;							
	globalPecaBackupDoPonteiro = VAZIO;
	_instance = nullptr;
}

void PecaBase::moveParaDireita(char** tabuleiroBackEnd){

	if (globalColunaPonteiro >= 0 && globalColunaPonteiro < (LINHAS -1) )
	{
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
		globalColunaPonteiro++;
		globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = PONTEIRO_DIRECIONAL;
	}
}

void PecaBase::moveParaEsquerda(char** tabuleiroBackEnd) {

	if (globalColunaPonteiro > 0 && globalColunaPonteiro <= (LINHAS - 1) )
	{
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
		globalColunaPonteiro--;
		globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = PONTEIRO_DIRECIONAL;
	}
}

void PecaBase::moveParaCima(char** tabuleiroBackEnd) {

	if (globalLinhaPonteiro > 0 && globalLinhaPonteiro <= (LINHAS - 1) )
	{
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
		globalLinhaPonteiro--;
		globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = PONTEIRO_DIRECIONAL;
	}
}

void PecaBase::moveParaBaixo(char** tabuleiroBackEnd) {

	if (globalLinhaPonteiro >= 0 && globalLinhaPonteiro < (LINHAS - 1) )
	{
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaBackupDoPonteiro;
		globalLinhaPonteiro++;
		globalPecaBackupDoPonteiro = tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro];
		tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = PONTEIRO_DIRECIONAL;
	}
}

void PecaBase::pegaPeca(char** tabuleiroBackEnd) {

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

void PecaBase::soltaPeca(char** tabuleiroBackEnd) {

	if (globalPecaSelecionada == PECA_PRETA || globalPecaSelecionada == PECA_BRANCA)
	{
		validarMovimentoPecaSimples(tabuleiroBackEnd);
	}

	if (globalPecaSelecionada == PECA_BRANCA_DAMA || globalPecaSelecionada == PECA_PRETA_DAMA)
	{
		validarJogadaDama(tabuleiroBackEnd);
	}

	verificaSeVirouDama(tabuleiroBackEnd);
}

void PecaBase::cancelaJogada(char** tabuleiroBackEnd) {

	if (globalPecaSelecionada != VAZIO) {
		tabuleiroBackEnd[globalLinhaPecaSelecionada][globalColunaPecaSelecionada] = globalPecaSelecionada;

		if (globalPecaBackupDoPonteiro == PECA_SELECIONADA)
		{
			globalPecaBackupDoPonteiro = globalPecaSelecionada;
		}

		globalPecaSelecionada = VAZIO;
	}
}

void PecaBase::verificaSeVirouDama(char** tabuleiroBackEnd) {

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

void PecaBase::validarMovimentoPecaSimples(char** tabuleiroBackEnd) {

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

void PecaBase::validarJogadaPecaComumParaEliminarPecaInimiga(char** tabuleiroBackEnd)
{
	//VERIFICO SE AS JOGADAS ESTAO SENDO PARA CAPTURAR PECA INIMIGA A DIREITA, AVANÇANDO O TABULEIRO
	if ((globalLinhaPecaSelecionada + 2) == globalLinhaPonteiro && (globalColunaPecaSelecionada + 2) == globalColunaPonteiro) {

		if (((tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada + 1] == PECA_BRANCA ||
			tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada + 1] == PECA_BRANCA_DAMA) && globalPecaSelecionada == PECA_PRETA) ||
			((tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada + 1] == PECA_PRETA ||
				tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada + 1] == PECA_PRETA_DAMA) && globalPecaSelecionada == PECA_BRANCA)) {

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

		if (((tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada - 1] == PECA_BRANCA ||
			tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada - 1] == PECA_BRANCA_DAMA) && globalPecaSelecionada == PECA_PRETA) ||
			((tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada - 1] == PECA_PRETA ||
				tabuleiroBackEnd[globalLinhaPecaSelecionada + 1][globalColunaPecaSelecionada - 1] == PECA_PRETA_DAMA) && globalPecaSelecionada == PECA_BRANCA)) {

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


		if (((tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada - 1] == PECA_BRANCA ||
			tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada - 1] == PECA_BRANCA_DAMA) && globalPecaSelecionada == PECA_PRETA) ||
			((tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada - 1] == PECA_PRETA ||
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

		if (((tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada + 1] == PECA_BRANCA ||
			tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada + 1] == PECA_BRANCA_DAMA) && globalPecaSelecionada == PECA_PRETA) ||
			((tabuleiroBackEnd[globalLinhaPecaSelecionada - 1][globalColunaPecaSelecionada + 1] == PECA_PRETA ||
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

void PecaBase::soltaPecaAposValidacoes(char** tabuleiroBackEnd) {
	//RETIRO A PECA DO LOCAL ANTERIOR 
	tabuleiroBackEnd[globalLinhaPecaSelecionada][globalColunaPecaSelecionada] = VAZIO;

	//SOLTO A PECA NO NOVO LOCAL
	tabuleiroBackEnd[globalLinhaPonteiro][globalColunaPonteiro] = globalPecaSelecionada;

	//VOLTO O BACKUP DE PECA ONDE O PONTEIRO ESTA LOCALIZADO
	globalPecaBackupDoPonteiro = globalPecaSelecionada;

	globalPecaSelecionada = VAZIO;
}

void PecaBase::validarJogadaDama(char** tabuleiroBackEnd)
{
	int linhaPecaInimiga = 0,
		colunaPecaInimiga = 0;
	bool sairLoopEncadeado = false;

	//VALIDACAO DIAGONAL DIREITA A BAIXO
	for (int linha = globalLinhaPonteiro, coluna = globalColunaPonteiro, sairLoopEncadeado = false; linha < LINHAS && coluna < COLUNAS && sairLoopEncadeado == false; linha++, coluna++) {

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

