cholOMP: testOMP.c matrix.c cholOMP.c 
	mpicc -Wall -o "cholOMP" "testOMP.c" "matrix.c" "cholOMP.c" -lm -ggdb -fopenmp

cholSerial: testSerial.c matrix.c cholSerial.c  
	mpicc -Wall -o "cholSerial" "testSerial.c" "matrix.c" "cholSerial.c" -lm -ggdb -fopenmp

cholMPI: testMPI.c cholMPI.c matrix.c
	mpicc -Wall -o "cholMPI" "testMPI.c" "cholMPI.c" "matrix.c" -lm -ggdb -fopenmp