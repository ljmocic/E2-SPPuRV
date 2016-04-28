#include <stdio.h>
#include <stdlib.h>

#include <windows.h> // needed for timeGetTime()
#include <mmsystem.h> // needed for timeGetTime()


int fib(int n)
{
	if (n < 2)
		return n;

	int x = fib(n - 1);
	int y = fib(n - 2);

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
