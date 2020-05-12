#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "matrix.h"
#include "cholOMP.h"

int testBasicOutputOfChol(double **A, double ** L, int n);

typedef int bool;
enum { false, true };
struct timespec begin={0,0}, end={0,0};

time_t start, stop;

int main(int argc, char **argv)
{
    // generate seed
    srand(time(NULL));
    
    if (argc != 3)

    {   
       printf("You did not feed me arguments, I will die now :( ... \n");
       printf("Usage: %s [matrix size] [number of threads] \n", argv[0]);
       return 1;
    }
    int matrixSize = atoi(argv[1]);
    int threadsNumber = atoi(argv[2]);
    
    
    
    printf("Test basic output for a matrix of size %d:\n", matrixSize);
    // Generate random SPD matrix
    double** A = initialize(0, 10, matrixSize);
    //printf("Chol matrix\n");
    //print(A, matrixSize);
    double **L = initialize(0, 10, matrixSize);
        
    //Testing OpenMP Program
    printf("Testing OpenMP implementation Output: \n");
    omp_set_num_threads(threadsNumber);
    copyMatrix(A,L,matrixSize);
    
    clock_gettime(CLOCK_MONOTONIC, &begin);
    cholOMP(L, matrixSize);
    clock_gettime(CLOCK_MONOTONIC, &end); //Get the current time.
    
    testBasicOutputOfChol(A,L,matrixSize);
    
    //Test execution time
    printf("The OpenMP computation took %.5f seconds \n",
           ((double)end.tv_sec + 1.0e-9 * end.tv_nsec) - 
           ((double)begin.tv_sec + 1.0e-9 * begin.tv_nsec));

    //Test FLOPs
    double time = (((double)end.tv_sec + 1.0e-9 * end.tv_nsec) - 
           ((double)begin.tv_sec + 1.0e-9 * begin.tv_nsec));
    double computations = 0;
    computations += (double)matrixSize / 1000000000 ;
    computations += ((double)matrixSize * (matrixSize - 1) / 2) / 1000000000;
    computations += ((double)matrixSize * matrixSize * matrixSize - matrixSize) / 6000000000;
    computations += ((double)matrixSize * matrixSize * matrixSize - matrixSize) / 6000000000;
    
    printf("OMP %.5f GFLOPs\n", 
           ( computations / time));

    printf("\n");
    return 0;
}

int testBasicOutputOfChol(double **A, double ** L, int n)
{
    double ** LLT = matrixMultiply(L, transpose(L, n), n);
  
    int i, j;
    float precision = 0.00000000001;
    for (i = 0; i < n; i++){
                for (j = 0; j < n; j++){
                        if( !(abs(LLT[i][j] - A[i][j]) < precision))
                        {
                         printf("FAILED\n"); //if it fails show the error
                         ComputeSumOfAbsError(A,LLT,n);
                         return 0;
                        }
                }
        }
        printf("PASSED\n");
        return 1;
}