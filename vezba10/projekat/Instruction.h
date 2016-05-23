#pragma once

#include "Tree.h"

#include <string>

/*
* Class used for intermediate representation of MIPS instructions.
* Each instruction has lists of destination and source registers and
* also its string representation.
*/
class Instruction
{

public:

	Instruction(std::string asmString, Regs* dest, Regs* src) :
	 m_asmString(asmString), m_dest(dest), m_src(src) {};

	/* Print instruction to the console */
	void printInstruction();

protected:

	std::string m_asmString;

	Regs* m_dest;

	Regs* m_src;

private:

	/* Format the assembly instruction string by adding sources and destinations
	* to specified locations in the asm string (replacing `s and `d)
	*/
	std::string format();
};