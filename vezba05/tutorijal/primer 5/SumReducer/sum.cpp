#include <iostream>

#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>
#include <cilk/reducer.h>


template <typename Type>
class SumReducer
{
public:
	struct Monoid : cilk::monoid_base<Type>
	{
		// reduce function does summation
		static void reduce (Type* left, Type* right)
		{
			*left += *right;
		}
	};

	// Constructor: initialize view to the identity value; use Type class wrapper
	SumReducer() : m_imp(Type(0)) {}

	// get_value function by convention
	const Type& get_value() const { return m_imp.view(); }

	/* Two update operations */
	// Add 'v' to the value of this object.
	SumReducer& operator+=(const Type& v)
	{
		m_imp.view() += v;
		return *this;
	}

	// Increment the value of this object using pre-increment syntax.
	SumReducer& operator++()
	{
		m_imp.view() += 1;
		return *this;
	}
	/*************************/

private:
	// Hyperobject for serving views
	cilk::reducer<Monoid> m_imp;
};


unsigned int compute(unsigned int i)
{
	return i; // return a value computed from i
}


int main()
{
	unsigned int n = 1000000;
	//cilk::reducer_opadd<unsigned int> total; // cilk-defined reducer
	SumReducer<unsigned int> total; // self-defined reducer

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
	}
	else
	{
		std::cout << "Total (" << total.get_value() << ") is WRONG, should be " << correct << std::endl;
	}

	return 0;
}
