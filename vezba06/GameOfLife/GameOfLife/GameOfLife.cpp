#include "GameOfLife.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cilk/cilk.h>

using namespace std;

GameOfLife::GameOfLife(unsigned int height, unsigned int width, InitModel model)
{
	m_height = height;
	m_width = width;

	m_buffer = new unsigned char[m_width * m_height];
	m_nextIter = new unsigned char[m_width * m_height];

	// fill buffer
	switch (model)
	{
	case PULSAR:
	{
		if (width > 15 && height > 15)
		{
			memset(m_buffer, 0x0, m_width * m_height * sizeof(unsigned char));
			m_buffer[2 * m_width + 4] = 1;
			m_buffer[2 * m_width + 5] = 1;
			m_buffer[2 * m_width + 6] = 1;

			m_buffer[2 * m_width + 10] = 1;
			m_buffer[2 * m_width + 11] = 1;
			m_buffer[2 * m_width + 12] = 1;

			m_buffer[4 * m_width + 2] = 1;
			m_buffer[5 * m_width + 2] = 1;
			m_buffer[6 * m_width + 2] = 1;

			m_buffer[4 * m_width + 7] = 1;
			m_buffer[5 * m_width + 7] = 1;
			m_buffer[6 * m_width + 7] = 1;

			m_buffer[4 * m_width + 9] = 1;
			m_buffer[5 * m_width + 9] = 1;
			m_buffer[6 * m_width + 9] = 1;

			m_buffer[4 * m_width + 14] = 1;
			m_buffer[5 * m_width + 14] = 1;
			m_buffer[6 * m_width + 14] = 1;

			m_buffer[7 * m_width + 4] = 1;
			m_buffer[7 * m_width + 5] = 1;
			m_buffer[7 * m_width + 6] = 1;

			m_buffer[7 * m_width + 10] = 1;
			m_buffer[7 * m_width + 11] = 1;
			m_buffer[7 * m_width + 12] = 1;

			m_buffer[9 * m_width + 4] = 1;
			m_buffer[9 * m_width + 5] = 1;
			m_buffer[9 * m_width + 6] = 1;

			m_buffer[9 * m_width + 10] = 1;
			m_buffer[9 * m_width + 11] = 1;
			m_buffer[9 * m_width + 12] = 1;

			m_buffer[10 * m_width + 2] = 1;
			m_buffer[11 * m_width + 2] = 1;
			m_buffer[12 * m_width + 2] = 1;

			m_buffer[10 * m_width + 7] = 1;
			m_buffer[11 * m_width + 7] = 1;
			m_buffer[12 * m_width + 7] = 1;

			m_buffer[10 * m_width + 9] = 1;
			m_buffer[11 * m_width + 9] = 1;
			m_buffer[12 * m_width + 9] = 1;

			m_buffer[10 * m_width + 14] = 1;
			m_buffer[11 * m_width + 14] = 1;
			m_buffer[12 * m_width + 14] = 1;

			m_buffer[14 * m_width + 4] = 1;
			m_buffer[14 * m_width + 5] = 1;
			m_buffer[14 * m_width + 6] = 1;

			m_buffer[14 * m_width + 10] = 1;
			m_buffer[14 * m_width + 11] = 1;
			m_buffer[14 * m_width + 12] = 1;

			break;
		}
		else
		{
			cout << "Board too small, using RANDOM." << endl;
		}
	}

	case RANDOM:
	{
		srand(time(NULL));
		for (unsigned int i = 0; i < m_height; i++)
		{
			for (unsigned int j = 0; j < m_width; j++)
			{
				m_buffer[i * m_width + j] = rand() % 2;
			}
		}
		break;
	}

	default:
		break;
	}
}


void GameOfLife::printIteration()
{
	for (int row = 0; row < m_height; row++)
	{
		for (int col = 0; col < m_width; col++)
		{
			char c;

			if (m_buffer[row * m_width + col] == 1)
				c = 0xb2;
			else
				c = 0x20;

			cout << c << " ";
		}
		cout << "\n";
	}
}


int GameOfLife::getNeighbourSum(unsigned int row, unsigned int col)
{
	int sum = 0;

	for (int r = row - 1; r <= row + 1; r++) {
		for (int c = col - 1; c <= col + 1; c++) {
			if ((r >= m_height) || (c >= m_width)) continue;
			else if (!((r == row) && (c == col))) sum += m_buffer[r * m_width + c];
		}
	}

	return sum;
}


void GameOfLife::nextIterSerial(int poc = 0, int kraj = 0, int switch_buffers = 1)
{
	if (switch_buffers) kraj = m_height;
	for (int row = poc; row < kraj; row++)
	{
		for (int col = 0; col < m_width; col++)
		{
			// TODO: IMPLEMENT getNeighbourSum
			int neighbours = getNeighbourSum(row, col);
			if (m_buffer[row * m_width + col] == 1)
			{
				if ((neighbours == 2) || (neighbours == 3))
				{
					m_nextIter[row * m_width + col] = 1;
				}
				else
				{
					m_nextIter[row * m_width + col] = 0;
				}
			}
			else
			{
				if (neighbours == 3)
				{
					m_nextIter[row * m_width + col] = 1;
				}
				else
				{
					m_nextIter[row * m_width + col] = 0;
				}
			}
		}
	}

	// switch buffers
	if (switch_buffers) {
		unsigned char* temp = m_buffer;
		m_buffer = m_nextIter;
		m_nextIter = temp;
	}
}


void GameOfLife::nextIterParallelRecursive(int begin, int end) {
	if ((end - begin) <= 16) nextIterSerial(begin, end, 0);
	else {
		unsigned int add = (end - begin) / 4;
		cilk_spawn nextIterParallelRecursive(begin, begin + add);
		cilk_spawn nextIterParallelRecursive(begin + add, begin + add * 2);
		cilk_spawn nextIterParallelRecursive(begin + add * 2, begin + add * 3);
		nextIterParallelRecursive(begin + add * 3, end);
		cilk_sync;
	}
}

void GameOfLife::nextIterParallel()
{
	// TODO: PLACE CODE HERE
	nextIterParallelRecursive(0, m_height, 0);

	unsigned char* temp = m_buffer;
	m_buffer = m_nextIter;
	m_nextIter = temp;

}


GameOfLife::~GameOfLife()
{
	delete[] m_buffer;
	delete[] m_nextIter;
}