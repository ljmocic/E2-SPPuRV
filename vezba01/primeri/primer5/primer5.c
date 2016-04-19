#include <stdio.h>


void print(int val)
{
	printf("\t%d\n", val);
}


void main(void)
{
	int i = 0;

	for (i = 1; i <= 4; i++)
	{
		switch (i)
		{
			case 1:
				print(1);
				break;
			case 2:
				print(2);
				break;
			case 3:
				print(1);
				break;
			case 4:
				print(4);
				break;
			default:
				break;
		}
	}

	return;
}
