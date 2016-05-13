#pragma once

#include "common.h"

#include <vector>
#include <string>

using namespace std;

class Token
{
private:
	/**
	 * Type of the token - as enumeration (defined in common.h)
	 */
	TokenType tokenType;
	
	/**
	 * Value of the token - as string
	 */
	string value;
	
	/**
	 * Helper function to get string representation of token type
	 */
	string tokenTypeToString(TokenType t);

public:

	Token(void);

	~Token(void);
	
	/**
	 * Returns token type
	 */
	TokenType getType();

	/**
	 * Sets token type
	 */
	void setType(TokenType t);
	
	/**
	 * Returns token value
	 */
	string getValue();
	
	/**
	 * Sets token value
	 */
	void setValue(string s);

	/**
	 * Creates a token
	 * [in] begin - start position in the program buffer - first character of the token
	 * [in] end - end position in the program buffer - end character of the token
	 * [in] program - program buffer
	 * [in] lastFiniteState - number of the last finite state, 
	 *		this is used to get the name of the state and store it as token type
	 */
	void makeToken(int begin, int end, std::vector<char>& program, int lastFiniteState);
	
	/**
	 * Creates an error token, storing the errnous content as token value
	 */
	void makeErrorToken(int pos, std::vector<char>& program);
	
	/**
	 * Creates end of file token when it is reached
	 */
	void makeEofToken();
	
	/**
	 * Prints token type and value
	 */
	void printTokenInfo();

	/**
	 * Prints token value
	 */
	void printTokenValue();
};

