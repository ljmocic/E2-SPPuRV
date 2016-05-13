#include "SyntaxAnalysis.h"
#include <iostream>

using namespace std;


SyntaxAnalysis::SyntaxAnalysis(LexicalAnalysis& lex) : lexicalAnalysis(lex), errorFound(false)
{
	tokenIterator = lexicalAnalysis.getTokenList().begin();
}


bool SyntaxAnalysis::Do()
{
	currentToken = getNextToken();

	// Call function for the starting non-terminal symbol
	q();

	return !errorFound;
}


void SyntaxAnalysis::printSyntaxError(Token& token)
{
	cout << "Syntax error! Token: " << token.getValue() << " unexpected" << endl;
}


void SyntaxAnalysis::eat(TokenType t)
{
	if (currentToken.getType() == t)
	{
		currentToken.printTokenInfo();
		currentToken = getNextToken();
	}
	else
	{
		printSyntaxError(currentToken);
	}
}


Token SyntaxAnalysis::getNextToken()
{
	if (tokenIterator == lexicalAnalysis.getTokenList().end())
		throw runtime_error("End of input file reached");
	return *tokenIterator++;
}


void SyntaxAnalysis::q()
{
	if (errorFound) return;

	if (currentToken.getType() == BEGIN) {
		eat(BEGIN);
		s();
		l();
	}
	else {
		errorFound = true;
		printSyntaxError(currentToken);
	}
}


void SyntaxAnalysis::s()
{
	if (errorFound) return;

	if (currentToken.getType() == IF) {
		eat(IF);
		e();
		if (currentToken.getType() == THEN) {
			eat(THEN);
			s();
			if (currentToken.getType() == ELSE) {
				eat(ELSE);
				s();
			}
			else {
				errorFound = true;
				printSyntaxError(currentToken);
			}
		}
		else {
			errorFound = true;
			printSyntaxError(currentToken);
		}
	}
	else if (currentToken.getType() == PRINT) {
		eat(PRINT);
		e();
	}
	else {
		errorFound = true;
		printSyntaxError(currentToken);
	}
}


void SyntaxAnalysis::l()
{
	if (errorFound) return;

	if (currentToken.getType() == END) {
		eat(END);
		cout << "Syntax OK" << endl;
	}
	else {
		s();
		l();
	}
}


void SyntaxAnalysis::e()
{
	if (errorFound) return;

	if (currentToken.getType() == ID) {
		eat(ID);
		if (currentToken.getType() == EQ) {
			eat(EQ);
			if (currentToken.getType() == NUM) {
				eat(NUM);
			}
			else {
				errorFound = true;
				printSyntaxError(currentToken);
			}
		}
		else {
			errorFound = true;
			printSyntaxError(currentToken);
		}
	}
	else {
		errorFound = true;
		printSyntaxError(currentToken);
	}
}
