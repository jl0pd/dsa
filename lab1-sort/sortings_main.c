#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <limits.h>

static void swap (int *a, int *b){
	int tmp=*a;
	*a=*b;
	*b=tmp;
}
void arr_fill (int * array, int len){
	for (int i=0; i<len; i++){
		array[i]=rand() % 1000000;
	}
}
int findLargestNum(int* arr, int size){

	int i;
	int largestNum = -1;

	for(i = 0; i < size; i++){
		if(arr[i] > largestNum)
			largestNum = arr[i];
	}

	return largestNum;
}

void radixSort(int * arr, int size)
{

	int i;
	int semiSorted[size];
	int significantDigit = 1;
	int largestNum = findLargestNum(arr, size);

	while (largestNum / significantDigit > 0)
	{
		int bucket[10] = { 0 };

		for (i = 0; i < size; i++)
			bucket[(arr[i] / significantDigit) % 10]++;

		for (i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];

		for (i = size - 1; i >= 0; i--)
			semiSorted[--bucket[(arr[i] / significantDigit) % 10]] = arr[i];

		for (i = 0; i < size; i++)
			arr[i] = semiSorted[i];

		significantDigit *= 10;
	}
}
void quickSort (int* arr, int first, int last)
{
	int i, j, pivot;

	if (first < last)
	{
	pivot = first;
	i = first;
	j = last;
		while (i < j)
		{
			while (arr[i] <= arr[pivot] && i<last)
				i++;
			while (arr[j] > arr[pivot])
				j--;
			if (i < j)
			{
				swap(&arr[i], &arr[j]);
			}
		}
		swap(&arr[pivot], &arr[j]);
		quickSort(arr, first, j-1);
		quickSort(arr, j+1, last);
	}
}

void odd_evenSort(int * array, int len)
{
	int sort = 0;
	while(!sort)
	{
		sort = 1;
		for (int i = 1; i < len; i+=2)
		{
			if (array[i] > array [i+1])
			{
				swap (&array[i],  &array[i+1]);
				sort = 0;
			}
		}
		for (int j = 0; j < len; j+=2)
		{
			if (array[j] > array[j+1])
			{
				swap(&array[j], &array[j+1]);
				sort = 0;
			}
		}
	}
}

int main()
{
	int len;
	printf("Enter array size: ");
	scanf("%d", &len);
	while(getchar() != '\n');
	int array[len];
	arr_fill(array, len);

	char method_switcher='E';
	double start, end, time;

	while (method_switcher != '0')
	{
		method_switcher='E';

		printf("Choose sort method:\n");
		printf("1. Radix\n");
		printf("2. Odd-Even\n");
		printf("3. QuickSort\n");
		printf("r. Refill\n");
		printf("c. Minimize array leng & refill\n");
		printf("0. Exit\n");
		printf("-> ");

		method_switcher = getchar ();

		switch (method_switcher)
		{
		case 'r':
			arr_fill(array, len);
			printf("Done!\n");
			break;
		case 'c':
			printf("Enter array size: ");
			int len_old=len;
			scanf("%d", &len);
			if (len_old<len){
				printf("new len must be less than old!");
				break;
			}
			array[len];
		//	array=(int*) malloc (sizeof(int) * len);
			arr_fill(array, len);
			printf("Done!\n");
			break;
		
		case '1':
			start=clock();
			radixSort(array, len);
			end= clock(); 
			time = difftime(end, start) / 1000000; 
			printf("%0.10f\n", time);
			break;
		case '2':
			start=clock();
			odd_evenSort(array, len);
			end= clock(); 
			time = difftime(end, start) / 1000000; 
			printf("%0.10f\n", time);
			break;
		case '3':
			start=clock();
			quickSort(array, 0, len-1);
			end= clock(); 
			time = difftime(end, start) / 1000000; 
			printf("%0.10f\n", time);
			break;
		case '0':
			printf("Goodbye!\n");
			return 0;
		default:
			printf("Something went wrong\n");
			break;
		}

		while(getchar() != '\n');
	}
}

