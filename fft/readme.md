# Cooley–Tukey FFT algorithm

### MPI tests
fft.c contains tests for MPI implementation
###### compile
make fft
###### run
np must be >= 2

problem size must be 2^x

mpirun -np [number of processes] ./fft [problem size]
###### results
results are given in Flops
