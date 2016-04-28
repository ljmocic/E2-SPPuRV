#include <stdio.h>
#include <stdlib.h>

#include <cilk/cilk.h>
#include <cilk/reducer_min.h>

#define MAX_ELEMENTS 10


template <typename T>
size_t IndexOfMin(T array[], size_t n)
{
	cilk::reducer_min_index<size_t, T> r;

	cilk_for (int i = 0; i < n; i++)
	{
		r.min_of(i, array[i]);
	}

	return r.get_index();
}


int main()
{
	int array[MAX_ELEMENTS] = {0};
	int i = 0;

	/* load some random values into the array */
	for (i = 0; i < MAX_ELEMENTS; i++)
	{
		array[i] = rand() % 100;
	}

	/* print the array */
	printf("Array: ");
	for (i = 0; i < MAX_ELEMENTS; i++)
	{
		printf(" %d ", array[i]);
	}
	printf("\n");

	int ind = IndexOfMin(array, MAX_ELEMENTS);

	printf("Index of minimal element is %d.\n", ind);
}
