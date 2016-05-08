#include "GameOfLife.h"
#include <iostream>

#include "cilktime.h"

using namespace std;

int main(int argc, char* argv[])
{
	unsigned long long startTicks;
	unsigned long long endTicks;

	GameOfLife game(16, 16, PULSAR);

	// serial version
	startTicks = cilk_getticks();
	for (int i = 0; i < 10; i++)
	{
		cout << "Iteration: " << i << endl;

		game.printIteration();
		system("pause");
		system("cls");
		game.nextIterSerial();
	}
	endTicks = cilk_getticks();
	cout << "Serial time: \t\t\t" << endTicks - startTicks << " ticks\n";

	// parallel version
	startTicks = cilk_getticks();
	for (int i = 0; i < 10; i++)
	{
		// TODO: IMPLEMENT PARALLEL FUNCTION
		game.nextIterParallel();
	}
	endTicks = cilk_getticks();
	cout << "Parallel time: \t" << endTicks - startTicks << " ticks\n";
}
