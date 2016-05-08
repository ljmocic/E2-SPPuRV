#include "passI.h"

#include "assemblerLib.h"

using namespace std;


bool passI()
{
	DIRECTIVE_T directive;
	PARAM_STACK params;
	SECTION_T section = S_TEXT;
	SOURCE_LIST* sourceList;
	SOURCE_LIST::iterator sourceListIter;
	long memLocCounter;
	string sourceLine;
	long lineNum;
	string symbol;
	string msg;
	string executable;
	/******************************************************************************************
	* Add your variables here
	*******************************************************************************************/

	sourceList = getSourceList();   // get source code loaded in STL list, where each element is SOURCE_LINE, 
									// structure consisted of line number and source line string

	memLocCounter = 0; // memory locations counter start at 0

	for (sourceListIter = sourceList->begin(); sourceListIter != sourceList->end(); sourceListIter++)
	{
		// for each line from source code
		sourceLine = sourceListIter->sourceLine;	// get source line
		lineNum = sourceListIter->lineNumber;		// get line number

		getParams(params, sourceLine, lineNum);	// get params from current source line e.g.:
												// from line "add $t3, $t2, $0", extracted parametrs should be "$t3", "$t2", and "$0"
												// from line "value: .word 9", extracted parametrs should be "9"

		directive = getDirective(sourceLine, lineNum); // extract directive from source line (string following ".")

		if(getSymbol(symbol, sourceLine)){
			if(!symbolExists(symbol)) pushSymbol(symbol, memLocCounter, section);
			else addError(lineNum,sourceLine, "Simbol vec postoji!");	
		}

		if(getExecutable(executable, sourceLine, lineNum,false)) memLocCounter += 4;

		directive = getDirective(sourceLine, lineNum);

		switch (directive)
		{
		case D_NONE:
			// directive not found in current line
			break;

		case D_ORG:
			// if the directive is .org
			if (checkEnoughParams(lineNum, sourceLine, params, 1)) // check if the line with directive is correct
			{
				changeSectionAndLocation(params.top(), section, memLocCounter); // current section is updated due to .org directive (data/text section)
			}
			break;

		case D_WORD:
			// .word directive => extract the value as first parameter, convert it to number and add to literal table
			pushLiteral(memLocCounter, constConv(params.top()));
			memLocCounter += 4;
			// Extra question: what if .word directive can have more than one parameter?
			break;

		case D_SPACE:
			// .space directive => just check if it is followed by a number (single parameter)
			checkEnoughParams(lineNum, sourceLine, params, 1);

			memLocCounter += stoi(params.top());
			memLocCounter += ( 4 - stoi(params.top()) % 4 );

			break;

		case D_GLOBL:
			// .globl directive => get the symbol as first parameter, check if exists in global symbols table and add it to the table
			if (checkEnoughParams(lineNum, sourceLine, params, 1))
			{
				if (globalSymbolExists(params.top()))
				{
					msg = "Global symbol already exist: " + params.top();
					addError(lineNum, sourceLine, msg);
				}
				else
				{
					pushGlobalSymbol(params.top(), memLocCounter);
				}
			}
			break;

		case D_EXTERN:
			// .extern directive => get the symbol as first parameter, check if exists in extern symbols table and add it to the table
			if (checkEnoughParams(lineNum, sourceLine, params, 1))
			{
				if (externSymbolExists(params.top()))
				{
					msg = "Extern symbol already exist: " + params.top();
					addError(lineNum, sourceLine, msg);
				}
				else
				{
					pushExternSymbol(params.top(), memLocCounter);
				}
			}
			break;

		default:
			// error!
			break;
		}
	}

	return !errorsFound();
}
