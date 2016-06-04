#ifndef __TYPES_H__
#define __TYPES_H__

#include "Constants.h"

#include <list>


/**
 * Instruction type.
 */
typedef enum
{
	move = 0,
	equ,
	sub,
	add,
	mul,
	cond,
	ret,
	others
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
	char name;			///< variable name
	int pos;			///< position in interference matrix
	Regs assignment;	///< variable assignment to reg

	/**
	 * Variable constructor.
	 */
	Variable (char nName, int pPos)
	{
		name = nName;
		pos = pPos;
		assignment = (Regs)__UNDEFINE__;
	}
};

/**
 * This structure represent few variable from program code.
 */
typedef std::list<Variable*> Variables;

/**
 * This structure represent one instruction in program code.
 */
typedef struct InstructionStruct
{
	char pos;				///< instruction (node) position in flow control graph

	InstructionType type;	///< instruction type

	Variables use;			///< use variables in this instruction
	Variables def;			///< defined variables in this instruction

	Variables in;			///< live in variables for this instruction, get this from livness annalysis
	Variables out;			///< live out variables for this instruction, get this from livness annalysis

	std::list<InstructionStruct*> succ;		///< successive instructions in control flow graph
	std::list<InstructionStruct*> pred;		///< previous instructions in control flow graph

	/**
	 * Instruction constructor.
	 */
	InstructionStruct(char pPos, InstructionType tType, Variable* dDst, Variable* sSrc1, Variable* sSrc2)
	{
		pos  = pPos;
		type = tType;

		if (dDst != NULL)
			def.push_back(dDst);

		if (sSrc1 != NULL)
			use.push_back(sSrc1);

		if (sSrc2 != NULL)
			use.push_back(sSrc2);
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
typedef std::list<Instruction*> Instructions;

#endif
