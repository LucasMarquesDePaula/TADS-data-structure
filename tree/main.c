// ALUNOS: WESLEY MAFFAZZOLLI E LUCAS MARQUES DE PAULA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUMERO_DE_NODOS 2
#define ESQ 1
#define DIR 0
#define ANT 0
#define PROX 1
#define TOPO PROX
#define SEPARADORES "()"
#define NUMEROS "0123456789"
#define OPERADORES "+-/*^s"
#define TAM_MAX_EXP 256
#define LIN 15
#define COL 150

typedef char Dado[TAM_MAX_EXP];

typedef char MatrizChar[LIN][COL];
typedef struct nodo {
	Dado dado;
	struct nodo *nodos[NUMERO_DE_NODOS];
} Nodo;

typedef Nodo* Arvore;

typedef Nodo* Lista;

typedef char Expressao[TAM_MAX_EXP];

Nodo* novoNodo(Dado dado) {
	Nodo*nodo = (Nodo*) malloc(sizeof(Nodo));
	if (nodo == NULL) {
		exit(EXIT_FAILURE);
	}
	memset(nodo->nodos, NULL, sizeof(Nodo*) * NUMERO_DE_NODOS);
	memcpy(nodo->dado, dado, sizeof(Dado));
	return nodo;
}

Lista insereLista(Lista lista, Nodo* nodo) {
	if (lista != NULL) {
		nodo->nodos[PROX] = lista;
		lista->nodos[ANT] = nodo;
	}
	return nodo;
}

Lista removeLista(Nodo* nodo) {
	if (nodo->nodos[PROX] != NULL) {
		nodo->nodos[PROX]->nodos[ANT] = nodo->nodos[ANT];
	}
	if (nodo->nodos[ANT] != NULL) {
		nodo->nodos[ANT]->nodos[PROX] = nodo->nodos[PROX];
	}
	return nodo;
}

int validaSeparador(char c) {
	char spt[3];
	strcpy(spt, SEPARADORES);
	return strchr(spt, c) != NULL ? (int)(strchr(spt, c) - spt) + 1 : 0;
}

int validaNumero(char c) {
	return strchr(NUMEROS, c) != NULL;
}

int validaOperador(char c) {
	return strchr(OPERADORES, c) != NULL;
}

Lista transformaExpressaoEmLista(Expressao exp) {
	Lista lista = NULL;
	Expressao aux;
	int i;
	for (i = 0; i < TAM_MAX_EXP && exp[i] != '\0'; i++) {
		strcpy(aux, "");
		if (validaSeparador(exp[i])) {
			sprintf(aux, "%c", exp[i]);
			lista = insereLista(lista, novoNodo(aux));
		}

		else if (validaNumero(exp[i])) {
			do
			{
				sprintf(aux, "%s%c", aux, exp[i]);
				i++;
			} while (i < TAM_MAX_EXP && exp[i] != '\0' && validaNumero(exp[i]));
			i--;
			lista = insereLista(lista, novoNodo(aux));
		}

		else if (validaOperador(exp[i])) {
			sprintf(aux, "%c", exp[i]);
			lista = insereLista(lista, novoNodo(aux));
		}
	}
	return lista;
}

int grauPrecedencia(char c) {
	char grau[32];
	strcpy(grau, OPERADORES);
	return (int)(strchr(grau, c) - grau);
}

Nodo* localizaFimSeparador(Nodo* nodo) {
	Nodo* aux = NULL;
	int contaSeparadores = 0;
	int valida;
	int sentido = validaSeparador(*(nodo->dado)) - 1;
	do {
		aux = aux == NULL ? nodo : aux->nodos[sentido];
		valida = validaSeparador(*(aux->dado));
		if (valida == 2) {
			contaSeparadores++;
		}
		else if (valida == 1) {
			contaSeparadores--;
		}
	} while (aux != NULL && contaSeparadores != 0);

	return aux;
}

Nodo* localizaInicioLista(Nodo* nodo) {
	Nodo* aux = nodo;
	while (aux != NULL && aux->nodos[ANT] != NULL) {
		aux = aux->nodos[ANT];
	}
	return aux;
}

Nodo* localizaOperacaoMenorPrecedencia(Lista lista) {
	Nodo* aux = localizaInicioLista(lista);
	Nodo* menor = NULL;

	while (aux != NULL) {
		if (validaSeparador(*(aux->dado))) {
			aux = localizaFimSeparador(aux);
		}
		if (validaOperador(*(aux->dado)) && (menor == NULL || (grauPrecedencia(*(aux->dado)) < grauPrecedencia(menor->dado[0])))) {
			menor = aux;
		}
		aux = aux->nodos[PROX];
	}
	return menor;
}

Arvore limpaSeparadores(Lista lista) {
	Nodo* inicioSeparador = lista;
	int sentido = validaSeparador(*(lista->dado)) - 1;
	if (inicioSeparador != NULL && validaSeparador(*(inicioSeparador->dado))) {
		lista = lista->nodos[sentido];
		free(removeLista(localizaFimSeparador(inicioSeparador)));
		free(removeLista(inicioSeparador));
	}
	return lista;
}

Arvore transformaListaEmArvore(Lista lista) {
	Arvore arvore = NULL;
	while (lista != NULL && (arvore = localizaOperacaoMenorPrecedencia(lista)) == NULL && validaSeparador(*(lista->dado))) {
		lista = limpaSeparadores(lista);
	}
	if (arvore != NULL && arvore->nodos[DIR] != NULL) {
		arvore->nodos[DIR]->nodos[ESQ] = NULL;
		arvore->nodos[DIR] = transformaListaEmArvore(arvore->nodos[DIR]);
	}

	if (arvore != NULL && arvore->nodos[ESQ] != NULL) {
		arvore->nodos[ESQ]->nodos[DIR] = NULL;
		arvore->nodos[ESQ] = transformaListaEmArvore(arvore->nodos[ESQ]);
	}

	return arvore != NULL ? arvore : lista;
}

double calcula(double a, Nodo* o, double b) {
	double r = 0.;

	if (o->dado[0] == '-') {
		r = a - b;
	}
	else if (o->dado[0] == '+') {
		r = a + b;
	}
	else if (o->dado[0] == '*') {
		r = a * b;
	}
	else if (o->dado[0] == '/') {
		if (b != 0.) {
			r = a / b;
		}
	}
	else if (o->dado[0] == '^') {
		r = pow(a, b);
	}
	else if (o->dado[0] == 's') {
		r = sqrt(b);
	}
	return r;
}

double operaArvore(Arvore* arvore) {
	double r, a, b;
	r = a = b = 0.;
	if (*arvore != NULL) {
		if (validaNumero((**arvore).dado[0])) {
			sscanf((**arvore).dado, "%lf", &r);
		} else {
			a = operaArvore(&(**arvore).nodos[ESQ]);
			b = operaArvore(&(**arvore).nodos[DIR]);
			r = calcula(a, *arvore, b);
		}
	}
	free(*arvore);
	*arvore = NULL;
	return r;
}

int imprimeDadoMatrizChar(MatrizChar matriz, Dado dado, int posicaoAtualCursor, int nivel) {
	int i = 0;
	matriz[nivel][posicaoAtualCursor + i] = '(';
	while (dado[i] != '\0') {
		matriz[nivel][posicaoAtualCursor + i + 1] = dado[i];
		i++;
	}
	matriz[nivel][posicaoAtualCursor + i + 1] = ')';
	return posicaoAtualCursor + i + 2;
}

void imprimeTracosArvoreMatrizChar(MatrizChar matriz, Arvore arvore, int posicaoCursorEsquerda, int nivel) {
	int posicaoAtualCursor = posicaoCursorEsquerda;

	while (matriz[nivel][posicaoAtualCursor] == ' ') {
		posicaoAtualCursor--;
	}

	posicaoAtualCursor++;
	while (matriz[nivel][posicaoAtualCursor] == ' ' && posicaoAtualCursor < COL) {
		matriz[nivel][posicaoAtualCursor] = '-';
		posicaoAtualCursor++;
	}
}

int imprimeArvoreParaMatrizChar(MatrizChar matriz, Arvore arvore, int posicaoAtualCursor, int nivel) {
	int posicaoCursorEsquerda = posicaoAtualCursor;

	if (arvore != NULL) {
		posicaoAtualCursor = posicaoCursorEsquerda = imprimeArvoreParaMatrizChar(matriz, arvore->nodos[ESQ], posicaoAtualCursor, nivel + 1);
	}

	posicaoAtualCursor = imprimeDadoMatrizChar(matriz, arvore != NULL ? arvore->dado : "", posicaoAtualCursor, nivel);

	if (arvore != NULL) {
		posicaoAtualCursor = imprimeArvoreParaMatrizChar(matriz, arvore->nodos[DIR], posicaoAtualCursor, nivel + 1);
	}

	if (arvore != NULL) {
		imprimeTracosArvoreMatrizChar(matriz, arvore, posicaoCursorEsquerda, nivel + 1);
	}

	return posicaoAtualCursor;
}

void preparaMatrizChar(MatrizChar matriz) {
	int i, j;
	for (i = 0; i < LIN; i++) {
		for (j = 0; j < COL; j++) {
			matriz[i][j] = ' ';
		}
	}
}

void mostraMatrizChar(MatrizChar matriz) {
	int i, j;
	for (i = 0; i < LIN; i++) {
		for (j = 0; j < COL; j++) {
			printf("%c", matriz[i][j]);
		}
		printf("\n");
	}
}

int main() {
	Arvore arvore = NULL;
	Lista listaDeExpressoes = NULL;
	Nodo* nodo = NULL;
	Dado entradaUsuario;
	MatrizChar matrizChar;


	printf("Entre com uma expressao ou em branco para executar calculos:\n");
	gets(entradaUsuario);
	while(strcmp("", entradaUsuario) != 0) {
		listaDeExpressoes = insereLista(listaDeExpressoes, novoNodo(entradaUsuario));
		printf("Entre com uma expressao ou em branco para executar calculos:\n");
		gets(entradaUsuario);
	}
	while (listaDeExpressoes != NULL) {
		system("cls");
		nodo = listaDeExpressoes;
		listaDeExpressoes = listaDeExpressoes->nodos[PROX];
		printf("Expressao Avaliada: %s\n", nodo->dado);
		arvore = transformaListaEmArvore(transformaExpressaoEmLista(nodo->dado));
		preparaMatrizChar(matrizChar);
		imprimeArvoreParaMatrizChar(matrizChar, arvore, 0, 0);
		mostraMatrizChar(matrizChar);
		printf("Resultado obtido: %lf\nPressione Qualquer tecla para continuar...", operaArvore(&arvore));
		getchar();
	}
	//Lista lista = parse("-1+2*(4-3+(s(3+7*10))*(-(50-30))-2)");
	//Lista lista = parse("-1");
	//Lista lista = parse("-1/10");
	//Lista lista = parse("2^4");
	//Lista lista = parse("-2^4");
	//Lista lista = parse("(-2)^4/3-(12-s(4 + 7*30))");
	//Lista lista = parse("sqrt(4 + 7*30)");
	return 0;
}
