#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>


int minval(int* A, int n)
{
	int currmin;
	int i;

	for (i = 0; i < n; i++)
		if (A[i] < currmin)
			currmin = A[i];

	return currmin;
}


void main(void)
{
	int A[5] = {12, 25, 3, 9, 8};
	int retVal = 0;

	retVal = minval(A, 5);

	
	printf("\nNajmanji element niza je: %d\n", retVal);

	return;
}
