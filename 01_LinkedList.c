#include <stdio.h>
#include<stdlib.h>


struct node//структура, описывающая узел списка
{ 
 	int value;
	struct node *next;
} node;

struct list//структура, описывающая сам список
{		
	struct node* first;
	struct node *last;
} list;

void init(struct list* struc,int value)//инициализация пустого списка
{
	struct node* tmp;
	tmp = (struct node*)malloc(sizeof(struct node));
	tmp->value=value;
	tmp->next=NULL;
	struc->first = tmp;
}

void clear(struct list* struc)//удалить все элементы в списке
{
	if(isEmpty(struc)==1)
	{
		struct node *tmp=struc->first;
		struct node *temp=NULL;
		while(tmp!=NULL)
		{
			temp=tmp->next;
			free(tmp);
			tmp=temp;
		}
		struc->first=NULL;
	}
}

int isEmpty(struct list* struc)//проверка на пустой список
{
	return struc->first==NULL;
}

struct node* find(struct list* struc,int value)//поиск узла по значению
{
	struct node *tmp=struc->first;
	while(tmp->value!=value)
	{
		if(tmp->next!=NULL)
			tmp=tmp->next;
		else
			return 0;
	}
	return tmp;
}

int push_back(struct list* struc, int x)//вставка в конец
{
	if(isEmpty(struc)==1)
		init (struc,x);
	else
	{
		struct node* tmp = (struct node*)malloc(sizeof(struct node));
		tmp->value=x;
		tmp->next=NULL;
		struct node* temp = struc->first;
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=tmp;
	}
	return 0;
}

int push_front(struct list* struc,int x)//вставка в начало
{
	if(isEmpty(struc)==1)
		init (struc,x);
	else
	{
		struct node *tmp = (struct node*)malloc(sizeof(struct node));
		tmp->value=x;
		tmp->next=struc->first;
		struc->first=tmp;
	}
	return 0;
}

int insertAfter	(struct list* struc,int num, int value)//вставка значения после указанного узла
{
	struct node *temp = malloc(sizeof(node));
	temp->value=value;

	struct node* tmp = struc->first;
	struct node* prev_tmp = struc->first;
	
	for (int i = 1;i<num+1;i++)
	{
		prev_tmp=tmp;
		tmp=tmp->next;
		if(tmp==NULL) 
			return -1;
	}
	prev_tmp->next=temp;
	temp->next=tmp;
	return 0;   
}

void removenode(struct list* struc, struct node *tmp)//для удаления узлов
{
	if(tmp!=NULL)
	{
		if (tmp==struc->first)
			struc->first=tmp->next;
		else
		{
			struct node *temp = (struct node*)malloc(sizeof(struct node));
			temp=struc->first;
			while(temp->next!=tmp)
				temp=temp->next;
			temp->next = tmp->next;
		}
		free(tmp);
	}
}

int RemoveFirst(struct list* struc, int x)//удалить первый элемент с указанным значением
{
	struct node* element = find(struc,x);
	if (element!=NULL)
	{
		removenode(struc,element);
		return 0;
	}
	return -1;
}

void print(struct list* struc)//вывести значения списка
{
	struct node* tmp=struc->first;
	while(tmp->next!=NULL)
	{
		printf("%d ", tmp->value);
		tmp=tmp->next;
	}
	printf("%d\n", tmp->value);
}


int main()
{
	int n,a;
    struct list* list=(struct list*)malloc(sizeof(struct list));//инициализация и добавление узлов в список	
	scanf("%d",&n);
	for (int i=0;i<n;i++)
	{
		scanf("%d",&a);
		push_back(list,a);
	}
	print(list);//выведение значений списка
	
	int k[3];//поиск узлов с указанными значениями k1 k2 и k3
        scanf("%d%d%d",&k[0],&k[1],&k[2]);
	for(int i=0;i<3;i++)
	{
		if(find(list,k[i])!=NULL)
			printf("1 ");
		else
			printf("0 ");
	}
	printf("\n");

	int m;//вставка в конец списка
	scanf("%d",&m);
	push_back(list,m);
	print(list);//выведение значений списка

	int t;
	scanf("%d",&t);//вставка в начало списка
	push_front(list,t);
	print(list);//выведение значений списка

	int j,x;//вставка после узла
	scanf("%d%d",&j,&x);
	insertAfter(list,j,x);
	print(list);//выведение значений списка

	int z;//удалить первый эелемент с указанным значением
	scanf("%d",&z);
	RemoveFirst(list,z);
	print(list);//выведение значений списка

	clear(list);
	return 0;
}