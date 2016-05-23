#include "Instruction.h"
#include "RegisterAllocation.h"

#include <iostream>
#include <assert.h>

using namespace std;


void Instruction::printInstruction()
{
	cout << format() << endl;
}

std::string Instruction::format()
{
	Regs::iterator srci, dsti;
	char c;				// current character in asm string
	int i;				// current index of a characted in a string
	string formattedString = "";

	if (m_src != NULL)
		srci = m_src->begin();

	if (m_dest != NULL)
		dsti = m_dest->begin();

	i = 0;
	while (i != m_asmString.size())
	{
		c = m_asmString[i];
		
		if (c == '`')
		{
			switch (m_asmString[i+1])
			{
				case 's':
					formattedString += getColor(*srci);
					srci++;
					i++;
					break;

				case 'd':
					formattedString += getColor(*dsti);
					dsti++;
					i++;
					break;

				default:
					assert(0);
			}
		}
		else
		{
			formattedString += c;
		}
		i++;
	}

	return formattedString;
}
