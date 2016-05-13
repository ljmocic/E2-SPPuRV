#pragma once

#include "LexicalAnalysis.h"
#include "Token.h"

class SyntaxAnalysis
{

private:
	
	/**
	 * Reference to lexical analysis module
	 */
	LexicalAnalysis& lexicalAnalysis;

	/**
	 * Iterator to the token list which represents the output of the lexical analysis
	 */
	TokenList::iterator tokenIterator;

	/**
	 * Current token that is being analyzed
	 */
	Token currentToken;

	/**
	 * Nonterminal Q
	 */
	void q();

	/**
	 * Nonterminal S
	 */
	void s();

	/**
	 * Nonterminal L
	 */
	void l();

	/**
	 * Nonterminal E
	 */
	void e();

	/**
	 * Syntax error indicator
	 */
	bool errorFound;

public:

	/**
	 * Constructor
	 */
	SyntaxAnalysis(LexicalAnalysis& lex);

	/**
	 * Method which performs lexical analysis
	 */
	bool Do();

	/**
	 * Prints the token that caused the syntax error
	 */
	void printSyntaxError(Token& token);

	/**
	 * Eats the current token if its type is "t"
	 * otherwise reports syntax error
	 *
	 * param[in] - t - the expected token type
	 */
	void eat(TokenType t);

	/**
	 * Returns the next token from the token list
	 */
	Token getNextToken();
};

