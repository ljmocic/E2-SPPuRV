#pragma once

#include <list>
#include <vector>


/**
 * Use this type to describe register.
 */
typedef int Reg;

/**
 * Use this type to describe list of registers.
 */
typedef std::list<Reg> Regs;


/**
 * List of available MIPS registers.
 */
static std::vector<std::string> availableRegisters;

/**
 * This function populates the availableRegisters vector with MIPS registers
 */
void initAvailableRegs();

/**
 * Use this function to translate reg(number) to appropriate MIPS register.
 * This function hold table of MIPS registers(colors), reg is index (int) which index table.
 *
 */
std::string getColor(Reg reg);


/**
 * Make new register.
 * @return new reg
 */
Reg getNewReg();


/**
 * Use this function to get zero register. Zero register in MIPS always hold 0 value.
 * @return zero reg
 */
Reg getZeroReg();
