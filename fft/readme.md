# Cooley–Tukey FFT algorithm

### MPI tests
fft.c contains tests for MPI implementation
###### compile
make fft
###### run
np must be >= 2

problem size must be 2^x

for single run

mpirun -np [number of processes] ./fft [problem size]

for test run (max flops in 5 runs)

make testfft

###### results
results are given in Flops
