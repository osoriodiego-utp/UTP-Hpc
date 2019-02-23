// Pi calculated with Montecarlo method.
//$ g++ -std=c++11 seq.cpp -o seqExe
//$ ./seqExe

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;


float **MatrixMultiplication(float **m1, float **m2, int size){
	float **result = (float **)malloc(size * sizeof(float *));
	for (int i = 0; i < size; ++i)
		result[i] = (float *)malloc(size * sizeof(float));

	for(int i = 0; i < size; ++i){
		for(int j = 0; j < size; ++j){
			float resultAux = 0;
			for(int k = 0; k < size; ++k){
				resultAux += m1[i][k] * m2[k][j];
			}
			result[i][j] = resultAux;
		}
	}
	return result;
}

void FillMatrix(float **vec, int size)
{
	FILE *f = fopen("ficheroMatrix.csv", "w");
	float a = 9.0;
	for (int i=0; i < size; ++i){
		for (int j=0; j < size; ++j){
			vec[i][j] = ((float)rand() / (float)(RAND_MAX)) * a;
			fprintf(f, "%f,", vec[i][j]);
		}
	}
	fclose(f);
}


int main()
{

	vector<long> matrixSize = {100, 500, 1000, 5000, 10000, 50000};

	for (int j=0; j<matrixSize.size(); j++)
      {
      	srand(time(NULL));

		double start, delta;		// calculo del tiempo
		//int size;
		//printf("Enter the size: ");
		//scanf("%d", &size);


		float **matrix1 = (float **)malloc(matrixSize[j] * sizeof(float *));
		for (int i = 0; i < matrixSize[j]; ++i)
			matrix1[i] = (float *)malloc(matrixSize[j] * sizeof(float));

		float **matrix2 = (float **)malloc(matrixSize[j] * sizeof(float *));
		for (int i = 0; i < matrixSize[j]; ++i)
			matrix2[i] = (float *)malloc(matrixSize[j] * sizeof(float));

		FillMatrix(matrix1, matrixSize[j]);
		FillMatrix(matrix2, matrixSize[j]);
		
		start = clock();
		float **matrixResult = MatrixMultiplication(matrix1, matrix2, matrixSize[j]);
		delta = double(clock()-start)/CLOCKS_PER_SEC;

		cout<<"Matrix size: "<<matrixSize[j]<<"x"<<matrixSize[j]<<endl;
		cout<<"MatrixMultiplication time: "<<delta<<"\n"<<endl;
	}

	return 0;
}