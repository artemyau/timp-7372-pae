#include <stdio.h>

float rfact=1.2473309;//оптимальное значение фактора уменьшения
int temporal;//используется при замене

void combsort(int *arr, int length)//функция сортировки расческой
{
	if (length != 0)//проверка на наличие хотя бы одного элемента
	{
		int step = length, i;
		int changed = 1;
		while (step > 1 || changed)
		{
			if (step > 1)
				step /= rfact;//изменение расстояния между сравниваемыми элементами
			changed = 0;
			for (i = 0; i + step < length; ++i)
				if (arr[i + step] > arr[i])//сравнивание i-го и i-го + шаг элеметов
				{
					temporal = arr[i];
					arr[i] = arr[i + step];
					arr[i + step] = temporal;
					changed = 1;
				}
		}
	}
	else
	    printf("Массив не содержит элементов");
}


int main()
{
	int n;
	scanf("%d", &n);//ожидаемое количество элементов n
	int arr[n];
	for (int i = 0; i < n; i++)//введение n элементов
	{
		scanf("%d", &arr[i]);
	}
	combsort(arr, n);// вызов функции сотрировки 
	for (int i = 0; i < n; i++)// вывод элементов отсортированного массива
	{
		printf("%d ", (arr[i]));
	}
}
	printf("\n");
}