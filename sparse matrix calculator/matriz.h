/*
ALUNOS: 	LUCAS MARQUES DE PAULA 	GRR20157104
			WESLEY MAFFAZZOLLI		GRR20155124
*/

typedef Nodo Elemento;
typedef Lista Matriz;
typedef float(*Operacao)(float, float);

float Soma(float a, float b) { return a + b; }
float Subtracao(float a, float b) { return a - b; }
float Multiplicacao(float a, float b) { return a * b; }

Elemento* NovoElemento(int lin, int col, float dado)
{
	return NovoNodo(lin, col, dado);
}

Matriz NovaMatriz(int numeroLinhas, int numeroColunas)
{
	return NovoElemento(numeroLinhas, numeroColunas, -1.);
}

void ApagaMatriz(Matriz *mtx, int apagaDescritor)
{
	ApagaLista(&((*mtx)->prox));
	(*mtx)->prox = NULL;
	if (apagaDescritor)
	{
		free(*mtx);
		*mtx = NULL;
	}
}

Elemento* BuscaPosicaoElemento(Matriz mtx, Elemento el)
{
	Elemento *aux = mtx;
	while (aux->prox != NULL && (aux->prox->lin < el.lin || (aux->prox->lin == el.lin && aux->prox->col < el.col)))
	{
		aux = aux->prox;
	}
	return aux;
}

void InsereElemento(Matriz mtx, Elemento* el)
{
	Elemento *pos;

	if (el == NULL || el->col > mtx->col || el->lin > mtx->lin)
	{
		free(el);
		return;
	}

	pos = BuscaPosicaoElemento(mtx, *el);

	if (pos->prox != NULL && (pos->prox->lin == el->lin && pos->prox->col == el->col))
	{
		free(RemoveNodo(pos));
	}

	if (el->dado != 0.)
	{
		InsereNodo(pos, el);
	}
	
}

char* MatrizParaString(Matriz mtx, char tipo)
{
	int m = mtx->lin, n = mtx->col;
	int i, j;
	char *saida = (char*)malloc(((12 * (n + 1) * m) + 1) * sizeof(char));
	char aux[14];

	mtx = mtx->prox;
	strcpy(saida, "");
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (mtx != NULL && mtx->col == j && mtx->lin == i)
			{
				sprintf(aux, "%9.2f\t", mtx->dado);
				mtx = mtx->prox;
			}
			else
			{
				sprintf(aux, "%9.2f\t", 0.);
			}

			if (tipo == '*' || (tipo == 'P' && i == j) || (tipo == 'S' && i == -j + n + 1))
			{
				strcat(saida, aux);
			}

		}
		strcat(saida, "\n");
	}
	strcat(saida, "\0");
	return saida;
}

void ImprimeDiagonalPrincipal(Matriz mtx) {
	//Uma função que imprime os elementos da diagonal principal, inclusive os zeros caso existam.
	char* saida = MatrizParaString(mtx, 'P');
	printf("%s\n\n", saida);
	free(saida);
}

void ImprimeDiagonalSecundaria(Matriz mtx) {
	char* saida = MatrizParaString(mtx, 'S');
	printf("%s\n\n", saida);
	free(saida);
}

void ImprimeMatriz(Matriz mtx) {
	//Uma função que imprime todos os dados da matriz, inclusive os zeros;
	char* saida = MatrizParaString(mtx, '*');
	printf("%s\n\n", saida);
	free(saida);
}

float SomatorioMatriz(Elemento* el)
{
	if (el != NULL)
	{
		return el->dado + SomatorioMatriz(el->prox);
	}
	return 0.;
}

Matriz SubMatriz(Matriz mtx, int linIni, int colIni, int linFim, int colFim)
{
	Matriz subMatriz = NovaMatriz(linFim - linIni + 1, colFim - colIni + 1);
	while ((mtx = mtx->prox) != NULL && (mtx->lin < linFim || (mtx->lin == linFim && mtx->col <= colFim)))
	{
		if (mtx->lin >= linIni && mtx->lin <= linFim && mtx->col >= colIni && mtx->col <= colFim)
		{
			InsereElemento(subMatriz, NovoElemento(mtx->lin - linIni + 1, mtx->col - colIni + 1, mtx->dado));
		}
	}
	return subMatriz;
}

Matriz MatrizTransposta(Matriz mtx)
{
	//Uma função que gera a matriz transposta;
	Matriz tpt = NovaMatriz(mtx->col, mtx->lin);
	while ((mtx = mtx->prox) != NULL)
	{
		InsereElemento(tpt, NovoElemento(mtx->col, mtx->lin, mtx->dado));
	}
	return tpt;
}

Matriz MatrizOperacao(Matriz mtA, Matriz mtB, Operacao operacao)
{
	Matriz mtO = NovaMatriz(mtA->lin, mtA->col);
	float a, b;
	Elemento *aux;
	mtA = mtA->prox;
	mtB = mtB->prox;
	while (mtA != NULL || mtB != NULL)
	{
		a = b = 0.;

		if (mtB != NULL && (mtA == NULL || mtB->lin < mtA->lin || (mtB->lin == mtA->lin && mtB->col < mtA->col)))
		{
			b = mtB->dado;
			aux = mtB;
			mtB = mtB->prox;
		}

		else if (mtA != NULL && (mtB == NULL || mtA->lin < mtB->lin || (mtA->lin == mtB->lin && mtA->col < mtB->col)))
		{
			a = mtA->dado;
			aux = mtA;
			mtA = mtA->prox;
		}

		else 
		{
			a = mtA->dado;
			b = mtB->dado;
			aux = mtA;
			mtA = mtA->prox;
			mtB = mtB->prox;
		}

		InsereElemento(mtO, NovoElemento(aux->lin, aux->col, operacao(a, b)));
	}
	return mtO;
}

Matriz MatrizSoma(Matriz mtA, Matriz mtB)
{
	//Uma função que soma duas matrizes;
	return MatrizOperacao(mtA, mtB, Soma);
}

Matriz MatrizSubtracao(Matriz mtA, Matriz mtB)
{
	//Uma função que subtrai duas matrizes;
	return MatrizOperacao(mtA, mtB, Subtracao);
}

Matriz MatrizMultiplicacao(Matriz mtA, Matriz mtB)
{
	//Uma função que multiplica duas matrizes;
	Matriz mul = NovaMatriz(mtA->lin, mtB->col);
	Matriz smA, smB, mtO;
	int u, v;
	mtB = MatrizTransposta(mtB);
	for (u = 1; u <= mtA->lin; u++)
	{
		for (v = 1; v <= mtB->lin; v++)
		{
			smA = SubMatriz(mtA, u, 1, u, mtA->col);
			smB = SubMatriz(mtB, v, 1, v, mtB->col);
			mtO = MatrizOperacao(smA, smB, Multiplicacao);
			InsereElemento(mul, NovoElemento(u, v, SomatorioMatriz(mtO->prox)));
			ApagaMatriz(&smA, 1);
			ApagaMatriz(&smB, 1);
			ApagaMatriz(&mtO, 1);
		}
	}
	ApagaMatriz(&mtB, 1);
	return mul;
}