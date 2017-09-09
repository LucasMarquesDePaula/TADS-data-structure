#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "fila.h"
#include "curses.h"
#include "aviao.h"


void menu(Pista *pousos, Pista *decolagens)
{
    Aviao *valor, *aux;
    char menu, decisao;

    do
    {
		clear();
		refresh();
		printf("*\\============ Painel de Controle - Espaço Aéreo TADS 2016 ============/*\n\n"
               "-> Número de aeronaves em fila de espera para:\n-> Pousar: %d\n-> Decolar: %d\n\n"
               "-> 1.  Autorizar a decolagem do primeiro avião na fila de decolagem\n"
               "-> 2.  Autorizar o pouso do primeiro avião na fila de pouso\n"
               "-> 3.  Adicionar um avião na fila de espera para decolagem\n"
               "-> 4.  Adicionar um avião na fila de espera para pouso\n"
               "-> 5.  Listar todos os aviões que estão na fila de espera para decolagem, por ordem de chegada\n"
               "-> 6.  Listar todos os aviões que estão na fila de espera para pouso, por ordem de chegada\n"
               "-> 7.  Listar as características do primeiro avião da fila, antes de autorizar a sua decolagem\n"
               "-> 8.  Listar as características do primeiro avião da fila, antes de autorizar o seu pouso\n"
               "-> 9.  Sair\n\n"
			"Digite o comando: ", pousos->quantidade, decolagens->quantidade);
		fflush(stdin);
		menu = getch();
		clear();
		refresh();
		switch(menu)
        {
        case '1':
            printw("-> Autorizar decolagem: \n\n");
			if (fila_vazia(decolagens) == NULL)
			{
                printw("A pista está vazia.\n\n");
			}
            else
            {
                aux = autoriza_aviao(decolagens);
				decola();
                printw("\n-> Avião %d - %s, com destino a %s, decolou.\n", aux->id, aux->nome, aux->destino);
				free(aux);
				aux = NULL;
            }
			break;
        case '2':
            printw("-> Autorizar pouso: \n\n");
			if (fila_vazia(pousos) == NULL)
			{
                printw("A pista está vazia.\n\n");
			}
            else
            {
                aux = autoriza_aviao(pousos);
				pousa();
				printw("\n-> Avião %d - %s, com origem de %s, pousou.\n", aux->id, aux->nome, aux->origem);
                free(aux);
				aux = NULL;
			}
            break;
        case '3':
            printw("-> Adicionar um avião na fila de espera para decolagem: \n\n");
            enqueue(decolagens, aloca_aviao(detalha_aviao()));
            break;
        case '4':
            printw("-> Adicionar um avião na fila de espera para pouso: \n\n");
            enqueue(pousos, aloca_aviao(detalha_aviao()));
            break;
        case '5':
			if (fila_vazia(decolagens) == NULL) 
			{
                printw("A fila está vazia.\n");
			}
            else
            {
                printw("-> Aviões que estão na fila de espera para decolagem por ordem de chegada:\n\n");
                mostra_fila_espera(*decolagens);
            }
            break;
        case '6':
			if (fila_vazia(pousos) == NULL)
			{
                printw("A fila está vazia.\n");
			}
            else
            {
                printw("-> Aviões que estão na fila de espera para pouso por ordem de chegada:\n\n");
                mostra_fila_espera(*pousos);
            }
            break;
        case '7':
            valor = fila_vazia(decolagens);
			if (valor == NULL)
			{
                printw("A fila está vazia.\n");
			}
            else
            {
                printw("-> Características do primeiro avião na fila de decolagem:\n\n");
                mostra_aviao(*valor);
                printw("\n-> Autorizar a decolagem? (s/n) \n");
				fflush(stdin);
				menu = getch();
				if (menu == 's' || menu == 'S')
				{
                    aux = autoriza_aviao(decolagens);
					decola();
					printw("\n-> Avião %d - %s, com destino a %s, decolou.\n\n", aux->id, aux->nome, aux->destino);
					free(aux);
					aux = NULL;
				}
            }
			valor = NULL;
            break;
        case '8':
            valor = fila_vazia(pousos);
			if (valor == NULL)
			{
                printw("A fila está vazia.\n");
			}
            else
            {
                printw("-> Características do primeiro avião na fila de pouso:\n\n");
                mostra_aviao(*valor);
                printw("\n-> Autorizar o pouso? (s/n) \n");
				fflush(stdin);
				menu = getch();
				if (menu == 's' || menu == 'S')
				{
                    aux = autoriza_aviao(pousos);
					pousa();
					printw("\n-> Avião %d - %s, com origem de %s, pousou.\n\n", aux->id, aux->nome, aux->origem);
					free(aux);
					aux = NULL;
				}
            }
			valor = NULL;
            break;
		case '9':
			printw("\nSaindo do programa.\n");
			break;
		default:
			printw("\nOpção inválida.\n");
        }
		printw("\nPressione Qualquer Tela para Continuar... \n");
		fflush(stdin);
		getch();
	}
    while(menu != '9');
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Pista pousos, decolagens;

	inicializa_fila(&pousos);
	inicializa_fila(&decolagens);
	initscr();

	menu(&pousos, &decolagens);

	apaga_pista(&pousos);
	apaga_pista(&decolagens);

	endwin();

    return 0;
}
