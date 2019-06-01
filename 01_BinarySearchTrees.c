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
} Node;

typedef struct Tree//структура дерева
{
	struct Node * root;
	int count;
}
Tree;

void init(Tree * K)//инициализация дерева
{
	struct Tree * next_K = malloc(sizeof next_K);
	next_K->root = NULL;
	next_K->count = 0;
	K = next_K;
}

int find(Tree* K, int value, Node* Z)//поиск элемента по значению
{
	struct Node * Z2;
	Z2 = K->root;
	if (K->root == NULL)
	{
		return 1;
	}

	while (1)
	{
		if (Z2 == NULL)
		{
			return 1;
		}
		else if (Z2->information == value)
		{
			Z->information = Z2->information;
			Z->left = Z2->left;
			Z->right = Z2->right;
			Z->original = Z2->original;
			return 0;
		}
		else if (value > Z2->information)
		{
			Z2 = Z2->right;
		}
		else
		{
			Z2 = Z2->left;
		}
	}
	return 1;
}

int insert(Tree* K, int value)//вставка в дерево
{
	struct Node * Z, ** ZZ, *last_Z = NULL;
	struct Node * Q;
	Q = malloc(sizeof * Q);
	int err = find(K, value, Q);
	if (err == 0)
	{
		return 1;
	}
	ZZ = &K->root;
	Z = K->root;
	while (1)
	{
		if (Z == NULL)
		{
			Z = *ZZ = malloc(sizeof * Z);
			if (Z != NULL)
			{
				Z->information = value;
				Z->left = NULL;
				Z->right = NULL;
				Z->original = last_Z;
				K->count++;
				return 0;
			}
			else
			{
				return 2;
			}
		}
		last_Z = Z;
		if (value > Z->information)
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

int removenode(Tree* K, int value)//удаление узла
{
	Node * Z = K->root;
	if (K->root == NULL)
	{
		return 1;
	}
	while (1)
	{
		if (Z == NULL)
		{
			break;
			return 1;
		}
		else if (Z->information == value)
		{
			break;
		}
		else if (value > Z->information)
		{
			Z = Z->right;
		}
		else
		{
			Z = Z->left;
		}
	}

	if ((Z->left == NULL) && (Z->right == NULL))
	{
		if (Z->original->right->information == Z->information)
		{
			Z->original->right = NULL;
		}
		else
		{
			Z->original->left = NULL;
		}
	}
	else if (Z->right == NULL)
	{
		*Z = *Z->left;
	}
	else if (Z->left == NULL)
	{
		*Z = *Z->right;
	}
	else
	{
		Node * search = Z->right;
		int min_value;
		Node *min;
		while (1)
		{
			if (search == NULL)
			{
				break;
			}
			else
			{
				min = search;
				min_value = search->information;
				search = search->left;
			}
		}
		Z->information = min->information;
		Z = min;
		if ((Z->left == NULL) && (Z->right == NULL))
		{
			if (Z->original->right->information == Z->information)
			{
				Z->original->right = NULL;
			}
			else
			{
				Z->original->left = NULL;
			}
		}
		else if (Z->right == NULL)
		{
			*Z = *Z->left;
		}
		else
		{
			*Z = *Z->right;
		}
	}
	K->count--;
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

void printNode(struct Node * Z, int current, int Deep, int first)//вывести узел и потомков
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

void print(struct Node * Z)//вывести узел
{
	int E = Deepness(Z, 0);
	for (int i = 1; i <= E; i++)
	{
		printNode(Z, 1, i, 0);
		printf("\n");
	}
}

void printTree(struct Tree * K)//вывести дерево
{
	print(K->root);
}

void dump(struct Node * Z)
{
	if (Z != NULL)
	{
		printf("%d ", Z->information);
		dump(Z->left);
		dump(Z->right);
	}
} 

int removenodeMin(Node* Z)//удалить минимальный э-т поддерева
{

	if (Z->left == NULL)
	{
		Z = Z->right;
	}
	while (1)
	{
		if (Z->left == NULL)
		{
			if ((Z->left == NULL) && (Z->right == NULL))
			{
				if (Z->original->right->information == Z->information)
				{
					Z->original->right = NULL;
				}
				else
				{
					Z->original->left = NULL;
				}
			}
			else if (Z->right == NULL)
			{
				*Z = *Z->left;
			}
			else
			{
				*Z = *Z->right;
			}
			return Z->information;
		}
		else
		{
			Z = Z->left;
		}
	}
}

int rotateRight(Tree * K, Node *x)//вращать вправо
{
	Node * y = x->left;
	if ((y != NULL) && (x != NULL))
	{
		x->left = y->right;

		if (y->right != NULL)
		{
			y->right->original = x;
		}
		y->original = x->original;

		if (x->original != NULL)
		{
			if (x->original->left == x)
			{
				x->original->left = y;
			}
			else
			{
				x->original->right = y;
			}
		}
		K->root = y;
		y->right = x;
		x->original = y;
		return 0;
	}
	else
	{
		return 1;
	}
}

int rotateLeft(Tree * K, Node *x)//вращать влево
{
	Node * y = x->right;
	if ((y != NULL) && (x != NULL))
	{
		x->right = y->left;
		if (y->left != NULL)
		{
			y->left->original = x;
		}
		y->original = x->original;
		if (x->original != NULL)
		{
			if (x->original->right == x)
			{
				x->original->right = y;
			}
			else
			{
				x->original->left = y;
			}
		}
		K->root = y;
		y->left = x;
		x->original = y;
		return 0;
	}
	else
	{
		return 1;
	}
}


int main()
{

	struct Tree * K = malloc(sizeof K);
	init(K);//инициализация
	for (int i = 0; i < 4; i++)//добавление четырех узлов
	{
		int a;
		scanf("%d", &a);
		insert(K, a);
	}
	printTree(K);//вывод значений э-ов
	for (int i = 0; i < 3; i++)//считывание 3-х элементов, которые будут занесены в дерево
	{
		int a;
		scanf("%d", &a);
		insert(K, a);
	}
	printTree(K);//вывод значений э-ов

	int m1;//считывание m1, для которого будут найдены значения предков и потомков если они есть
	scanf("%d", &m1);
	struct Node * Z;
	Z = malloc(sizeof * Z);
	find(K, m1, Z);
	if (Z->original != NULL)
	{
		printf("%d ", Z->original->information);
	}
	else
	{
		printf("_ ");
	}
	if (Z->left != NULL)
	{
		printf("%d ", Z->left->information);
	}
	else
	{
		printf("_ ");
	}
	if (Z->right != NULL)
	{
		printf("%d\n", Z->right->information);
	}
	else
	{
		printf("_\n");
	}
	int m2;
	scanf("%d", &m2);//считывание m2, для которого будут найдены значения предков и потомков если они есть
	int err = find(K, m2, Z);
	if (err == 1)
	{
		printf("-\n");
	}
	else
	{
		if (Z->original != NULL)
		{
			printf("%d ", Z->original->information);
		}
		else
		{
			printf("_ ");
		}
		if (Z->left != NULL)
		{
			printf("%d ", Z->left->information);
		}
		else
		{
			printf("_ ");
		}
		if (Z->right != NULL)
		{
			printf("%d\n", Z->right->information);
		}
		else
		{
			printf("_\n");
		}
	}
	
	int m3;
	scanf("%d", &m3);//считывание m3, который будет удален
	removenode(K, m3);
	printTree(K);//вывод значений э-ов
	
	
	while (rotateLeft(K, K->root) != 1);//выполнять левый поворот, пока возможно
	printTree(K);//вывод значений э-ов
	
	
	while (rotateRight(K, K->root) != 1);//выполнять правый поворот, пока возможно
	printTree(K);//вывод значений э-ов
	
	
	printf("%d\n", K->count);
	printf("-\n");
	return 0;
}