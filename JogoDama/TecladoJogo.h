#pragma once
#include "CoreDama.h"

class TecladoJogo {

public:
	static TecladoJogo* getInstance();
	~TecladoJogo();
	int capturaTeclado();

private:
	TecladoJogo();
	void registraTeclasDoJogo();
};
