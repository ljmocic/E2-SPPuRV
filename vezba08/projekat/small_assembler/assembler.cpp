#include "assemblerLib.h"
#include "machineInstructionList.h"
#include "pseudoInstructionList.h"
#include "sourceLoader.h"
#include "passI.h"
#include "passII.h"

#include <iostream>

using namespace std;


void usage()
{
	cout << "Wrong number of input parameteres.\n\n";
	cout << "Set parameters In command line like a form:\n";
	cout << "assembler.exe <input_file> [output_file]\n";
}


void main(const int argc, const char* argv[])
{
	string input_file = "..\\fact.s";
	string output_file_bin = "..\\fact.o";
	string output_file_txt = "..\\fact.lst";

	cout << "\nSPPURV1 - V8\n\tMIPS Assembler\n\n\n";

	// check passed arguments
	if (argc > 3)
	{
		usage();
		return;
	}
	else if (argc == 2)
	{
		input_file.assign(argv[1]);
		string basic_name = input_file.substr(0, input_file.rfind("."));
		output_file_bin = basic_name + ".o";
		output_file_txt = basic_name + ".lst";
	}
	else if (argc == 3)
	{
		input_file.assign(argv[1]);
		output_file_bin.assign(argv[2]);
		output_file_txt.assign(argv[2]);
		output_file_bin = output_file_bin.substr(0, output_file_bin.rfind(".")) + ".o";
		output_file_txt = output_file_txt.substr(0, output_file_txt.rfind(".")) + ".lst";
	}

	// initialize all tables
	init(MACHINE_INSTRUCTIONS, MACHINE_INSTRUCTIONS_NO, PSEUDO_INSTRUCTIONS, PSEUDO_INSTRUCTIONS_NO);

	// load source to sourceList and replace pseudo instructions
	if (loadSourceRepPseudo(input_file))
	{
		// run first pass
		if (passI())
		{
			// run second pass
			if (passII())
			{
				cout << "\n---------------------------------";
				cout << "\nAssembling completed successfuly.\n\n";

				// write binary and text data to out file
				writeDataToFile(output_file_bin, output_file_txt);
			}
		}
	}

	//release taken memory resources
	clean();

	cout << endl;
	return;
}
