#include "matrixFunctions.h"

using namespace std;


int main(int argc, char* argv[]){
	int* matrix1D;
	int** matrix2D;

	int rows;
	int cols;
	//set through arguments
	//rows = atoi(argv[1]);
	//cols = atoi(argv[2]);

	//or manually
	rows = 3;
	cols = 3;

	//1D stuff
	matrix1D = new int[rows*cols];

	initMatrix1D(matrix1D, rows, cols);
	printMatrix1D(matrix1D, rows, cols);

	pushRandNumsMatrix1D(matrix1D, rows, cols);
	printMatrix1D(matrix1D, rows, cols);

	quickSort1D(matrix1D, 0, rows*cols-1);
	//sortMatrix1D(matrix1D, rows, cols, true);
	printMatrix1D(matrix1D, rows, cols);

	delete[] matrix1D;

	//2D stuff
	matrix2D = new int*[rows]; 

	for(int i = 0; i < rows; i++) matrix2D[i] = new int[cols]; 

	initMatrix2D(matrix2D, rows, cols);
	printMatrix2D(matrix2D, rows, cols);

	pushRandNumsMatrix2D(matrix2D, rows, cols);
	printMatrix2D(matrix2D, rows, cols);

	//sortMatrix2D(matrix2D, rows, cols, false);
	//printMatrix2D(matrix2D, rows, cols);
	
	transposeMatrix2D(matrix2D, rows, cols);
	flipMatrix2D(matrix2D, rows, cols);
	printMatrix2D(matrix2D, rows, cols);
	
	for (int i = 0; i < rows; i++)  delete[] matrix2D[i];
	delete[] matrix2D;


	//Vector stuff
	
	vector<vector<int>> matrixVector = initMatrixVector(rows, cols);
	printMatrixVector(&matrixVector, rows, cols);

	pushRandNumsMatrixVector(&matrixVector, rows, cols);
	printMatrixVector(&matrixVector, rows, cols);
	
	sortMatrixVector(&matrixVector, rows, cols, true);
	printMatrixVector(&matrixVector, rows, cols);
	
	for(int i = 0; i < matrixVector.size(); i++) matrixVector[i].clear();

	system("PAUSE");
}