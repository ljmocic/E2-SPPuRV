#pragma once

#include "Tree.h"
#include "Instruction.h"

/**
 * Use this type to describe list of instruction pointers.
 */
typedef std::list<Instruction*> InstructionList;

/**
 * Use this function Munch algorithm to translate IR statement to MIPS instructions.
 * @param statement - IR statement which will be translated to MIPS instructions
 */
void munchStm(Statement* statement);


/**
 * Use this function Munch algorithm to translate IR expression to MIPS instructions.
 * @param expression - IR expression which will be translated to MIPS instructions
 * @return every expression returns value in a register
 */
Reg munchExp(Expression* expression);


/**
 * Use this function to get instruction list built in Munch algorithm
 * @return instruction list from Munch algorithm
 */
InstructionList& getInstructionList();

