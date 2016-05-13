#pragma once

#include <map>
#include <string>

#include "common.h"

typedef std::map<int, std::map<char,int>> STATE_MACHINE;

class FiniteStateMachine
{
private:
	/**
	 * State machine map, containing possible FSM states and transition matrix as an inner map
	 *		map<StateNumber, map<TransitionCharacter, NextStateNumber>>
	 * map1 key:		state number
	 * map1 value:	map2 key -> next letter in the stream, identifies the transition to the next state
	 *				map2 value -> next state number
	 */
	STATE_MACHINE stateMachine;

	/**
	 * Table containing all possible states for the FSM
	 */
	static const TokenType stateToTokenTable[D_NUM_STATE];

	/**
	 * Array contaning supported characters
	 */
	static const char supportedCharacters[D_NUM_OF_CHARACTERS];

	/**
	 * State transition matrix:
	 *	Rows represent current state and columns the next state
	 *	Transition characters (symbols) for each transition are defined with supportedCharacters array
	 *	Since there are more than 10 states we introduced A-M states which are defined as numbers 
	 *	from 10-22 for easier understanding of the matrix
	 *
	 *	Example:
	 *		row [1] -> state 1 will change to state D if the next character is 0..9
	 */
	static const int stateMatrix[D_NUM_STATE][D_NUM_OF_CHARACTERS];

public:
	/**
	 * Returns the next state number, based on current state and transition letter
	 */
	int getNextState(int currentState, char transitionLetter);

	/**
	 * Call this function to initialize FSM.
	 * This function must be called before getNextLexToken function.
	 */
	void initStateMachine();

	/**
	 * Get token type from the number of the state
	 */
	static TokenType getTokenType(int stateNumber);
};



