#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
	int i;
	int n;

	if (argc < 2 || argc > 2)
	{
		printf("\nNiste uneli odgovarajuce argumente komandne linije!\n");
		exit(-1);
	}

	printf("\n1. Podrazumevani argument je naziv programa:\n%s\n", argv[0]);

	printf("\n2. Argument koji ste vi prosledili je n = %s\n\n", argv[1]);

	n = atoi(argv[1]);

	for (i = 0; i < n; i++)
		printf("%d. Hello World!\n", i + 1);

	printf("\n");
	return 0;
}
