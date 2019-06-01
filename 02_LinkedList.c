#include <stdio.h>
#include <stdlib.h>

struct Node//структура, описывающая узел списка 
 {
  int value;
  struct Node *next;
  struct Node *prev;
 } Node;

struct List //структура, описывающая сам список
 {
  struct Node* begin;
  struct Node* end;
 } List;
 
void init(struct List* SP, int value)//инициализация пустого списка
 {
  struct Node* tmp;
  tmp = (struct Node*)malloc(sizeof(struct Node));
  tmp->value = value;
  tmp->next = NULL;
  tmp->prev = NULL;
  SP->begin = tmp;
  SP->end = tmp;
 }
 
 int clear(struct List* SP)//удалить все элементы в списке
 {
  if (isEmpty(SP) == 1)
   {
    struct Node *tmp = SP->begin;
    struct Node *temp = NULL;
    while (tmp != NULL)
     {
      temp = tmp->next;
      free(tmp);
      tmp = temp;
     }
    SP->begin = NULL;
    SP->end = NULL;
   }
 }
 
int isEmpty(struct List* SP)//проверка на пустой список
 {
  return SP->begin == NULL && SP->end == NULL;
 }

struct Node* find(struct List* SP, int k)//поиск узла по значению
 {
  struct Node *tmp = SP->begin;
  while (tmp->value != k) 
   {
    if (tmp->next != NULL) 
     {
      tmp = tmp->next;
     }
    else 
     {
      return 0;
     }
   }
  return tmp;
 }



int push_back(struct List* SP, int x)//вставка в конец
 {
  if (isEmpty(SP) == 1)
  init(SP, x);
  else
   {
    struct Node *tmp = (struct Node*)malloc(sizeof(struct Node));
    tmp->value = x;
    tmp->prev = SP->end;
    tmp->next = NULL;
    SP->end = tmp;
    tmp->prev->next = tmp;
   }
  return 0;
 }

int push_front(struct List* SP, int x)//вставка в начало
 {
  if (isEmpty(SP) == 1)
  init(SP, x);
  else
   {
    struct Node *tmp = (struct Node*)malloc(sizeof(struct Node));
    tmp->value = x;
    tmp->prev = NULL;
    tmp->next = SP->begin;
    SP->begin = tmp;
    tmp->next->prev = tmp;
   }
  return 0;
 }

int insertAfter(struct List* SP, int num, int data)//вставка значения после указанного узла
 {
  struct Node* tmp = SP->begin;
  for (int i = 1; i<num; i++)
   {
    tmp = tmp->next;
    if (tmp == NULL)
    return -1;
   }
  struct Node *temp = malloc(sizeof(Node));
  temp->value = data;
  temp->next = tmp->next;
  temp->prev = tmp;
  tmp->next->prev = temp;
  tmp->next = temp;
  return 0;
 }

int insertBefore(struct List* SP, int num, int data)//вставка перед указанным узлом
 {
  struct Node* tmp = SP->begin;
  for (int i = 1; i < num; i++)
   {
    tmp = tmp->next;
    if (tmp == NULL)
    return -1; 
   }
  struct Node *temp = malloc(sizeof(Node));
  temp->value = data;
  temp->prev = tmp->prev;
  temp->next = tmp;
  tmp->prev = temp;
  temp->prev->next = temp;
  return 0;
 }
 
 int removeFirst(struct List* SP, int x)//удалить первый элемент с указанным значением
 {
  struct Node* EL = find(SP, x);
  if (EL != NULL) 
   {
    removenode(SP, EL);
    return 0;
   }
  return -1;
 }

void removenode(struct List* SP, struct Node *tmp)//для удаления узлов
 {
  if (tmp != NULL) 
   {
    if (tmp == SP->begin && tmp == SP->end) 
     {
      clear(SP);
      return;
     }
    if (tmp == SP->begin)
     {
      SP->begin = tmp->next;
      tmp->next->prev = NULL;
     }
    else if (tmp == SP->end)
     {
      SP->end = tmp->prev;
      tmp->prev->next = NULL;
     }
    else if (tmp != SP->begin && tmp != SP->end)
     {
      tmp->next->prev = tmp->prev;
      tmp->prev->next = tmp->next;
     }
    free(tmp);
   }
 }
 
 struct Node* find_invers(struct List* SP, int k)//для поиска узла (исп в удалении последнего)
 {
  struct Node *tmp = SP->end;
  while (tmp->value != k) 
   {
    if (tmp->prev != NULL) 
     {
      tmp = tmp->prev;
     }
    else 
     {
      return 0;
     }
   }
  return tmp;
 }


int removeLast(struct List* SP, int x)//удалить последний элемент с указанным значением
 {
  struct Node* EL = find_invers(SP, x);
  if (EL != NULL) 
   {
    removenode(SP, EL);
    return 0;
   }
  return -1;
 }
 
void print(struct List* SP)//вывест значения списка в прямом порядке
 {
  struct Node* tmp = SP->begin;
  while (tmp->next != NULL)
   {
    printf("%d ", tmp->value);
    tmp = tmp->next;
   }
  printf("%d\n", tmp->value);
 }
 

void print_invers(struct List* SP)//вывест значения списка в обратном порядке
 {
  struct Node* tmp = SP->end;
  while (tmp->prev != NULL)
   {
    printf("%d ", tmp->value);
    tmp = tmp->prev;
   }
  printf("%d\n", tmp->value);
 }

int main()
 {
  int n, a;
  struct List* list = (struct List*)malloc(sizeof(struct List));//инициализация списка и добавление узлов
  scanf("%d", &n);
  for (int i = 0; i<n; i++)
   {
    scanf("%d", &a);
    push_back(list, a);
   }
  print(list);//вывод значений

  int k[3];//поиск значений k1 k2 k3
  scanf("%d%d%d", &k[0], &k[1], &k[2]);
  for (int i = 0; i<3; i++) 
   {
    if (find(list, k[i]) != NULL)
    printf("1 ");
    else
    printf("0 ");
   }
  printf("\n");

  int m;
  scanf("%d", &m);
  push_back(list, m);//вставить m в конец списка
  print_invers(list);//вывести в обратном порядке
  int t;
  scanf("%d", &t);
  push_front(list, t);//вставить t в начало списка
  print(list);//вывести в прямом порядке

  int j, x;
  scanf("%d%d", &j, &x);
  insertAfter(list, j, x);//вставить после
  print_invers(list);//вывести в обратном порядке

  int u, y;
  scanf("%d%d", &u, &y);
  insertBefore(list, u, y);//вставить y перед u
  print(list);//вывести в прямом порядке
  int z;
  scanf("%d", &z);
  removeFirst(list, z);//удалить первый
  print_invers(list);//вывести в обратном порядке
  int r;
  scanf("%d", &r);
  removeLast(list, r);//удалить последний
  print(list);//вывести в прямом порядке

  clear(list);//удалить все узлы
  return 0;
 }