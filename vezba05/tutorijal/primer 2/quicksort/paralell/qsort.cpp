#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <mmsystem.h>

#include <cilk/cilk.h>

#define MAXARRAY 10

void quicksort(int arr[], int low, int high);


int main(void)
{
	int array[MAXARRAY] = {0};
	int i = 0;

	/* load some random values into the array */
	for (i = 0; i < MAXARRAY; i++)
	{
		array[i] = rand() % 100;
	}

	/* print the original array */
	printf("Before quicksort: ");
	for (i = 0; i < MAXARRAY; i++)
	{
		printf(" %d ", array[i]);
	}
	printf("\n");

	DWORD startTime = timeGetTime();
	quicksort(array, 0, (MAXARRAY - 1));
	DWORD endTime = timeGetTime();

	/* print the `quicksorted' array */
	printf("After  quicksort: ");
	for (i = 0; i < MAXARRAY; i++)
	{
		printf(" %d ", array[i]);
	}
	printf("\n");

	printf("Run time: %d ms.\n", endTime - startTime);

	return 0;
}


/* sort everything inbetween `low' <-> `high' */
void quicksort(int arr[], int low, int high) 
{
	int i = low;
	int j = high;
	int y = 0;
	/* compare value */
	int z = arr[(low + high) / 2];

	/* partition */
	do
	{
		/* find member above ... */
		while (arr[i] < z)
		{
			i++;
		}

		/* find element below ... */
		while (arr[j] > z)
		{
			j--;
		}

		if (i <= j) 
		{
			/* swap two elements */
			y = arr[i];
			arr[i] = arr[j]; 
			arr[j] = y;
			i++; 
			j--;
		}
	} while (i <= j);

	/* recurse */
	if (low < j) 
	{
		cilk_spawn quicksort(arr, low, j);
	}

	if (i < high)
	{
		quicksort(arr, i, high);
	}

	cilk_sync;
}
