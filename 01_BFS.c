#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>

typedef struct Node//структура узла
{
	int information;
	struct Node * left;
	struct Node * right;
	struct Node * original;
}Node;

typedef struct tree//структура дерева
{
	struct Node * C;

	int count;
}
tree;

void init(tree* K)//инициировать дерево
{
	struct tree * next_tree = malloc(sizeof next_tree);
	next_tree->C = NULL;
	next_tree->count = 0;
	K = next_tree;
}

int find(tree* K, int aim, Node* Z)//поиск узла
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

int insert(tree* K, int aim)//втавка узла
{
	struct Node * Z, ** St, *pr_St = NULL;
	struct Node * F;
	F = malloc(sizeof * F);
	int error_tree = find(K, aim, F);
	if (error_tree == 0)
	{
		return 1;
	}
	St = &K->C;
	Z = K->C;
	while (1)
	{
		if (Z == NULL)
		{
			Z = *St = malloc(sizeof * Z);
			if (Z != NULL)
			{
				Z->information = aim;
				Z->left = NULL;
				Z->right = NULL;
				Z->original = pr_St;
				K->count++;
				return 0;
			}
			else
			{
				return 2;
			}
		}

		pr_St = Z;
		if (aim > Z->information)
		{
			St = &Z->right;
			Z = Z->right;
		}
		else
		{
			St = &Z->left;
			Z = Z->left;
		}
	}
	return 0;
}

int R(struct Node * Z, int Deepness)
{
	if (Z == NULL)
	{
		return Deepness;
	}
	int R1 = R(Z->left, Deepness + 1);
	int R2 = R(Z->right, Deepness + 1);
	return (R1 > R2) ? R1 : R2;
}

void printNode(struct Node * Z, int current, int Deepness, int first)//вывести узел
{
	if (current == Deepness)
	{
		if (first > 0)
		{
			printf(" ");
		}
		if (Z == NULL)
		{
			printf(" ");
		}
		else
		{
			printf("%d", Z->information);
		}
	}
	else if (Z != NULL)
	{
		printNode(Z->left, current + 1, Deepness, first);
		printNode(Z->right, current + 1, Deepness, first + 1);
	}
	else
	{
		printNode(Z, current + 1, Deepness, first);
		printNode(Z, current + 1, Deepness, first + 1);
	}
}

void print(struct Node * Z)//для выведения дерева
{

	int Q = R(Z, 0);
	for (int i = 1; i <= Q; i++)
	{
		printNode(Z, 1, i, 0);
		printf("\n");
	}
}

void printTree(struct tree * K)//вывести дерево
{
	print(K->C);
}

void printBFS(struct Node * Z)
{
	int Q = R(Z, 0);
	int flag_tree = 0;
	for (int i = 1; i <= Q; i++)
	{
		if (flag_tree > 0)
		{
			printf(" ");
		}
		else
		{
			flag_tree++;
		}
		printNode(Z, 1, i, 0);
	}
}

int main()
{
	struct tree * K = malloc(sizeof K);
	init(K);//инициализация, добавление узлов
	for (int i = 0; i < 7; i++)
	{
		int a;
		scanf("%d", &a);
		insert(K, a);
	}
	printBFS(K->C);//вывести узлы в порядке обхода в ширину
	printf("\n");
	return 0;
}