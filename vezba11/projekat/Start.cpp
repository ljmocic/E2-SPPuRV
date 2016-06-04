#include "Types.h"
#include "Constants.h"
#include "Instruction.h"
#include "Test.h"
#include "LivenessAnalysis.h"
#define LIB_NAME "LivenessAnalysis"
#include "auto_link.h"

#include <iostream>

using namespace std;


void main(int argc, char argv[])
{
	Instructions& instructions = getInstructions();
	Variables& variables = getVariables();


	// 1) build instruction list (some nodes from pseudo code)
	makeExample();
	cout << "Variables list:" << endl;
	printVariables(variables);
	cout << endl << endl;
	cout << endl << "Instruction list (flow control graph):" << endl;
	printInstructions(instructions);
	cout << endl << endl;


	// 2) do liveness analysis of variables using control flow graph
	livenessAnalysis(instructions);
	cout << endl << "Instruction list after LIVENESS ANALYSIS:" << endl;
	printInstructions(instructions);
	cout << endl << endl;


	cout << "END" << endl;

	getchar();

	return;
}
