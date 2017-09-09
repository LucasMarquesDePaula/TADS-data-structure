typedef struct Node {
	int rowIncrement, columnIncrement;
	int row, column;
	struct Node *prev;
} Node;

typedef Node* Stack;

Node *NewNode(int row, int column, int rowIncrement, int columnIncrement)
{
	Node* novo = (Node*)malloc(sizeof(Node));
	if (novo == NULL)
	{
		exit(EXIT_FAILURE);
	}
	novo->column = column;
	novo->row = row;
	novo->rowIncrement = rowIncrement;
	novo->columnIncrement = columnIncrement;
	novo->prev = NULL;
	return novo;
}

Stack NewStack()
{
	return NewNode(-1, -1, -1, -1);
}

Stack Push(Stack stack, Node* node)
{
	node->prev = stack->prev;
	stack->prev = node;
	return stack;
}

Node* Top(Stack stack)
{
	return stack->prev;
}

Node* Pop(Stack stack)
{
	Node* node = stack->prev;
	if (node != NULL)
	{
		stack->prev = node->prev;
	}
	return node;
}

int isEmpty(Stack stack)
{
	return stack->prev == NULL ? 1 : 0;
}

void EmptyStack(Stack* stack)
{
	if (*stack != NULL)
	{
		EmptyStack(&((*stack)->prev));
		free(*stack);
		*stack = NULL;
	}
}