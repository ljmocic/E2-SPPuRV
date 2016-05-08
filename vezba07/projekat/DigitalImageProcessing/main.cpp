#include <cilk/cilk.h>
#include <iostream>
#include <stdlib.h>

#include "BitmapRawConverter.h"
#include "cilktime.h"

#define __ARG_NUM__ 8

using namespace std;

/**
* @brief Serial version of moving average filter.
* @param inBuffer buffer of input image
* @param outBuffer buffer of output image
* @param width image width
* @param height image height
*/
void filter_serial_avg(int* inBuffer, int* outBuffer, int width, int height){
	for (int i = 1; i < width - 1; i ++){
		for (int j = 1; j < height - 1; j++){
			for (int m = -1; m <= 1; m++){
				for (int n = -1; n <= 1; n++){
					outBuffer[i * width + j] += inBuffer[(i + n) * width + (j + m)] / 9;
				}
			}
		}
	}
}


/**
* @brief Parallel version of moving average filter.
* 
* @param inBuffer buffer of input image
* @param outBuffer buffer of output image
* @param width image width
* @param height image height
*/
void filter_parallel_avg(int* inBuffer, int* outBuffer, int width, int height){
	// TODO: PLACE CODE HERE
	for (int i = 1; i < width - 1; i ++){
		cilk_for (int j = 1; j < height - 1; j++){
			int sum = 0;
			sum += __sec_reduce_add(inBuffer[( (j - 1) * width + (i - 1) ) : 3]);
			sum += __sec_reduce_add(inBuffer[(	j  * width + (i - 1) ) : 3]);
			sum += __sec_reduce_add(inBuffer[( (j + 1) * width + (i - 1) ) : 3]);
			outBuffer[j * width + i] = sum/9;
		}
	}
}


void quicksort(int arr[], int low, int high) {
	int i = low, j = high, z = arr[(low + high) / 2];

	do{
		while (arr[i] < z) i++;
		while (arr[j] > z) j--;

		if (i <= j) {
			swap(arr[i], arr[j]); 
			i++; j--;
		}
	} while (i <= j);

	//not worth using parallel quicksort for such small submatrix
	//for bigger submatrix use parallel quicksort
	//if (low < j) cilk_spawn quicksort(arr, low, j); for parallel
	if (low < j) quicksort(arr, low, j);
	if (i < high) quicksort(arr, i, high);
	//cilk_sync;
}

/**
* @brief Serial version of median filter.
* @param inBuffer buffer of input image
* @param outBuffer buffer of output image
* @param width image width
* @param height image height
*/
void filter_serial_med(int* inBuffer, int* outBuffer, int width, int height){
	// TODO: PLACE CODE HERE
	for (int i = 1; i < width - 1; i ++){
		for (int j = 1; j < height - 1; j++){

			int a[9];
			int x = 0;

			//submatrix -> array
			for (int m = -1; m <= 1; m++){
				for (int n = -1; n <= 1; n++){
					a[x] = inBuffer[(j + n) * width + (i + m)];
					x++;
				}
			}

			//sort
			//quicksort(a, 0, 8);

			//bubble
			for (int m = 0; m < 9; m++){
				for (int n = 0; n < 9; n++){
					if(a[m] > a[n]) swap(a[m], a[n]);
				}
			}
			
			outBuffer[j * width + i] = a[4];

		}
	}
}


/**
* @brief Parallel version of median filter.
* 
* @param inBuffer buffer of input image
* @param outBuffer buffer of output image
* @param width image width
* @param height image height
*/
void filter_parallel_med(int* inBuffer, int* outBuffer, int width, int height){
	// TODO: PLACE CODE HERE
	for (int i = 1; i < width - 1; i ++){
		cilk_for (int j = 1; j < height - 1; j++){

			int a[9];

			//submatrix -> array
			a[0:3] = inBuffer[( (j - 1) * width + (i - 1) ) : 3];
			a[3:3] = inBuffer[(	 j  * width + (i - 1) ) : 3];
			a[6:3] = inBuffer[( (j + 1) * width + (i - 1) ) : 3];
			
			//sort
			quicksort(a, 0, 8);

			//bubble
			/*
			for (int m = 0; m < 9; m++){
				for (int n = 0; n < 9; n++){
					if(a[m] > a[n]) swap(a[m], a[n]);
				}
			}
			*/

			
			//put median in center of current submatrix
			outBuffer[j * width + i] = a[4];

		}
	}
}


/**
* @brief Serial version of edge filter.
* @param inBuffer buffer of input image
* @param outBuffer buffer of output image
* @param width image width
* @param height image height
*/
void filter_serial_edge(int* inBuffer, int* outBuffer, int width, int height){
	// TODO: PLACE CODE HERE

	//binarize picture
	//do only once, because we have only one inBuffer
	for (int i = 1; i < width - 1; i ++){
		for (int j = 1; j < height - 1; j++){
			if(inBuffer[j * width + i] < 128) inBuffer[j * width + i] = 0;
			else inBuffer[j * width + i] = 1;
		}
	}

	for (int i = 1; i < width - 1; i ++){
		for (int j = 1; j < height - 1; j++){

			int sum = 0;

			//get submatrix sum 
			for (int m = -1; m <= 1; m++){
				for (int n = -1; n <= 1; n++){
					sum += inBuffer[(j + n) * width + (i + m)];
				}
			}

			//formulas for P and O
			int P = sum > 0 ? 1 : 0;
			int O = sum < 9 ? 0 : 1;

			//see abs(P-O) is 1 or 0, and convert back to rgb range (0, 255) 
			outBuffer[j * width + i] =  abs(P-O) > 0  ? 0 : 255;

		}
	}
}


/**
* @brief Parallel version of edge filter.
* 
* @param inBuffer buffer of input image
* @param outBuffer buffer of output image
* @param width image width
* @param height image height
*/
void filter_parallel_edge(int* inBuffer, int* outBuffer, int width, int height){
	// TODO: PLACE CODE HERE
	for (int i = 1; i < width - 1; i ++){
		cilk_for (int j = 1; j < height - 1; j++){

			int sum = 0;

			//get submatrix sum using reductors
			sum += __sec_reduce_add(inBuffer[( (j - 1) * width + (i - 1) ) : 3]);
			sum += __sec_reduce_add(inBuffer[(		j  * width + (i - 1) ) : 3]);
			sum += __sec_reduce_add(inBuffer[( (j + 1) * width + (i - 1) ) : 3]);

			int P = sum > 0 ? 1 : 0;
			int O = sum < 9 ? 0 : 1;

			outBuffer[j * width + i] =  abs(P-O) > 0  ? 0 : 255;

		}
	}
}

/**
* @brief Print program usage.
*/
void usage()
{
	cout << "ERROR: call program like DigitalImageProcessing.exe input.bmp outputSerialAvg.bmp outputParallelAvg.bmp outputSerialMed.bmp outputParallelMed.bmp outputSerialEdge.bmp outputParallelEdge.bmp." << endl;
}


int main(int argc, char* argv[])
{
	if (argc != __ARG_NUM__)
	{
		usage();
		return 0;
	}

	BitmapRawConverter inputFile(argv[1]);

	unsigned int width = inputFile.getWidth();
	unsigned int height = inputFile.getHeight();

	BitmapRawConverter outputFileSerialAvg(width, height);
	BitmapRawConverter outputFileParallelAvg(width, height);
	BitmapRawConverter outputFileSerialMed(width, height);
	BitmapRawConverter outputFileParallelMed(width, height);
	BitmapRawConverter outputFileSerialEdge(width, height);
	BitmapRawConverter outputFileParallelEdge(width, height);

	unsigned long long start_tick;
	unsigned long long end_tick;


	// SERIAL VERSION - MOVING AVERAGE FILTER
	cout << "Running serial version of moving average filter" << endl;
	start_tick = cilk_getticks();
	filter_serial_avg(inputFile.getBuffer(), outputFileSerialAvg.getBuffer(), width, height);
	end_tick = cilk_getticks();
	cout << "Ticks: " << end_tick - start_tick << endl;
	outputFileSerialAvg.pixelsToBitmap(argv[2]); // saves the result in a file


	// PARALLEL VERSION - MOVING AVERAGE FILTER
	cout << "Running parallel version of moving average filter" << endl;
	start_tick = cilk_getticks();
	// TODO: IMPLEMENT filter_parallel_avg FUNCTION
	filter_parallel_avg(inputFile.getBuffer(), outputFileParallelAvg.getBuffer(), width, height);
	end_tick = cilk_getticks();
	cout << "Ticks: " << end_tick - start_tick << endl;
	outputFileParallelAvg.pixelsToBitmap(argv[3]); // saves the result in a file


	// SERIAL VERSION - MEDIAN FILTER
	cout << "Running serial version of median filter" << endl;
	start_tick = cilk_getticks();
	// TODO: IMPLEMENT filter_serial_med FUNCTION
	filter_serial_med(inputFile.getBuffer(), outputFileSerialMed.getBuffer(), width, height);
	end_tick = cilk_getticks();
	cout << "Ticks: " << end_tick - start_tick << endl;
	outputFileSerialMed.pixelsToBitmap(argv[4]); // saves the result in a file


	// PARALLEL VERSION - MEDIAN FILTER
	cout << "Running parallel version of median filter" << endl;
	start_tick = cilk_getticks();
	// TODO: IMPLEMENT filter_parallel_med FUNCTION
	filter_parallel_med(inputFile.getBuffer(), outputFileParallelMed.getBuffer(), width, height);
	end_tick = cilk_getticks();
	cout << "Ticks: " << end_tick - start_tick << endl;
	outputFileParallelMed.pixelsToBitmap(argv[5]); // saves the result in a file

	// SERIAL VERSION - EDGE FILTER
	cout << "Running serial version of edge filter" << endl;
	start_tick = cilk_getticks();
	// TODO: IMPLEMENT filter_parallel_med FUNCTION
	filter_serial_edge(inputFile.getBuffer(), outputFileSerialEdge.getBuffer(), width, height);
	end_tick = cilk_getticks();
	cout << "Ticks: " << end_tick - start_tick << endl;
	outputFileSerialEdge.pixelsToBitmap(argv[6]); // saves the result in a file

	// PARALLEL VERSION - EDGE FILTER
	cout << "Running parallel version of edge filter" << endl;
	start_tick = cilk_getticks();
	// TODO: IMPLEMENT filter_parallel_med FUNCTION
	filter_parallel_edge(inputFile.getBuffer(), outputFileParallelEdge.getBuffer(), width, height);
	end_tick = cilk_getticks();
	cout << "Ticks: " << end_tick - start_tick << endl;
	outputFileParallelEdge.pixelsToBitmap(argv[7]); // saves the result in a file

	return 0;
}
