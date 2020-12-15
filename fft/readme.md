# Cooley–Tukey FFT algorithm

### MPI tests
fft.c contains tests for MPI implementation
###### compile
make fft
###### run
np must be >= 2 (this program uses first MPI process only to send and receive data from other processes, thats why 2 or more MPI processes required)

problem size must be 2^x

for single run

mpirun -np [number of processes] ./fft [problem size]

for test run (median flops in 10 runs)

make testfft

###### results
results are given in Flops
