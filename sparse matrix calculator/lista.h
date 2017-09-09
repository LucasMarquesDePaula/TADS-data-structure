/*
ALUNOS: 	LUCAS MARQUES DE PAULA 	GRR20157104
			WESLEY MAFFAZZOLLI		GRR20155124
*/

#include <stdlib.h>

typedef struct Nodo {
	float dado;
	int lin, col;
	struct Nodo *prox;
} Nodo;

typedef Nodo* Lista;

Nodo *NovoNodo(int lin, int col, float dado)
{
	//Uma função que faz a alocação de memória para cada nodo criado na lista;
	Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
	if (novo == NULL)
	{
		exit(EXIT_FAILURE);
	}
	novo->col = col;
	novo->lin = lin;
	novo->dado = dado;
	novo->prox = NULL;
	return novo;
}

Lista NovaLista()
{
	return NovoNodo(-1, -1, -1.);
}

void InsereNodo(Nodo* ref, Nodo* novo)
{
	//Uma função que insere na lista um nodo alocado;
	novo->prox = ref->prox;
	ref->prox = novo;
}

Nodo* BuscaValor(Nodo* ref, float dado) 
{
	//Uma função que lê(busca) os dados de uma lista;
	if (ref == NULL || ref->dado == dado)
	{
		return ref;
	}
	return BuscaValor(ref->prox, dado);
}

Nodo* RemoveNodo(Nodo* ref)
{
	Nodo* nodo;
	nodo = ref->prox;
	if (nodo != NULL)
	{
		ref->prox = nodo->prox;
	}
	return nodo;
}

void ApagaLista(Nodo** ref)
{
	//Uma função que libera a memória alocada para a lista;
	if (*ref != NULL)
	{
		ApagaLista(&((*ref)->prox));
		free(*ref);
		*ref = NULL;
	}
}