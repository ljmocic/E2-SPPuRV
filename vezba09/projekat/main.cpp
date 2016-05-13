#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"

#include <iostream>
#include <exception>

using namespace std;

void main()
{
	try
	{
		bool retVal = false;

		LexicalAnalysis lex;
		
		if (!lex.readInputFile(".\\program.txt"))
			throw runtime_error("\nException! Failed to open input file!\n");
		
		lex.initialize();

		retVal = lex.Do();

		if (retVal)
		{
			cout << "Lexical analysis finished successfully!" << endl;
		}
		else
		{
			cout << "Lexical analysis failed!" << endl;
			lex.printLexError();
		}

		SyntaxAnalysis syntax(lex);

		retVal = syntax.Do();

		if (retVal)
		{
			cout << "Syntax analysis finished successfully!" << endl;
		}
		else
		{
			cout << "Syntax analysis failed!" << endl;
		}
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
	}
}