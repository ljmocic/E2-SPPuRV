#ifndef __INTERFERENCE_GRAPH__
#define __INTERFERENCE_GRAPH__

#include "Types.h"


/**
 * Use this function to make interference graph from instructions list.
 * @param instructions pointer to instruction list
 * @return pointer to interference graph
 */
InterferenceGraph* doInterferenceGraph(Instructions* instructions);


/**
 * Use this function to free all interference graph resources.
 * @param ig pointer to InterferenceGraph structure which values are going to be free
 */
void freeInterferenceGraph(InterferenceGraph* ig);


/**
 * Use this function to print interference graph values in console.
 * @param ig pointer to interference graph structure which value will be printed in console. 
 */
void printInterferenceGraph(InterferenceGraph* ig);


#endif
