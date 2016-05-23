#include "RegisterAllocation.h"

using namespace std;


static int counter = 8;

void initAvailableRegs()
{
	availableRegisters.push_back("$zero");
	availableRegisters.push_back("$at");
	availableRegisters.push_back("$v0");
	availableRegisters.push_back("$v1");
	availableRegisters.push_back("$a0");
	availableRegisters.push_back("$a1");
	availableRegisters.push_back("$a2");
	availableRegisters.push_back("$a3");
	availableRegisters.push_back("$t0");
	availableRegisters.push_back("$t1");
	availableRegisters.push_back("$t2");
	availableRegisters.push_back("$t3");
	availableRegisters.push_back("$t4");
	availableRegisters.push_back("$t5");
	availableRegisters.push_back("$t6");
	availableRegisters.push_back("$t7");
	availableRegisters.push_back("$s0");
	availableRegisters.push_back("$s1");
	availableRegisters.push_back("$s2");
	availableRegisters.push_back("$s3");
	availableRegisters.push_back("$s4");
	availableRegisters.push_back("$s5");
	availableRegisters.push_back("$s6");
	availableRegisters.push_back("$s7");
	availableRegisters.push_back("$t8");
	availableRegisters.push_back("$t9");
	availableRegisters.push_back("$k0");
	availableRegisters.push_back("$k1");
	availableRegisters.push_back("$gp");
	availableRegisters.push_back("$sp");
	availableRegisters.push_back("$fp");
	availableRegisters.push_back("$ra");
}


string getColor(Reg reg)
{
	return availableRegisters[(int)reg];
}


Reg getNewReg()
{
	return (Reg)(counter++);
}


Reg getZeroReg()
{
	return (Reg)0;
}
