/*
ALUNOS: 	LUCAS MARQUES DE PAULA 	GRR20157104
			WESLEY MAFFAZZOLLI		GRR20155124
*/

#include "lista.h"
#include "matriz.h"
#include <stdio.h>
#include <locale.h>

int confirmarAcao(char *acao)
{
	char opcao = ' ';

	printf("%s", acao);
	scanf("\n%c", &opcao);

	if (opcao == 'S' || opcao == 's')
	{
		return 1;
	}
	else if (opcao == 'n' || opcao == 'N')
	{
		return 0;
	}

	return confirmarAcao(acao);
}

int criaMatriz(Matriz* mtx)
{
	int lin, col;
	
	printf("Digite as dimensões da matriz: linha e colunas separadas por um espaço\n");
	scanf("%d %d", &lin, &col);
	
	if (lin <= 0 || col <= 0)
	{
		printf("Dimensões inválidas: (%d X %d)\n", lin, col);
		return 0;
	}

	*mtx = NovaMatriz(lin, col);
	return 1;
}

void insereNovosDados(Matriz* mtx)
{
	Elemento* el;
	int lin, col;
	float dado;

	if (*mtx == NULL)
	{
		if(!(criaMatriz(mtx) > 0))
		return;
	}

	do
	{
		printf("Digite a linha, coluna e valor separados por um espaço\n");
		scanf("%d %d %f", &lin, &col, &dado);

		if (lin > (*mtx)->lin || col > (*mtx)->col || lin <= 0 || col <= 0)
		{
			printf(
				"ERRO: Posição incorreta !!!							\n"
				"As Dimensões da Matriz são: (%d X %d)					\n"
				"Você tentou inserir um elemento na posição: (%d X %d)	\n"
				, (*mtx)->lin, (*mtx)->col, lin, col
				);
			continue;
		}
		InsereElemento(*mtx, NovoElemento(lin, col, dado));
	} while (confirmarAcao("Deseja inserir novo dado ? (s/n)\n") > 0);
}

int validaMatriz(Matriz mtx)
{
	if (mtx == NULL)
	{
		printf("As matriz não foi preenchida\n");
		return 0;
	}
	return 1;
}

int validaMatrizes(Matriz mtA, Matriz mtB)
{
	if (mtA == NULL || mtB == NULL)
	{
		printf("As duas Matrizes matrizes não foram preenchidas\n");
		return 0;
	}
	return 1;
}

int main (int argc, char * argv[])
{
	Matriz mtA;
	Matriz mtB;
	Matriz mtC;
	mtA = mtB = mtC = NULL;


	char opcaoMenu = ' ';
	setlocale(LC_ALL, "Portuguese");

	while (1)
	{
		printf(
			"Insira a opção desejada:						\n"
			"0 - Sair										\n"
			"1 - Inserir dados na Matriz A					\n"
			"2 - Inserir dados na Matriz B					\n"
			"3 - Somar										\n"
			"4 - Subtrair									\n"
			"5 - Multiplicar								\n"
			"6 - Transpor a Matriz A						\n"
			"7 - Transpor a Matriz B						\n"
			"8 - Apagar a Matriz A							\n"
			"9 - Apagar a Matriz B							\n"
			"a - Mostrar a Matriz A							\n"
			"b - Mostrar a Matriz B							\n"
			"c - Mostrar a diagonal principal da Matriz A	\n"
			"d - Mostrar a diagonal principal da Matriz B	\n"
			);
		scanf("\n%c", &opcaoMenu);

		switch (opcaoMenu)
		{
		case '0':
			if (confirmarAcao("Realmente deseja sair do programa (s/n) ?\n") > 0)
			{
				exit(EXIT_SUCCESS);
			}
			break;
		case '1':
			insereNovosDados(&mtA);
			break;
		case '2':
			insereNovosDados(&mtB);
			break;
		case '3':
			if (validaMatrizes(mtA, mtB) > 0)
			{
				if (mtA->lin != mtB->lin || mtA->col != mtB->col)
				{
					printf("As matrizes devem ter as mesmas dimensões para essa operação!!\n");
					break;
				}
				mtC = MatrizSoma(mtA, mtB);
			}
			break;
		case '4':
			if (validaMatrizes(mtA, mtB) > 0)
			{
				if (mtA->lin != mtB->lin || mtA->col != mtB->col)
				{
					printf("As matrizes devem ter as mesmas dimensões para essa operação!!\n");
					break;
				}
				mtC = MatrizSubtracao(mtA, mtB);
			}
			break;
		case '5':
			if (validaMatrizes(mtA, mtB) > 0)
			{
				if (mtA->col != mtB->lin)
				{
					printf("As matriz A deve ter o mesmo numero de linhas da matriz B para fazer essa operação!!\n");
					break;
				}
				mtC = MatrizMultiplicacao(mtA, mtB);
			}
			break;
		case '6':
			if (validaMatriz(mtA) > 0)
			{
				mtC = MatrizTransposta(mtA);
				ApagaMatriz(&mtA, 1);
				mtA = mtC;
				mtC = NULL;
			}
			break;
		case '7':
			if (validaMatriz(mtB) > 0)
			{
				mtC = MatrizTransposta(mtB);
				ApagaMatriz(&mtB, 1);
				mtB = mtC;
				mtC = NULL;
			}
			break;
		case '8':
			if (validaMatriz(mtA) > 0)
			{
				ApagaMatriz(&mtA, 1);
			}
			break;
		case '9':
			if (validaMatriz(mtB) > 0)
			{
				ApagaMatriz(&mtB, 1);
			}
			break;
		case 'a':
			if (validaMatriz(mtA) > 0)
			{
				ImprimeMatriz(mtA);
			}
			break;
		case 'b':
			if (validaMatriz(mtB) > 0)
			{
				ImprimeMatriz(mtB);
			}
			break;
		case 'c':
			if (validaMatriz(mtA) > 0)
			{
				if (mtA->col != mtA->lin)
				{
					printf("As matriz deve ter o mesmo numero de linhas e colunas para fazer essa operação!!\n");
					break;
				}
				ImprimeDiagonalPrincipal(mtA);
			}
			break;
		case 'd':
			if (validaMatriz(mtB) > 0)
			{
				if (mtB->col != mtB->lin)
				{
					printf("As matriz deve ter o mesmo numero de linhas e colunas para fazer essa operação!!\n");
					break;
				}
				ImprimeDiagonalPrincipal(mtB);
			}
			break;
		default:
			printf("Opção inválida\n");
		}

		if (mtC != NULL)
		{
			ImprimeMatriz(mtC);
			ApagaMatriz(&mtC, 1);
		}

		system("pause");
	}
	return 0;
}
