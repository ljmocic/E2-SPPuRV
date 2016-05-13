#pragma once

#include <string>
#define LIB_NAME "Lex"
#include "auto_link.h"
/**
* Possible states.
*/
typedef enum TokenType
{
	NO_TYPE,
	START,
	NO_FINITE,
	COMMENT,
	ID,
	NUM,
	REAL,
	IF,
	THEN,
	ELSE,
	PLUS,
	MINUS,
	EQ,
	SEMI,
	WHITE_SPACE,
	ERROR,
	END_OF_FILE,
	BEGIN,
	END,
	PRINT,
	MINUSMINUS,
	MINUSEQ,
	PLUSPLUS,
	PLUSEQ,
	EQEQ
};

#define LEFT_ALIGN				20
#define RIGHT_ALIGN				25

/**
 * Definition of start state.
 */
#define START_STATE				0

/**
 * Number of states in FSM
 */
#define D_NUM_STATE				40

/**
 * Number of supported characters
 */
#define D_NUM_OF_CHARACTERS		46

/**
 * Definition of closed states.
 */
#define D_NOTHING				(-2)

