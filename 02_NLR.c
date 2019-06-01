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

void init(Tree * K)//инициализация дерева
{
	struct Tree * next_Tree = malloc(sizeof next_Tree);
	next_Tree->C = NULL;
	next_Tree->count = 0;
	K = next_Tree;
}

int find(Tree* K, int S, Node* Z)//поиск узла
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
		else if (ZZ->information == S)
		{
			Z->information = ZZ->information;
			Z->left = ZZ->left;
			Z->right = ZZ->right;
			Z->original = ZZ->original;
			return 0;
		}
		else if (S > ZZ->information)
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

int insert(Tree* K, int S)//ввод узла
{
	struct Node * Z, ** ZZ, *ZZZ = NULL;
	struct Node * plus;
	plus = malloc(sizeof * plus);
	int E = find(K, S, plus);
	if (E == 0)
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
				Z->information = S;
				Z->left = NULL;
				Z->right = NULL;
				Z->original = ZZZ;
				K->count++;
				return 0;
			}
			else
			{
				return 2;
			}
		}
		ZZZ = Z;
		if (S > Z->information)
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
		else {
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
	int H = Deepness(Z, 0);
	for (int i = 1; i <= H; i++)
	{
		printNode(Z, 1, i, 0);
		printf("\n");
	}
}

void printTree(struct Tree * K)//вывод дерева
{
	print(K->C);
}

void printNLR(struct Tree * K)//вывод прямого обхода
{
	Node * a[15];
	int V1 = 0;
	Node * write[15];
	int V2 = 0;
	Node * Z = K->C;
	while (V2 < K->count)
	{
		while (Z != NULL)
		{
			V2++;
			if (Z->right != NULL)
			{
				V1++;
				a[V1] = Z->right;
			}
			write[V2] = Z;
			Z = Z->left;
		}
		Z = a[V1];
		V1 -= 1;
	}
	int treeflag = 0;
	for (int i = 1; i <= V2; i++)
	{
		if (treeflag > 0)
		{
			printf(" ");
		}
		else
		{
			treeflag++;
		}
		printf("%d", write[i]->information);
	}
	printf("\n");
}

int main()
{
	struct Tree * K = malloc(sizeof K);
	init(K);//инициализация, добавление узлов
	for (int i = 0; i < 7; i++)
	{
		int a;
		scanf("%d", &a);
		insert(K, a);
	}
	printNLR(K);//вывод узлов в порядке прямого обхода
	return 0;
}