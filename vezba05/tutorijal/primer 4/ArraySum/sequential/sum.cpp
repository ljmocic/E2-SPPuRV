#include <iostream>


unsigned int compute(unsigned int i)
{
	return i; // return a value computed from i
}


int main()
{
	unsigned int n = 1000000;
	unsigned int total = 0;

	// Compute the sum of integers  1..n
	for (unsigned int i = 1; i <= n; ++i)
	{
		total += compute(i);
	}
	// the sum of the first n integers
	// should be n * (n + 1) / 2
	unsigned int correct = (n * (n + 1)) / 2;

	if (total == correct)
	{
		std::cout << "Total (" << total << ") is correct" << std::endl;
	}
	else
	{
		std::cout << "Total (" << total << ") is WRONG, should be " << correct << std::endl;
	}

	return 0;
}
