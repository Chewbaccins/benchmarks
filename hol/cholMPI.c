#include "cholMPI.h"

int testBasicOutput(double **A, double ** L, int n)
{
    double ** LLT = matrixMultiply(L, transpose(L, n), n);
  
    int i, j;
    float precision = 0.0000001;
    for (i = 0; i < n; i++){
                for (j = 0; j < n; j++){
                        if( !(abs(LLT[i][j] - A[i][j]) < precision))
                        {
                         printf("FAILED\n");
                         ComputeSumOfAbsError(A,LLT,n);
                         return 0;
                        }
                }
        }
        printf("PASSED\n");
        return 1;
}

void cholMPI(double ** A,double ** L, int n, int argc, char ** argv){
    // Warning: cholMPI() acts directly on the given matrix! 
    int npes, rank;
    //MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &npes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0) printf("Test basic output for a matrix of size %d:\n", n);
    
    double start, end;  
    MPI_Barrier(MPI_COMM_WORLD); /* Timing */
    if (rank == 0) {
        start = MPI_Wtime();
        
        
        /*// Test
        printf("A = \n");
        print(L, n);*/
        
    }
    //printf("i am alive!\n");
    
    // For each column
    int i, j, k;
    for (j = 0; j < n; j++) {
    
        /*
         * Step 0:
         * Replace the entries above the diagonal with zeroes
         */
        //if (rank == 0) {
        //  for (i = 0; i < j; i++) {
        //      L[i][j] = 0.0;
        //  }
        //}
        
        /*
         * Step 1:
         * Update the diagonal element
         */
         
        if (j%npes == rank) {

            for (k = 0; k < j; k++) {
                L[j][j] = L[j][j] - L[j][k] * L[j][k];
            }

            L[j][j] = sqrt(L[j][j]);
        }

        // Broadcast row with new values to other processes
        MPI_Bcast(L[j], n, MPI_DOUBLE, j%npes, MPI_COMM_WORLD);

        /*
         * Step 2:
         * Update the elements below the diagonal element
         */

        // Divide the rest of the work
        for (i = j+1; i < n; i++) {
            if (i%npes == rank) {
                for (k = 0; k < j; k++) {
                    L[i][j] = L[i][j] - L[i][k] * L[j][k];
                }
            
                L[i][j] = L[i][j] / L[j][j];
            }
        }
    }
    end = MPI_Wtime();
    for (j = 0; j < n; j++) {
        
        /*
         * Step 0:
         * Replace the entries above the diagonal with zeroes
         */
        if (rank == 0) {
            for (i = 0; i < j; i++) {
                L[i][j] = 0.0;
            }
        }
    }
    
    MPI_Barrier(MPI_COMM_WORLD); /* Timing */
    if (rank == 0){ 
        
        if (rank == 0) {
            printf("Testing MPI implementation Output: \n");
            testBasicOutput(A, L, n);
    	    printf("The MPI computation took %.5f seconds \n",
               (end - start));
        }
        
        //Test FLOPs
        double computations = 0;
        computations += (double)n / 1000000000 ;
        computations += ((double)n * (n - 1) / 2) / 1000000000;
        computations += ((double)n * n * n - n) / 6000000000;
        computations += ((double)n * n * n - n) / 6000000000;
        
        printf("MPI %f GFLOPs\n\n", 
               ( computations / (end - start)));
    }

    //MPI_Finalize();
}
