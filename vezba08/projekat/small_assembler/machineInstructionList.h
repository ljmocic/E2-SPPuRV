#ifndef __MACHINEINSTRUCTIONLIST_H__
#define __MACHINEINSTRUCTIONLIST_H__

#include "assemblerLib.h"

/**
 * The number of defined machine instructions.
 */
#define MACHINE_INSTRUCTIONS_NO 47

/**
 * The array of defined machine instructions.
 */
const tableOpCode_Pair MACHINE_INSTRUCTIONS[MACHINE_INSTRUCTIONS_NO] =
{
	//               symbol             symbol      optype format opcode funct  parNum
	tableOpCode_Pair("add"     , OPCODE("add"     , MACHINE, R   , 0x0  , 0x20 , 3 )),
	tableOpCode_Pair("addi"    , OPCODE("addi"    , MACHINE, I   , 0x8  , 0x0  , 3 )),
	tableOpCode_Pair("addiu"   , OPCODE("addiu"   , MACHINE, I   , 0x9  , 0x0  , 3 )),
	tableOpCode_Pair("addu"    , OPCODE("addu"    , MACHINE, R   , 0x0  , 0x21 , 3 )),
	tableOpCode_Pair("and"     , OPCODE("and"     , MACHINE, R   , 0x0  , 0x24 , 3 )),
	tableOpCode_Pair("andi"    , OPCODE("andi"    , MACHINE, I   , 0xC  , 0x0  , 3 )),
	tableOpCode_Pair("beq"     , OPCODE("beq"     , MACHINE, B   , 0x4  , 0x0  , 3 )),
	tableOpCode_Pair("bgez"    , OPCODE("bgez"    , MACHINE, BZ  , 0x1  , 0x1  , 2 )),
	tableOpCode_Pair("bgezal"  , OPCODE("bgezal"  , MACHINE, BZ  , 0x1  , 0x11 , 2 )),
	tableOpCode_Pair("bgtz"    , OPCODE("bgtz"    , MACHINE, BZ  , 0x7  , 0x0  , 2 )),
	tableOpCode_Pair("blez"    , OPCODE("blez"    , MACHINE, BZ  , 0x6  , 0x0  , 2 )),
	tableOpCode_Pair("bltz"    , OPCODE("bltz"    , MACHINE, BZ  , 0x1  , 0x0  , 2 )),
	tableOpCode_Pair("bltzal"  , OPCODE("bltzal"  , MACHINE, BZ  , 0x1  , 0x10 , 2 )),
	tableOpCode_Pair("bne"     , OPCODE("bne"     , MACHINE, B   , 0x5  , 0x0  , 3 )),
	tableOpCode_Pair("div"     , OPCODE("div"     , MACHINE, MD  , 0x0  , 0x1A , 2 )),
	tableOpCode_Pair("divu"    , OPCODE("divu"    , MACHINE, MD  , 0x0  , 0x1B , 2 )),
	tableOpCode_Pair("j"       , OPCODE("j"       , MACHINE, J   , 0x2  , 0x0  , 1 )),
	tableOpCode_Pair("jal"     , OPCODE("jal"     , MACHINE, J   , 0x3  , 0x0  , 1 )),
	tableOpCode_Pair("jr"      , OPCODE("jr"      , MACHINE, JR  , 0x0  , 0x8  , 1 )),
	tableOpCode_Pair("lb"      , OPCODE("lb"      , MACHINE, I   , 0x20 , 0x0  , 3 )),
	tableOpCode_Pair("lui"     , OPCODE("lui"     , MACHINE, LUI , 0xF  , 0x0  , 2 )),
	tableOpCode_Pair("lw"      , OPCODE("lw"      , MACHINE, I   , 0x23 , 0x0  , 3 )),
	tableOpCode_Pair("mfhi"    , OPCODE("mfhi"    , MACHINE, MF  , 0x0  , 0x10 , 1 )),
	tableOpCode_Pair("mflo"    , OPCODE("mflo"    , MACHINE, MF  , 0x0  , 0x12 , 1 )),
	tableOpCode_Pair("mult"    , OPCODE("mult"    , MACHINE, MD  , 0x0  , 0x18 , 2 )),
	tableOpCode_Pair("multu"   , OPCODE("multu"   , MACHINE, MD  , 0x0  , 0x19 , 2 )),
	tableOpCode_Pair("nop"     , OPCODE("nop"     , MACHINE, N   , 0x0  , 0x0  , 0 )),
	tableOpCode_Pair("nor"     , OPCODE("nor"     , MACHINE, R   , 0x0  , 0x27 , 3 )),
	tableOpCode_Pair("or"      , OPCODE("or"      , MACHINE, R   , 0x0  , 0x25 , 3 )),
	tableOpCode_Pair("ori"     , OPCODE("ori"     , MACHINE, I   , 0xD  , 0x0  , 3 )),
	tableOpCode_Pair("sb"      , OPCODE("sb"      , MACHINE, I   , 0x28 , 0x0  , 3 )),
	tableOpCode_Pair("sll"     , OPCODE("sll"     , MACHINE, S   , 0x0  , 0x0  , 3 )),
	tableOpCode_Pair("sllv"    , OPCODE("sllv"    , MACHINE, SV  , 0x0  , 0x4  , 3 )),
	tableOpCode_Pair("slt"     , OPCODE("slt"     , MACHINE, R   , 0x0  , 0x2A , 3 )),
	tableOpCode_Pair("slti"    , OPCODE("slti"    , MACHINE, I   , 0xA  , 0x0  , 3 )),
	tableOpCode_Pair("sltiu"   , OPCODE("sltiu"   , MACHINE, I   , 0xB  , 0x0  , 3 )),
	tableOpCode_Pair("sltu"    , OPCODE("sltu"    , MACHINE, R   , 0x0  , 0x2B , 3 )),
	tableOpCode_Pair("sra"     , OPCODE("sra"     , MACHINE, S   , 0x0  , 0x3  , 3 )),
	tableOpCode_Pair("srav"    , OPCODE("srav"    , MACHINE, SV  , 0x0  , 0x7  , 3 )),
	tableOpCode_Pair("srl"     , OPCODE("srl"     , MACHINE, S   , 0x0  , 0x2  , 3 )),
	tableOpCode_Pair("srlv"    , OPCODE("srlv"    , MACHINE, SV  , 0x0  , 0x6  , 3 )),
	tableOpCode_Pair("sub"     , OPCODE("sub"     , MACHINE, R   , 0x0  , 0x22 , 3 )),
	tableOpCode_Pair("subu"    , OPCODE("subu"    , MACHINE, R   , 0x0  , 0x23 , 3 )),
	tableOpCode_Pair("sw"      , OPCODE("sw"      , MACHINE, I   , 0x2B , 0x0  , 3 )),
	tableOpCode_Pair("syscall" , OPCODE("syscall" , MACHINE, SC  , 0x0  , 0x09 , 0 )),
	tableOpCode_Pair("xor"     , OPCODE("xor"     , MACHINE, R   , 0x0  , 0x26 , 3 )),
	tableOpCode_Pair("xori"    , OPCODE("xori"    , MACHINE, I   , 0xE  , 0x0  , 3 ))
};

#endif  // __MACHINEINSTRUCTIONLIST_H__
