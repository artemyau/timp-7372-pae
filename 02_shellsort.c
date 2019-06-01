#include <stdio.h>

void ShellSort(int *array, int length)
{
	int i, j, d;
	int tmp;
	for (d = length / 2; d > 0; d /= 2)//выор расстояния d между сравниваемыми э-ми
		for (i = d; i < length; i++)
		{
			tmp = array[i];
			for (j = i; j >= d; j -= d)
			{
				if (tmp < array[j - d])//сравнение э-ов
					array[j] = array[j - d];
				else
					break;
			}
			array[j] = tmp;
		}
}

int main()
{
	int n;
	scanf("%d", &n);//кол-во э-ов
	int array[n];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &array[i]);//считывание э-ов
	}
	ShellSort(array, n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", (array[i]));//выведение отстортированного массива
	}
	printf("\n");
}