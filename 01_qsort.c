#include <stdio.h>

void quicksort(int* arr, int length)
{
	int size = length;
	int k = 0;
	int c = arr[(int)(length / 2)];//выбор опорного элемента
	int tmp = 0;
	do
	{
		while (arr[k] < c) k++;
		while (arr[length] > c) length--;
		if (k <= length) 
		{
			tmp = arr[k];
			arr[k] = arr[length];
			arr[length] = tmp;
			k++;
			length--;
		}
	} while (k <= length);
	if (length > 0) quicksort(arr, length);
	if (length > 0) quicksort(arr + k, size - k);
}

int main()
{
	int n;
	scanf("%d", &n);
	int arr[n];//инициализация массива, считывание элементов
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	quicksort(arr, n);//вызов ф-ии
	for (int i = 0; i < n; i++)//выведение э-ов
	{
		printf("%d ", (arr[i]));
	}
	printf("\n");
}