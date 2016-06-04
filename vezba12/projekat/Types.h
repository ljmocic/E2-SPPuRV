#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdio.h>
#include <list>
#include "Constants.h"

using namespace std;

/**
 * Instruction type.
 */
typedef enum
{
	T_MOVE = 0,
	T_EQU,
	T_SUB,
	T_ADD,
	T_MUL,
	T_COND,
	T_RET,
	T_OTHER
} InstructionType;

/**
 * Reg names.
 */
typedef enum
{
	reg0 = 0,
	reg1,
	reg2,
	reg3
} Regs;

/**
 * This structure represent one variable in program code.
 */
struct Variable
{
	char name;              ///< variable name
	int pos;                ///< position in interference matrix
	Regs assigment;         ///< variable assigment to reg 

	/**
		* Variable constructor.
		*/
	Variable (char nName, int pPos)
	{
		name = nName;
		pos = pPos;
		assigment = (Regs)__UNDEFINE__;
	}
};


/**
 * This structure represent few variable from program code.
 */
typedef list<Variable*> Variables;


/**
 * This structure represent one instruction in program code.
 */
typedef struct InstructionStruct
{
	char pos;               ///< instruction (node) position in flow control graph

	InstructionType type;	///< instruction type

	Variable* dst;			///< instruction destination operand
	Variable* src1;		///< instruction first operand
	Variable* src2;		///< instruction second operand

	Variables use;			///< use variables in this instruction, get this from livness annalysis
	Variables def;			///< defined variables in this instruction, get this from livness annalysis

	Variables in;			///< live in variables for this instruction, get this from livness annalysis
	Variables out;			///< live out variables for this instruction, get this from livness annalysis

	list<InstructionStruct*> succ;		///< successive instructions in control flow graph
	list<InstructionStruct*> pred;		///< previous instructions in control flow graph

	/**
		* Instruction constructor.
		*/
	InstructionStruct(char pPos, InstructionType tType, Variable* dDst, Variable* sSrc1, Variable* sSrc2)
	{
		pos  = pPos;
		type = tType;
		dst  = dDst;
		src1 = sSrc1;
		src2 = sSrc2;
	}

	/**
		* Default construction.
		*/
	InstructionStruct()
	{
	}

} Instruction;


/**
 * This type represent few instruction in program code.
 */
typedef list<Instruction*> Instructions;


/**
 * This structure represent interference graph.
 */
typedef struct
{
	Variables* variables;	///< all variables from instructions
	char** values;			///< matrix value
	int size;				///< size of square matrix
} InterferenceGraph;

#endif
