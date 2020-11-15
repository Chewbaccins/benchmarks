#include "matrix.h"
#include "cholMPI.h"
#include <mpi.h>

int main(int argc, char **argv)
{
    // generate seed
    srand(time(NULL));
    if (argc < 2)

    {   
       printf("You did not feed me arguments, I will die now :( ... \n");
       printf("Usage: %s [matrix size] \n", argv[0]);
       return 1;
    }
    int matrixSize = atoi(argv[1]);
    //int matrixMaxSize = atoi(argv[2]);
    //int matrixStepSize = atoi(argv[3]);
    
    // Generate random SPD matrix
    double** A = initialize(0, 10, matrixSize);
    /*printf("Chol matrix\n");
    print(A, matrixSize);*/
    double **L = initialize(0, 10, matrixSize);
    
    int rank;
    //Testing OpenMpi Program 
    
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        //A = initialize(0, 10, matrixSize);
        //L = initialize(0, 10, matrixSize);
        //**L = initialize(0, 10, matrixSize);
        copyMatrix(A,L,matrixSize);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    cholMPI(A,L, matrixSize, argc, argv); // Warning: cholMPI() acts directly on the given matrix L

    MPI_Finalize();
}


