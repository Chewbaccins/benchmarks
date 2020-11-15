### Serial tests
testSerial.c contains tests for the serial implementation
make cholSerial
./cholSerial [matrix size]

### Serial and OpenMP tests
testOMP.c contains tests for the serial and OpenMP implementation
make cholOMP
./cholOMP [matrix size] [number of threads]

### MPI tests
testMPI.c contains tests for MPI implementation
make cholMPI
mpirun -np [number of processes] ./cholMPI [matrix size]
