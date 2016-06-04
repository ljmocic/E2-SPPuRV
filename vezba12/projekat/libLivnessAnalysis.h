#ifndef __START__H__
#define __START__H__

#include "Types.h"


/**
 * Use this function to do livness analysis. 
 * @param debug use this to print debug information from livness analysis.Use __DEBUG__ for argument to print debug information.
 * @return list of instructions with livness analysis information
 */
Instructions* doLivenessAnalysis(int debug);


#endif
