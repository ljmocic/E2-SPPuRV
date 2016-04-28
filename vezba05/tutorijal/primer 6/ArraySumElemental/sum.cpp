#include <stdio.h>
#include <cilk/cilk.h>

#define MAX_EL 100

//declaring the function body
__declspec (vector) double ef_add (double x, double y)
{
	return x + y;
}


int main()
{
	int a1[MAX_EL] = {0};
	int a2[MAX_EL] = {0};
	int a3[MAX_EL] = {0};
	int b[MAX_EL] = {0};
	int c[MAX_EL] = {0};

	b[:] = 1;
	c[:] = 2;

	int n = MAX_EL/2;
	int s = 2; // every stride

	//invoking the function using array notations
	a1[:] = ef_add(b[:], c[:]);    //operates on the whole extent of the arrays a,b,c
	a2[0:n:s] = ef_add(b[0:n:s], c[0:n:s]); //use the full array notation construct to also specify n as an extend and s as a stride

	//Use the cilk_for construct to invoke the elemental function in a data parallel context
	cilk_for (int j = 0; j < MAX_EL; ++j)
	{
		a3[j] = ef_add(b[j],c[j]);
	}

	// if any element not equal to 3, print it out
	for (int j = 0; j < MAX_EL; ++j)
	{
		if (a1[j] != 3)
		{
			printf("a1(%d) = %d\n", j, a1[j]);
		}
		if (a2[j] != 3)
		{
			printf("a2(%d) = %d\n", j, a2[j]);
		}
		if (a3[j] != 3)
		{
			printf("a3(%d) = %d\n", j, a3[j]);
		}
	}
	printf("DONE.\n");

	return 0;
}
