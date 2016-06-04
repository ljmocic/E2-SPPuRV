#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include "Types.h"

/**
 * Use this function to print given variable.
 * @param variable pointer to variable for printing
 */
void printVariable(Variable* variable);

/**
 * Use this function to print all variables in list.
 * @param variables list of variables
 */
void printVariables(Variables variables);

/**
 * Use this function to print names of all variables in list.
 * @param variables list of variables
 */
void printVariablesNames(Variables variables);

/**
 * Use this function to check if variable exists in variables list.
 * @param variable pointer to variable which existance is meant to be checked
 * @param variables list of variables to check existance of variable
 * @return true if variable exists in variables list; false otherwise
 */
bool variableExists(Variable* variable, Variables variables);

#endif
