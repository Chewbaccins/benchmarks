# Cholesky Decomposition

### Serial tests
testSerial.c contains tests for the serial implementation 
###### compile
make cholSerial
###### run
./cholSerial [matrix size]
###### results
results are given in GFlops

---
### Serial and OpenMP tests
testOMP.c contains tests for the serial and OpenMP implementation
###### compile
make cholOMP
###### run
./cholOMP [matrix size] [number of threads]
###### results
results are given in GFlops

---
### MPI tests
testMPI.c contains tests for MPI implementation
###### compile 
make cholMPI
###### run
mpirun -np [number of processes] ./cholMPI [matrix size]
###### results
results are given in GFlops
