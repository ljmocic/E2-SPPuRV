#include "matrixFunctions.h"

//Sort algorithms
void bubbleSort1D(int* matrix, int n, int m, bool rastuce){
	for(int i = 0; i < n*m; i++){
		for(int j = 0; j < n*m; j++){
			if(rastuce){
				if(matrix[i] < matrix[j]){
					swap(matrix[i], matrix[j]);
				}
			}
			else{
				if(matrix[i] > matrix[j]){
					swap(matrix[i], matrix[j]);
				}
			}
		}
	}
}

void bubbleSort2D(int** matrix, int n, int m, bool rastuce){
	int p, q, x, y; // for index manipulation n-cols m-rows
	for(int i = 0; i < n*m; i++){
		for(int j = 0; j < n*m; j++){
			p = i/m;
			q = i%m;
			x = j/m;
			y = j%m;
			if(rastuce){
				if(matrix[p][q] < matrix[x][y]){
					swap(matrix[p][q], matrix[x][y]);
				}
			}
			else{
				if(matrix[p][q] > matrix[x][y]){
					swap(matrix[p][q], matrix[x][y]);
				}
			}
		}
	}
}

void bubbleSortVector(vector<vector<int>>* matrix, int n, int m, bool rastuce){
	int p, q, x, y; // for index manipualtion
	for(int i = 0; i < n*m; i++){
		for(int j = 0; j < n*m; j++){
			p = i/m;
			q = i%m;
			x = j/m;
			y = j%m;
			if(rastuce){
				if((*matrix)[p][q] < (*matrix)[x][y]){
					swap((*matrix)[p][q], (*matrix)[x][y]);
				}
			}
			else{
				if((*matrix)[p][q] > (*matrix)[x][y]){
					swap((*matrix)[p][q], (*matrix)[x][y]);
				}
			}
		}
	}
}

void quickSort1D(int* niz, int left, int right){
    if (left < right)
    {
        int i = left;
        int j = right;
        int pivot = niz[(i+j)/2];
        while (i<=j)
        {
            while (niz[i] < pivot) i++;
            while (niz[j] > pivot) j--;
            if (i<=j)
            {
                swap(niz[i], niz[j]);
                i++;
                j--;
            }
        }
        quickSort1D(niz, left, j);
        quickSort1D(niz, i, right);
    }
}

//Random generators
void pushRandNumsMatrix1D(int* matrix, int n, int m){
	for (int i = 0; i < n*m; i++)  {   
		  matrix[i] = rand() % 100 + 1;
	} 
}

void pushRandNumsMatrix2D(int** matrix, int n, int m){
	int x = 0;
	for (int i = 0; i < n; i++)  {   
		for (int j = 0; j < m; j++)  {   
			//matrix[i][j] = rand() % 100 + 1;
			x++;
			matrix[i][j] = x;
		}
	} 
}

void pushRandNumsMatrixVector(vector<vector<int>> *matrix, int n, int m){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			(*matrix)[i][j] = rand() % 100 + 1;
		}
	}
}

//1D
void initMatrix1D(int* matrix, int n, int m){
	//n - rows
	//m -cols
	for (int i = 0; i < n*m; i++)  {   
		  matrix[i] = 0;
	} 
}

void printMatrix1D(int* matrix, int n, int m){
	cout<<"matrix1D: "; 
	for (int i = 0; i < n*m; i++)  {   
		  cout<<matrix[i]<<" ";
	} 
	cout << endl;
}

void sortMatrix1D(int* matrix, int n, int m, bool rastuce){
	bubbleSort1D(matrix, n, m, rastuce);
}

//2D
void initMatrix2D(int** matrix, int n, int m){
	for (int i = 0; i < n; i++)  {   
		for (int j = 0; j < m; j++){    
			matrix[i][j] = 0;   
		}  
	} 
}

void printMatrix2D(int** matrix, int n, int m){
	cout<<endl;
	cout<<"matrix2D: " << endl; 
	for (int i = 0; i < n; i++)  {   
		for (int j = 0; j < m; j++){    
			cout << matrix[i][j] << " "; 
		} 
		cout << endl;
	} 
	cout << endl;
}

void sortMatrix2D(int** matrix, int n, int m, bool rastuce){
	cout << "Sorted: ";
	bubbleSort2D(matrix, n, m, rastuce);
}

void transposeMatrix2D(int **matrix, int n, int m){
	cout << "Transposed +";
	for (int i = 0; i < n; i++)  { 
		for (int j = 0; j < m/2; j++){      
			swap(matrix[i][j], matrix[j][i]);
		} 
	}
}

void flipMatrix2D(int **matrix, int n, int m){
	cout << " Flipped -> Rotated";
	for (int i = 0; i < n; i++)  { 
		for (int j = 0; j < m/2; j++){      
			swap(matrix[i][j], matrix[i][n-j-1]);
		} 
	}
}

//vector
vector<vector<int>> initMatrixVector(int n, int m){
	vector<vector<int>> matrix(n, vector<int>(m));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			matrix[i][j] = 0;
		}
	}
	return matrix;
}

void printMatrixVector(vector<vector<int>> *matrix, int n, int m){
	cout << "Matrix vector<vector<int>>: "<< endl;
	vector<int> tempVec;
	for (int i = 0; i < n; i++)  { 
		for (int j = 0; j < m; j++){    
			tempVec = (*matrix).at(i);
			cout << tempVec.at(j) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void sortMatrixVector(vector<vector<int>> *matrix, int n, int m, bool rastuce){
	bubbleSortVector(matrix, n, m, rastuce);
}