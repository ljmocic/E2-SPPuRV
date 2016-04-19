#include <stdio.h>
#include <crtdbg.h>

#define SQUARE(n) (n*n)


void main(void)
{
	int a = 1;
	int b = 2;
	int val = 0;

	val = SQUARE(a + b);

	printf("\nval = %d\n", val);

	_ASSERTE(val == (a + b) * (a + b));

	return;
}
