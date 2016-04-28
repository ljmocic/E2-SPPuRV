#include <stdio.h>
#include <stdlib.h>

#include <windows.h> // needed for timeGetTime()
#include <mmsystem.h> // needed for timeGetTime()

#include <cilk/cilk.h>


int fib(int n)
{
	if (n < 2)
		return n;

	int x = cilk_spawn fib(n - 1);
	int y = fib(n - 2);
	cilk_sync;

	return x + y;
}


int main(int argc, char* argv[])
{
	int n = atoi(argv[1]);

	DWORD startTime = timeGetTime();
	int result = fib(n);
	DWORD endTime = timeGetTime();

	printf("Fibonacci of %d is %d.\n", n, result);
	printf("Run time: %d ms.\n", endTime - startTime);

	return 0;
}
