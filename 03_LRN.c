#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>
#include <string.h>

typedef struct Node//структура узла
{
	int information;
	struct Node * left;
	struct Node * right;
	struct Node * original;
}Node;

typedef struct Tree//структура дерева
{
	struct Node * C;
	int count;
}Tree;

void init(Tree* K)//инициализация
{
	struct Tree * next_Tree = malloc(sizeof next_Tree);
	next_Tree->C = NULL;
	next_Tree->count = 0;
	K = next_Tree;
}

int find(Tree* K, int aim, Node* Z)//поиск узла
{
	struct Node * ZZ;
	ZZ = K->C;
	if (K->C == NULL)
	{
		return 1;
	}
	while (1)
	{
		if (ZZ == NULL)
		{
			return 1;
		}
		else if (ZZ->information == aim)
		{
			Z->information = ZZ->information;
			Z->left = ZZ->left;
			Z->right = ZZ->right;
			Z->original = ZZ->original;
			return 0;
		}
		else if (aim > ZZ->information)
		{
			ZZ = ZZ->right;
		}
		else
		{
			ZZ = ZZ->left;
		}
	}
	return 1;
}

int insert(Tree* K, int aim)//ввод узла
{
	struct Node * Z, ** ZZ, *last_Node = NULL;
	struct Node * cc;
	cc = malloc(sizeof * cc);

	int error = find(K, aim, cc);
	if (error == 0)
	{
		return 1;
	}
	ZZ = &K->C;
	Z = K->C;
	while (1)
	{
		if (Z == NULL)
		{
			Z = *ZZ = malloc(sizeof * Z);
			if (Z != NULL)
			{
				Z->information = aim;
				Z->left = NULL;
				Z->right = NULL;
				Z->original = last_Node;
				K->count++;
				return 0;
			}
			else
			{
				return 2;
			}
		}
		last_Node = Z;
		if (aim > Z->information)
		{
			ZZ = &Z->right;
			Z = Z->right;
		}
		else
		{
			ZZ = &Z->left;
			Z = Z->left;
		}
	}
	return 0;
}

int Deepness(struct Node * Z, int Deep)//глубина узла
{
	if (Z == NULL)
	{
		return Deep;
	}

	int D1 = Deepness(Z->left, Deep + 1);
	int D2 = Deepness(Z->right, Deep + 1);
	return (D1 > D2) ? D1 : D2;
}

void printNode(struct Node * Z, int current, int Deep, int first)//вывод узла
{
	if (current == Deep)
	{
		if (first > 0)
		{
			printf(" ");
		}
		if (Z == NULL)
		{
			printf("_");
		}
		else
		{
			printf("%d", Z->information);
		}
	}
	else if (Z != NULL)
	{
		printNode(Z->left, current + 1, Deep, first);
		printNode(Z->right, current + 1, Deep, first + 1);
	}
	else
	{
		printNode(Z, current + 1, Deep, first);
		printNode(Z, current + 1, Deep, first + 1);
	}
}

void print(struct Node * Z)
{
	int m = Deepness(Z, 0);
	for (int i = 1; i <= m; i++)
	{
		printNode(Z, 1, i, 0);
		printf("\n");
	}
}

void printTree(struct Tree * K)//вывод дерева
{
	print(K->C);
}

void printLRN(struct Node * Z, int flag_Tree)//вывод дерева в порядке обратного обхода
{
	if (Z->left != NULL)
	{
		printLRN(Z->left, flag_Tree + 1);
	}
	if (Z->right != NULL)
	{
		printLRN(Z->right, flag_Tree + 1);
	}
	printf("%d", Z->information);
	if (flag_Tree > 0)
	{
		printf(" ");
	}
}

int main()
{
	struct Tree * K = malloc(sizeof K);
	init(K);//инициализация, добавление узлов
	for (int i = 0; i < 7; i++)
	{
		int X;
		scanf("%d", &X);
		insert(K, X);
	}
	printLRN(K->C, 0);//вывод в порядке обратного обхода
	printf("\n");
	return 0;
}