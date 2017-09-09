#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "curses.h"
#include "pilha.h"
#include "mapa.h"
#include "rato.h"

int main(int argc, char * argv[])
{
	Mapa mapa;
	Rato rato;
	srand(time(NULL));
	initscr();
	inicializaAmbiente(&mapa);
	inicializaRato(&rato);

	do {

		mapa.labirinto[rato.posicaoAtual.row][rato.posicaoAtual.column] = RATO;
		mostraMapa(mapa);

		if (podeProgredir(rato))
		{
			mapa.labirinto[rato.posicaoAtual.row][rato.posicaoAtual.column] = RASTRO;
			progredir(&rato);
		} 
		
		else if(podeRegredir(rato))
		{
			mapa.labirinto[rato.posicaoAtual.row][rato.posicaoAtual.column] = BECO;
			regredir(&rato);
		}
		
		analisaPossiveisRotas(rato, mapa);

	} while (podeSeLocomover(rato) && permaneceNoLabirinto(rato, mapa));

	mapa.labirinto[rato.posicaoAtual.row][rato.posicaoAtual.column] = RATO;
	mostraMapa(mapa);
	getch();
	finalizaRato(&rato);
	endwin();
	return 0;
}
