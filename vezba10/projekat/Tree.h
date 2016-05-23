#pragma once

#include "RegisterAllocation.h"

#include <cstddef>

/**
 * Class describing statement in IR tree.
 */
class Statement
{

public:

	/* statement types:
	- expression statement
	- move statement
	- seq statement (sequence of statements)
	*/
	enum StatementType
	{
		EXP_STM,
		MOVE_STM,
		SEQ_STM,
		NO_TYPE_STM
	};

	Statement() : m_type(NO_TYPE_STM) {}

	Statement(StatementType stmType) : m_type(stmType) {}

	void setType(StatementType stmType) { m_type = stmType; }

	StatementType getType() { return m_type; }

protected:

	StatementType m_type;
};


/**
 * Class describing expression in IR tree.
 */
class Expression
{

public:

	/* expression types:
	- binary operation expression
	- eseq expression (sequence of expression and statement)
	- memory expression (memory access)
	- reg expression (expression describing register)
	- const expression
	*/
	enum ExpressionType
	{
		BINOP_EXP,
		ESEQ_EXP,
		MEM_EXP,
		REG_EXP,
		CONST_EXP,
		NO_TYPE_EXP
	};

	Expression() : m_type(NO_TYPE_EXP) {}

	Expression(ExpressionType expType) : m_type(expType) {}

	void setType(ExpressionType expType) { m_type = expType; }

	ExpressionType getType() { return m_type; }

protected:

	ExpressionType m_type;
};


/**
 * Class describing expression statement in IR tree.
 */
class S_Exp : public Statement
{

public:

	S_Exp() : Statement(EXP_STM), m_exp(NULL) {}

	S_Exp(Expression* exp) : Statement(EXP_STM), m_exp(exp) {}

	Expression* getExp() { return m_exp; }

protected:

	Expression* m_exp;
};


/**
 * Class describing move statement in IR tree.
 */
class S_Move : public Statement
{

public:

	S_Move() : Statement(MOVE_STM), m_left(NULL), m_right(NULL) {}

	S_Move(Expression* left, Expression* right) : 
		Statement(MOVE_STM), m_left(left), m_right(right) {}

	Expression* getLeftExp() { return m_left; }

	Expression* getRightExp() { return m_right; }

protected:

	Expression* m_left;

	Expression* m_right;
};


/**
 * Class describing sequence of statements in IR tree.
 */
class S_Seq : public Statement
{

public:

	S_Seq() : Statement(SEQ_STM), m_left(NULL), m_right(NULL) {}

	S_Seq(Statement* left, Statement* right) : 
		Statement(SEQ_STM), m_left(left), m_right(right) {}

	Statement* getLeftStm() { return m_left; }

	Statement* getRightStm() { return m_right; }

protected:

	Statement* m_left;

	Statement* m_right;
};


/**
 * Class describing binary operation expressions in IR tree.
 */
class E_Binop : public Expression
{

public:

	enum BinopType
	{
		PLUS_OP,
		MINUS_OP,
		DIV_OP,
		NO_TYPE_OP
	};

	E_Binop() : Expression(BINOP_EXP), m_operType(NO_TYPE_OP),
		m_left(NULL), m_right(NULL) {}

	E_Binop(BinopType operType, Expression* left, Expression* right) : 
		Expression(BINOP_EXP), m_operType(operType), m_left(left), m_right(right) {}

	BinopType getOperType() { return m_operType; }

	Expression* getLeftExp() { return m_left; }

	Expression* getRightExp() { return m_right; }

protected:

	BinopType m_operType;

	Expression* m_left;

	Expression* m_right;
};


/**
 * Class describing sequence of expression and statement expressions in IR tree.
 */
class E_Eseq : public Expression
{

public:

	E_Eseq() : Expression(ESEQ_EXP), m_left(NULL), m_right(NULL) {}

	E_Eseq(Expression* left, Statement* right) : 
		Expression(ESEQ_EXP), m_left(left), m_right(right) {}

	Expression* getLeftExp() { return m_left; }

	Statement* getRightStm() { return m_right; }

protected:

	Expression* m_left;

	Statement* m_right;
};


/**
 * Class describing memory access expressions in IR tree.
 */
class E_Mem : public Expression
{

public:

	E_Mem() : Expression(MEM_EXP), m_exp(NULL) {}

	E_Mem(Expression* exp) : Expression(MEM_EXP), m_exp(exp) {}

	Expression* getExp() { return m_exp; }

protected:

	Expression* m_exp;
};


/**
 * Class describing register expressions in IR tree.
 */
class E_Reg : public Expression
{

public:
	E_Reg() : Expression(REG_EXP), m_regId(-1) {}

	E_Reg(Reg regId) : Expression(REG_EXP), m_regId(regId) {}

	Reg getRegId() { return m_regId; }

protected:

	Reg m_regId;
};


/**
 * Class describing constant expressions in IR tree.
 */
class E_Const : public Expression
{

public:
	E_Const() : Expression(CONST_EXP), m_value(0) {}

	E_Const(int val) : Expression(CONST_EXP), m_value(val) {}

	int getValue() { return m_value; }

protected:

	int m_value;
};
