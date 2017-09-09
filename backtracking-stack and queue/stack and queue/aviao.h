#define DESLOCAMENTO_Y 20
#define ALTURA_PISTA 10
#define LARGURA_PISTA 80
#define TEMPO 4.


void delay(int milliseconds)
{
	long ciclos = milliseconds / 1000. * CLOCKS_PER_SEC;
	clock_t inicio = clock();
	while ((clock() - inicio) < ciclos);
}

void pousa() {
	int p = 0;
	int ya = 0, xa = 0;
	clock_t inicio = clock();

	p = 0;
	while (((clock() - inicio) / CLOCKS_PER_SEC) <= TEMPO)
	{
		p = p > 0 ? 0 : 1;
		xa = LARGURA_PISTA - LARGURA_PISTA * (clock() - inicio) / CLOCKS_PER_SEC / TEMPO + 1;
		ya = DESLOCAMENTO_Y + (ALTURA_PISTA * (ya >= ALTURA_PISTA + DESLOCAMENTO_Y ? 1. : 2. * (clock() - inicio) / CLOCKS_PER_SEC / TEMPO));

		clear();
		mvprintw(ya + 0, xa, "  __________ /F ");
		mvprintw(ya + 1, xa, "c'____---__=_/  ");
		mvprintw(ya + 2, xa, "   o     o      ");
		mvprintw(DESLOCAMENTO_Y + ALTURA_PISTA + 3, p, "-- -- -- -- -- -- -- -- -- --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --");
		refresh();
	}
}

void decola() {
	int p = 0;
	int ya = 0, xa = 0;
	clock_t inicio = clock();

	p = 0;
	while (((clock() - inicio) / CLOCKS_PER_SEC) <= TEMPO)
	{
		p = p > 0 ? 0 : 1;
		xa = LARGURA_PISTA - LARGURA_PISTA * (clock() - inicio) / CLOCKS_PER_SEC / TEMPO + 1;
		ya = DESLOCAMENTO_Y + ((xa < LARGURA_PISTA  / 2.) ? 2. * (ALTURA_PISTA - ALTURA_PISTA * (clock() - inicio) / CLOCKS_PER_SEC / TEMPO) : ALTURA_PISTA);

		clear();
		mvprintw(ya + 0, xa, "  __________ /F ");
		mvprintw(ya + 1, xa, "c'____---__=_/  ");
		mvprintw(ya + 2, xa, "   o     o      ");
		mvprintw(DESLOCAMENTO_Y + ALTURA_PISTA + 3, p, "-- -- -- -- -- -- -- -- -- --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --");
		refresh();
	}
}
