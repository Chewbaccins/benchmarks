### Serial tests
testSerial.c contains tests for the serial implementation 
###### compile
make cholSerial
###### run
./cholSerial [matrix size]

---
### Serial and OpenMP tests
testOMP.c contains tests for the serial and OpenMP implementation
###### compile
make cholOMP
###### run
./cholOMP [matrix size] [number of threads]

---
### MPI tests
testMPI.c contains tests for MPI implementation
###### compile 
make cholMPI
###### run
mpirun -np [number of processes] ./cholMPI [matrix size]