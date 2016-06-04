#include "LivenessAnalysis.h"

void livenessAnalysis(Instructions instructions){

	for (Instructions::reverse_iterator i = instructions.rbegin(); i != instructions.rend(); i++){
		
		(*i)->out.clear();

		for (Instructions::iterator j = (*i)->succ.begin(); j != (*i)->succ.end(); j++)
			for (Variables::iterator k = (*j)->in.begin(); k != (*j)->in.end(); k++)
				(*i)->out.push_back((*k));
			
		(*i)->out.sort();
		(*i)->out.unique();

		(*i)->in = (*i)->use;
		for (Variables::iterator j = (*i)->out.begin(); j != (*i)->out.end(); j++)
			if (!variableExists(*j, (*i)->def)) (*i)->in.push_back((*j));

		(*i)->in.sort();
		(*i)->in.unique();

	}
}
