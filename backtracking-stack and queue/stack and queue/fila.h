#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct ua  //Unidade Aérea
{
    int id, autorizacao;
    char nome[32], origem[16], destino[16];
    struct ua *ant;
} Aviao;

typedef struct upd  //Unidade de Pousos e Decolagens
{
    Aviao *primeiro;
    int quantidade;
} Pista;

Aviao* aloca_aviao(Aviao novoAviao)
{
    Aviao *p;
    p = (Aviao*) malloc(sizeof(Aviao));
    if(!p)
    {
        printw("Problema de alocação");
        exit(EXIT_FAILURE);
    }
    p->id = novoAviao.id;
    p->autorizacao = 0;
    strcpy(p->nome, novoAviao.nome);
    strcpy(p->origem, novoAviao.origem);
    strcpy(p->destino, novoAviao.destino);
    p->ant = NULL;
    return p;
}

Aviao detalha_aviao()
{
    Aviao aeronave;
	printw("Cadastro da Aeronave:\n\n");
    printw("1 - ID: ");
    scanw("%d", &aeronave.id);
	printw("2 - Nome: ");
    scanw("\n%s", aeronave.nome);
	printw("3 - Origem: ");
    scanw("\n%s", aeronave.origem);
	printw("4 - Destino: ");
    scanw("\n%s", aeronave.destino);
    aeronave.ant = NULL;
    aeronave.autorizacao = 0;
    return aeronave;
}

void inicializa_fila(Pista *pista)
{
    pista->primeiro = NULL;
    pista->quantidade = 0;
}

Aviao ** busca_ultimo_aviao_pista(Pista *pista)
{
	Aviao **ultimo = &(pista->primeiro);
	while (*ultimo != NULL)
	{
		ultimo = &((*ultimo)->ant);
	}
	return ultimo;
}

void enqueue(Pista *pista, Aviao *novoAviao)
{
	Aviao **ultimaPosicao = busca_ultimo_aviao_pista(pista);
	*ultimaPosicao = novoAviao;
	pista->quantidade++;
}

Aviao * dequeue(Pista *pista)
{
    Aviao *aux = pista->primeiro;
    pista->primeiro = aux->ant;
	pista->quantidade--;
    return aux;
}

void apaga_pista(Pista *pista)
{
	while (pista->primeiro != NULL)
	{
		free(dequeue(pista));
	}
}

void mostra_fila_espera(Pista pista)
{
    int cont = 0;
    Aviao *aux = pista.primeiro;

	while (aux != NULL)
    {
		printw("%d -> %d - %s\n", ++cont, aux->id, aux->nome);
		aux = aux->ant;
    }
}

void mostra_aviao(Aviao aviao)
{
    printw("- ID: %d\n"
           "- Nome: %s\n"
           "- Origem: %s\n"
           "- Destino: %s\n", aviao.id, aviao.nome, aviao.origem, aviao.destino);
}

Aviao * fila_vazia(Pista *pista)
{
	return pista->primeiro;
}

Aviao * autoriza_aviao(Pista *pista)
{
    Aviao *aux;
    pista->primeiro->autorizacao = 1;
    aux = dequeue(pista);
    return aux;
}
