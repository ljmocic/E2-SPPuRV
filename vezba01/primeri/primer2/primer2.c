#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

#define NUMROWS 20
#define NUMCOLS 30


void main(void)
{
	int i, j;
	int pixels = 0;

	for (i = 0; i < NUMROWS; i++)
		for (j = 0; j < NUMCOLS; j++);
			pixels++;
	
	printf("\npixels = %d\n", pixels);

	return;
}
