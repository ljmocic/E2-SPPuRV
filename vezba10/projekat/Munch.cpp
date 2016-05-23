#include "Munch.h"
#include "Instruction.h"
#include "RegisterAllocation.h"

#include <cstdarg>
#include <assert.h>
#include <string>
#include <sstream>

using namespace std;


static InstructionList selectedInstructions;

/*
* Use this function to translate integer value to string
*/
string toString(int value)
{
	string retVal = "";
	stringstream s;
	s << value;
	s >> retVal;
	return retVal;
}

/*
* Add the instruction to the list of selected instructions
*/
void emit(Instruction* instr)
{
	selectedInstructions.push_back(instr);
}


InstructionList& getInstructionList()
{
	return selectedInstructions;
}


void munchStm(Statement* statement)
{
	switch (statement->getType())
	{
		case Statement::MOVE_STM:
		{
			S_Move* moveStm = (S_Move*)statement;
			
			Expression* destExp = moveStm->getLeftExp();
			Expression* srcExp = moveStm->getRightExp();

			// if the destination expression (left expression) is memory access
			// then the statement represents storing to memory
			if (destExp->getType() == Expression::MEM_EXP)
			{
				// Here goes the code for sw instruction
			}
			else
			{
				assert(0);
			}
		}
		break;


		case Statement::SEQ_STM:
		{
			S_Seq* stmSeq = (S_Seq*)statement;

			Statement* left = stmSeq->getLeftStm();
			Statement* right = stmSeq->getRightStm();

			munchStm(left);
			munchStm(right);
		}
		break;


		case Statement::EXP_STM:
		{
			S_Exp* stmExp = (S_Exp*)statement;
			
			Expression* expression = stmExp->getExp();
			
			munchExp(expression);
		}
		break;


		default:
			assert(0);
	}
}


Reg munchExp(Expression* expression)
{
	switch (expression->getType())
	{
		case Expression::MEM_EXP:
		{
			// Here goes the code for lw instruction
			assert(0);
			return -1;
		}
		break;

		case Expression::BINOP_EXP:
		{
			E_Binop* binopExp = (E_Binop*)expression;
			
			if (binopExp->getOperType() == E_Binop::PLUS_OP)
			{
				Regs* sourceRegs = new Regs;
				Regs* destinationRegs = new Regs;

				Expression* binopLeftExp = binopExp->getLeftExp();
				Expression* binopRightExp = binopExp->getRightExp();

				if (binopRightExp->getType() == Expression::CONST_EXP)
				{
					E_Const* constExp = (E_Const*)binopRightExp;

					string instructionString = "addi `d,`s, " + toString(constExp->getValue());

					Reg sourceReg = munchExp(binopLeftExp);
					Reg dstReg = getNewReg();

					sourceRegs->push_back(sourceReg);
					destinationRegs->push_back(dstReg);

					Instruction* instr = new Instruction(instructionString, destinationRegs, sourceRegs);
					
					emit(instr);
					
					return dstReg;
				}
				else if (binopLeftExp->getType() == Expression::CONST_EXP)
				{
					E_Const* constExp = (E_Const*)binopLeftExp;

					string instructionString = "addi `d,`s, " + toString(constExp->getValue());

					Reg sourceReg = munchExp(binopRightExp);
					Reg dstReg = getNewReg();

					sourceRegs->push_back(sourceReg);
					destinationRegs->push_back(dstReg);

					Instruction* instr = new Instruction(instructionString, destinationRegs, sourceRegs);

					emit(instr);

					return dstReg;
				}
				else
				{

					string instructionString = "add `d,`s, `s";

					Reg sourceRegRight = munchExp(binopRightExp);
					sourceRegs->push_back(sourceRegRight);

					Reg sourceRegLeft = munchExp(binopLeftExp);
					sourceRegs->push_back(sourceRegLeft);

					Reg dstReg = getNewReg();
					destinationRegs->push_back(dstReg);

					Instruction* instr = new Instruction(instructionString, destinationRegs, sourceRegs);

					emit(instr);

					return dstReg;
				}

			}
			else if (binopExp->getOperType() == E_Binop::MINUS_OP)
			{
				Regs* sourceRegs = new Regs;
				Regs* destinationRegs = new Regs;

				Expression* binopLeftExp = binopExp->getLeftExp();
				Expression* binopRightExp = binopExp->getRightExp();

				if (binopRightExp->getType() == Expression::CONST_EXP)
				{
					E_Const* constExp = (E_Const*)binopRightExp;

					string instructionString = "sub `d,`s, " + toString(constExp->getValue());

					Reg sourceReg = munchExp(binopLeftExp);
					Reg dstReg = getNewReg();

					sourceRegs->push_back(sourceReg);
					destinationRegs->push_back(dstReg);

					Instruction* instr = new Instruction(instructionString, destinationRegs, sourceRegs);
					
					emit(instr);
					
					return dstReg;
				}
				else if (binopLeftExp->getType() == Expression::CONST_EXP)
				{
					E_Const* constExp = (E_Const*)binopLeftExp;

					string instructionString = "sub `d,`s, " + toString(constExp->getValue());

					Reg sourceReg = munchExp(binopRightExp);
					Reg dstReg = getNewReg();

					sourceRegs->push_back(sourceReg);
					destinationRegs->push_back(dstReg);

					Instruction* instr = new Instruction(instructionString, destinationRegs, sourceRegs);

					emit(instr);

					return dstReg;
				}
				else
				{

					string instructionString = "sub `d,`s, `s";

					Reg sourceRegRight = munchExp(binopRightExp);
					sourceRegs->push_back(sourceRegRight);

					Reg sourceRegLeft = munchExp(binopLeftExp);
					sourceRegs->push_back(sourceRegLeft);

					Reg dstReg = getNewReg();
					destinationRegs->push_back(dstReg);

					Instruction* instr = new Instruction(instructionString, destinationRegs, sourceRegs);

					emit(instr);

					return dstReg;
				}


			}
			else if (binopExp->getOperType() == E_Binop::DIV_OP)
			{
				Regs* sourceRegs = new Regs;
				Regs* destinationRegs = new Regs;

				Expression* binopLeftExp = binopExp->getLeftExp();
				Expression* binopRightExp = binopExp->getRightExp();


				string instructionString = "div `d,`s, `s";

				Reg sourceRegRight = munchExp(binopRightExp);
				sourceRegs->push_back(sourceRegRight);

				Reg sourceRegLeft = munchExp(binopLeftExp);
				sourceRegs->push_back(sourceRegLeft);

				Reg dstReg = getNewReg();
				destinationRegs->push_back(dstReg);

				Instruction* instr = new Instruction(instructionString, destinationRegs, sourceRegs);

				emit(instr);

				return dstReg;
			}
			else
			{
				assert(0);
				return -1;
			}
		}

		case Expression::REG_EXP:
		{
			E_Reg* regExp = (E_Reg*)expression;
			return regExp->getRegId();
		}

		case Expression::CONST_EXP:
		{
			E_Const* constExp = (E_Const*)expression;

			string instructionString = "li `d, " + toString(constExp->getValue());

			Regs* destinationRegs = new Regs;

			Reg dstReg = getNewReg();
			destinationRegs->push_back(dstReg);

			Instruction* instr = new Instruction(instructionString, destinationRegs, NULL);

			emit(instr);

			return dstReg;
		}

		case Expression::ESEQ_EXP:
		{
			E_Eseq* eseqExp = (E_Eseq*)expression;

			Expression* eseqLeft = eseqExp->getLeftExp();
			Statement* eseqRight = eseqExp->getRightStm();

			Reg dstReg = munchExp(eseqLeft);
			munchStm(eseqRight);

			return dstReg;
		}

		default:
			assert(0);
			return -1;
	}

	assert(0);
}
