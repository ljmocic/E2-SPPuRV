#include "ResourceAllocation.h"
#include "InterferenceGraph.h"
#include "Constants.h"
#include "Instruction.h"


bool doResourceAllocation(stack<Variable*>* simplificationStack, InterferenceGraph* ig){

	list<Regs> regs;
	list<Variable*> colored;

	for(int i = 0; i < __REG_NUMBER__; i++) regs.push_back((Regs)i);

	while(!simplificationStack->empty()){
		
		Variable* temp = simplificationStack->top();

		bool interference = false;

		for(auto it = colored.begin(); it != colored.end(); it++) 
			if((*ig).values[temp->pos][(*it)->pos] == __INTERFERENCE__) interference = true;


		if(!interference) temp->assigment = regs.front();
		else {
			if(!regs.empty()){
				regs.pop_front();
				temp->assigment = regs.front();
			}
			else return false;
		}

		colored.push_back(temp);
		simplificationStack->pop();
	}

	return true;
}


Instructions* removeMove(Instructions* instrs){
	
	for (auto it = instrs->begin(); it != instrs->end(); it++) {
		if ( (*it)->type == T_MOVE ) {
			if ( (*it)->src1->assigment == (*it)->dst->assigment && (*it)->src2 == NULL) {
				instrs->remove(*it);
				break;
			}
		}
	}
		
	return instrs;
}