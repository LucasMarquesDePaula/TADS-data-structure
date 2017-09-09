typedef Node Posicao;
typedef Node Acao;
typedef Stack Acoes;

typedef struct {
	Posicao posicaoAtual;
	Acoes oQueFazer, oQueFoiFeito;
} Rato;

void inicializaRato(Rato* rato)
{
	rato->oQueFazer = NewStack();
	rato->oQueFoiFeito = NewStack();
	rato->posicaoAtual.column = 1;
	rato->posicaoAtual.row = 1;
	rato->posicaoAtual.columnIncrement = 0;
	rato->posicaoAtual.rowIncrement = 0;
}

void finalizaRato(Rato* rato)
{
	EmptyStack(&(rato->oQueFazer));
	EmptyStack(&(rato->oQueFoiFeito));
}

void analisaPossiveisRotas(Rato rato, Mapa mapa)
{
	//AVALIA PARA ESQUERDA 
	if (rato.posicaoAtual.column > 0 && mapa.labirinto[rato.posicaoAtual.row][rato.posicaoAtual.column - 1] == LIVRE)
	{
		Push(rato.oQueFazer, NewNode(rato.posicaoAtual.row, rato.posicaoAtual.column, 0, -1));
	}

	//AVALIA PARA BAIXO 
	else if (rato.posicaoAtual.row < mapa.numeroDeLinhas - 1 && mapa.labirinto[rato.posicaoAtual.row + 1][rato.posicaoAtual.column] == LIVRE)
	{
		Push(rato.oQueFazer, NewNode(rato.posicaoAtual.row, rato.posicaoAtual.column, 1, 0));
	}

	//AVALIA PARA DIREITA 
	else if (rato.posicaoAtual.column < mapa.numeroDeColunas - 1 && mapa.labirinto[rato.posicaoAtual.row][rato.posicaoAtual.column + 1] == LIVRE)
	{
		Push(rato.oQueFazer, NewNode(rato.posicaoAtual.row, rato.posicaoAtual.column, 0, 1));
	}

	//AVALIA PARA CIMA 
	else if (rato.posicaoAtual.row > 0 && mapa.labirinto[rato.posicaoAtual.row - 1][rato.posicaoAtual.column] == LIVRE)
	{
		Push(rato.oQueFazer, NewNode(rato.posicaoAtual.row, rato.posicaoAtual.column, -1, 0));
	}

}

void progredir(Rato* rato)
{
	Acao* acao = Pop(rato->oQueFazer);
	rato->posicaoAtual.row += acao->rowIncrement;
	rato->posicaoAtual.column += acao->columnIncrement;
	Push(rato->oQueFoiFeito, acao);
}

void regredir(Rato* rato)
{
	Acao* acao = Pop(rato->oQueFoiFeito);
	rato->posicaoAtual.row -= acao->rowIncrement;
	rato->posicaoAtual.column -= acao->columnIncrement;
	free(acao);
}

int podeProgredir(Rato rato)
{
	return !isEmpty(rato.oQueFazer);
}

int podeRegredir(Rato rato)
{
	return !isEmpty(rato.oQueFoiFeito);
}

int podeSeLocomover(Rato rato)
{
	return podeProgredir(rato) || podeRegredir(rato);
}

int permaneceNoLabirinto(Rato rato, Mapa mapa)
{
	return	rato.posicaoAtual.row > 0 && rato.posicaoAtual.row < mapa.numeroDeLinhas - 1
		&& rato.posicaoAtual.column > 0 && rato.posicaoAtual.column < mapa.numeroDeColunas - 1;
}