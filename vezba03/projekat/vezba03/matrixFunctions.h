#include <iostream>
#include <vector>
#include <stdlib.h> 

using namespace std;

//Sorting algorithms
void bubbleSort1D(int* matrix, int n, int m, bool rastuce);
void bubbleSort2D(int** matrix, int n, int m, bool rastuce);
void bubbleSortVector(vector<vector<int>>* matrix, int n, int m, bool rastuce);

void quickSort1D(int* niz, int left, int right);

//Random generators
void pushRandNumsMatrix1D(int* matrix, int n, int m);
void pushRandNumsMatrix2D(int** matrix, int n, int m);
void pushRandNumsMatrixVector(vector<vector<int>> *matrix, int n, int m);

//1D
void initMatrix1D(int* matrix, int n, int m);
void printMatrix1D(int* matrix, int n, int m);
void sortMatrix1D(int* matrix, int n, int m, bool rastuce);

//2D
void initMatrix2D(int** matrix, int n, int m);
void printMatrix2D(int** matrix, int n, int m);
void sortMatrix2D(int** matrix, int n, int m, bool rastuce);

void flipMatrix2D(int **matrix, int n, int m);
void transposeMatrix2D(int **matrix, int n, int m);


//Vector
vector<vector<int>> initMatrixVector(int n, int m);
void printMatrixVector(vector<vector<int>> *matrix, int n, int m);
void sortMatrixVector(vector<vector<int>> *matrix, int n, int m, bool rastuce);