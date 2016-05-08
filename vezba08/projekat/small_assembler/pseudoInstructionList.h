#ifndef __PSEUDOINSTRUCTIONLIST_H__
#define __PSEUDOINSTRUCTIONLIST_H__

#include "assemblerLib.h"

/**
 * The number of defined pseudo instructions
 */
#define PSEUDO_INSTRUCTIONS_NO 13

/**
 * The array of defined pseudo instructions
 */
const tableOpCode_Pair PSEUDO_INSTRUCTIONS[PSEUDO_INSTRUCTIONS_NO] =
{
	//               symbol           replace instructions                           optype                 parNum
	tableOpCode_Pair("text"  , OPCODE(".org $SECTION_TEXT"                          , PSEUDO , I_NONE , 0 , 0 , 0 )),
	tableOpCode_Pair("data"  , OPCODE(".org $SECTION_DATA"                          , PSEUDO , I_NONE , 0 , 0 , 0 )),
	tableOpCode_Pair("move"  , OPCODE("or %1,%2,$0"                                 , PSEUDO , I_NONE , 0 , 0 , 2 )),    // move $1, $2 -> or $1, $2, $0
	tableOpCode_Pair("beqz"  , OPCODE("beq %1,$0,%2"                                , PSEUDO , I_NONE , 0 , 0 , 2 )),    // beqz $1, loop -> beq $1, $0, loop
	tableOpCode_Pair("bneqz" , OPCODE("bne %1,$0,%2"                                , PSEUDO , I_NONE , 0 , 0 , 2 )),    // bneqz $1, loop -> bneq $1, $0, loop
	tableOpCode_Pair("li"    , OPCODE("lui %1,HI(%2)\nori %1,%1,LO(%2)"             , PSEUDO , I_NONE , 0 , 0 , 2 )),    // li $1, 0x80000000 -> lui $1,0x8000\nori $1,0x0000
	tableOpCode_Pair("la"    , OPCODE("lui %1,HI(ADDR(%2))\nori %1,%1,LO(ADDR(%2))" , PSEUDO , I_NONE , 0 , 0 , 2 )),    // li $1, $dataLabels{%2} -> lui $1,0x8000\n ori $1,$1,$dataLabels{%2}
	tableOpCode_Pair("neg"   , OPCODE("nor %1,%2,$0\naddi %1,%1,1"                  , PSEUDO , I_NONE , 0 , 0 , 2 )),    // neg $1, $2   -> nor $1, $2, $0 , addi $1, $1, 1
	tableOpCode_Pair("nori"  , OPCODE("ori $1,$0,%3\nnor %1,%2,$1"                  , PSEUDO , I_NONE , 0 , 0 , 3 )),    // not $1, $2   -> nor $1, $2, $0
	tableOpCode_Pair("not"   , OPCODE("nor %1,%2,$0"                                , PSEUDO , I_NONE , 0 , 0 , 2 )),    // not $1, $2   -> nor $1, $2, $0
	tableOpCode_Pair("bal"   , OPCODE("bgezal $0,%1"                                , PSEUDO , I_NONE , 0 , 0 , 1 )),
	tableOpCode_Pair("b"     , OPCODE("beq $0,$0,%1"                                , PSEUDO , I_NONE , 0 , 0 , 1 )),
	tableOpCode_Pair("mul"   , OPCODE("mult %2,%3\nmflo %1"                         , PSEUDO , I_NONE , 0 , 0 , 3 ))
};

#endif  // __PSEUDOINSTRUCTIONLIST_H__
