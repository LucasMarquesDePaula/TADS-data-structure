#define DELAY 100

#define NUMERO_COLUNAS_LABIRINTO 30
#define NUMERO_LINHAS_LABIRINTO 30
#define NIVEL_DIFICULDADE_LABIRINTO 30

#define LIVRE ' '
#define PAREDE ((char) 219)
#define RASTRO '.'
#define BECO ((char) 176)
#define RATO ((char) 1)

typedef char Labirinto[NUMERO_LINHAS_LABIRINTO][NUMERO_COLUNAS_LABIRINTO];

typedef struct {
	int numeroDeColunas, numeroDeLinhas;
	int nivelDificuldadeLabirinto;
	Labirinto labirinto;
} Mapa;

Mapa* cercaMapa(Mapa* mapa)
{
	int i;
	for (i = 0; i < mapa->numeroDeColunas; i++)
	{
		mapa->labirinto[0][i] = mapa->labirinto[mapa->numeroDeLinhas - 1][i] = PAREDE;
	}
	for (i = 0; i < mapa->numeroDeLinhas; i++)
	{
		mapa->labirinto[i][0] = mapa->labirinto[i][mapa->numeroDeColunas - 1] = PAREDE;
	}
	return mapa;
}

Mapa* criaEspacoLivre(Mapa* mapa)
{
	int i, j;
	for (i = 0; i < mapa->numeroDeLinhas; i++)
	{
		for (j = 0; j < mapa->numeroDeColunas; j++)
		{
			mapa->labirinto[i][j] = LIVRE;
		}
	}
	return mapa;
}

Mapa* criaLabirinto(Mapa* mapa)
{
	int maxNumeroDeParedes = mapa->numeroDeColunas * mapa->numeroDeLinhas * mapa->nivelDificuldadeLabirinto / 100.;
	int i;
	for (i = 0; i < maxNumeroDeParedes; i++)
	{
		mapa->labirinto[rand() % mapa->numeroDeLinhas][rand() % mapa->numeroDeColunas] = PAREDE;
	}
	return mapa;
}

Mapa* criaPorta(Mapa* mapa)
{
	switch (rand() % 4)
	{
	case 0:
		mapa->labirinto[rand() % (mapa->numeroDeLinhas - 2) + 1][mapa->numeroDeColunas - 1] = LIVRE;
		break;
	case 1:
		mapa->labirinto[rand() % (mapa->numeroDeLinhas - 2) + 1][0] = LIVRE;
		break;
	case 2:
		mapa->labirinto[mapa->numeroDeLinhas - 1][rand() % (mapa->numeroDeColunas - 2) + 1] = LIVRE;
		break;
	default:
		mapa->labirinto[0][rand() % (mapa->numeroDeColunas - 2) + 1] = LIVRE;
		break;
	}

	return mapa;
}

void delay(int milliseconds)
{
	long ciclos = milliseconds / 1000. * CLOCKS_PER_SEC;
	clock_t inicio = clock();
	while ((clock() - inicio) < ciclos);
}

void mostraMapa(Mapa mapa)
{
	int i, j;
	char saida[(NUMERO_LINHAS_LABIRINTO + 2) * NUMERO_COLUNAS_LABIRINTO];
	char aux[4];
	strcpy(saida, "");
	strcpy(aux, " ");
	for (i = 0; i < mapa.numeroDeLinhas; i++)
	{
		for (j = 0; j < mapa.numeroDeColunas; j++)
		{
			aux[0] = (mapa.labirinto)[i][j];
			strcat(saida, aux);
		}
		strcat(saida, "\n");
	}
	refresh();
	printf("%s\n", saida);
	delay(DELAY);
}

void inicializaAmbiente(Mapa* mapa)
{
	mapa->numeroDeColunas = NUMERO_COLUNAS_LABIRINTO;
	mapa->numeroDeLinhas = NUMERO_LINHAS_LABIRINTO;
	mapa->nivelDificuldadeLabirinto = NIVEL_DIFICULDADE_LABIRINTO;
	criaEspacoLivre(mapa);
	cercaMapa(mapa);
	criaLabirinto(mapa);
	criaPorta(mapa);
}

