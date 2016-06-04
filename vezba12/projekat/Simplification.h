#ifndef __SIMPLIFICATION_H__
#define __SIMPLIFICATION_H__

#include "Types.h"

#include <stack>

/**
 * Use this function to do simplification algorithm.
 * @param ig pointer to interference graph
 * @param degree numer of registers on hardware platform
 * @return simplification stack
 */
std::stack<Variable*>* doSimplification(InterferenceGraph* ig, int degree);

#endif
