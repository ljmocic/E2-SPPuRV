#include <iostream>

#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>


unsigned int compute(unsigned int i)
{
	return i; // return a value computed from i
}


int main()
{
	unsigned int n = 1000000;
	cilk::reducer_opadd<unsigned int> total;

	// Compute the sum of integers  1..n
	cilk_for (unsigned int i = 1; i <= n; ++i)
	{
		total += compute(i);
	}
	// the sum of the first n integers
	// should be n * (n + 1) / 2
	unsigned int correct = (n * (n + 1)) / 2;

	if (total.get_value() == correct)
	{
		std::cout << "Total (" << total.get_value() << ") is correct" << std::endl;
	else
	{
		std::cout << "Total (" << total.get_value() << ") is WRONG, should be " << correct << std::endl;
	}

	return 0;
}
