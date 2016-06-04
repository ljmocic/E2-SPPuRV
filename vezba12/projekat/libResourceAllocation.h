#ifndef __RESOURCE_ALLOCATION_LIB_H__
#define __RESOURCE_ALLOCATION_LIB_H__

#include "InterferenceGraph.h"

/**
 * Use this function to check resource allocation process. 
 * This function goes thought variables list and interference graph
 * and check does variables which have interference in interference graph containe diferent regs. 
 * @param ig pointer to interference graph
 * @return true if resource allocation is done with no error, else false
 */
bool checkResourceAllocation(InterferenceGraph* ig);

#endif
