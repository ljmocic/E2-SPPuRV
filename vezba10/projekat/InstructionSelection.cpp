#include "RegisterAllocation.h"
#include "Instruction.h"
#include "Tree.h"
#include "Munch.h"

#include <iostream>
#include <list>

using namespace std;


int main()
{
	Reg reg1 = (Reg)8;
	Reg reg2 = (Reg)9;
	Reg reg3 = (Reg)10;
	Reg zero = (Reg)0;
	
	initAvailableRegs();

	InstructionList instructionList;
	
	Statement* root;

	cout << "*******************************************************************" << endl;
	cout << "*******************************************************************" << endl;
	cout << "****************  INSTRUCTION SELECTION START...  *****************" << endl;
	cout << "*******************************************************************" << endl << endl;

	// Note: uncomment the desired tree for instruction selection

	// PLUS
	Statement* instruction11 = new S_Exp(new E_Binop(E_Binop::PLUS_OP, new E_Reg(reg1), new E_Const(20)));
	Statement* instruction12 = new S_Exp(new E_Binop(E_Binop::PLUS_OP, new E_Const(20), new E_Reg(reg1)));
	Statement* instruction13 = new S_Exp(new E_Binop(E_Binop::PLUS_OP, new E_Reg(reg1), new E_Reg(reg2)));
	root = new S_Seq(instruction11, new S_Seq(instruction12, instruction13));

	// MINUS
	Statement* instruction21 = new S_Exp(new E_Binop(E_Binop::MINUS_OP, new E_Reg(reg1), new E_Reg(reg2)));
	root = instruction21;

	// DIV
	Statement* instruction22 = new S_Exp(new E_Binop(E_Binop::DIV_OP, new E_Reg(reg1), new E_Reg(reg2)));
	root = instruction22;

	// LW
	//Statement* instruction31 = new S_Exp(new E_Mem(new E_Binop(E_Binop::PLUS_OP, new E_Const(15), new E_Reg(reg2))));
	//Statement* instruction32 = new S_Exp(new E_Mem(new E_Binop(E_Binop::PLUS_OP, new E_Reg(reg2), new E_Const(20))));
	//Statement* instruction33 = new S_Exp(new E_Mem(new E_Const(0x10010000)));
	//Statement* instruction34 = new S_Exp(new E_Mem(new E_Reg(reg2)));
	//root = new S_Seq(instruction31, new S_Seq(instruction32, new S_Seq(instruction33, instruction34)));

	// SW
	//Statement* instruction41 = new S_Move(
	//						new E_Mem(new E_Binop(E_Binop::PLUS_OP, new E_Const(0), new E_Const(0x10010000))),	// dst
	//						new E_Const(4)													// src
	//);
	//Statement* instruction42 = new S_Move(
	//						new E_Mem(new E_Binop(E_Binop::PLUS_OP, new E_Const(0), new E_Reg(reg2))),			// dst
	//						new E_Const(4)													// src
	//);
	//Statement* instruction43 = new S_Move(
	//						new E_Mem(new E_Binop(E_Binop::PLUS_OP, new E_Reg(reg2), new E_Const(0))),			// dst
	//						new E_Const(4)													// src
	//);
	//Statement* instruction44 = new S_Move(
	//						new E_Mem(new E_Const(0x10010000)),									// dst
	//						new E_Const(4)														// src
	//);
	//Statement* instruction45 = new S_Move(
	//						new E_Mem(new E_Reg(reg2)),										// dst
	//						new E_Const(4)													// src
	//);
	//root = new S_Seq(instruction41, new S_Seq(instruction42, new S_Seq(instruction43, new S_Seq(instruction44, instruction45))));

	// MOVE
	//Statement* instruction51 = new S_Move(
	//						new E_Mem(new E_Reg(reg2)),										// dst
	//						new E_Mem(new E_Reg(reg1))											// src
	//);
	//root = instruction51;
	
	// PROGRAM (from pdf)
	//Statement* program = new S_Move(
	//	new E_Mem(new E_Binop(E_Binop::PLUS_OP,
	//	new E_Mem(new E_Binop(E_Binop::PLUS_OP, new E_Const(20), new E_Reg(reg1))), 
	//	new E_Binop(E_Binop::MINUS_OP, new E_Const(15), new E_Reg(reg2))
	//	)
	//	),
	//	new E_Mem(new E_Binop(E_Binop::PLUS_OP, new E_Const(10), new E_Reg(reg3)))
	//	);
	//root = program;

	munchStm(root);
	
	instructionList = getInstructionList();

	for (auto it = instructionList.begin(); it != instructionList.end(); it++)
	{
		(*it)->printInstruction();
	}

	cout << "*******************************************************************" << endl;
	cout << "************  INSTRUCTION SELECTION END SUCESSFULL! ***************" << endl;
	cout << "********************** press any key ...***************************" << endl;
	cout << "*******************************************************************" << endl;

	getchar();
}
