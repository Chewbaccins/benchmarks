### MPI tests
fft.c contains tests for MPI implementation
###### compile
make fft
###### run
problem size must be 2^x
mpirun -np [number of processes] ./fft [problem size]
