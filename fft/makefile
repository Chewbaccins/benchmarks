num_procs = 4
prob_size = 2048

fft: fft.c
	mpicc fft.c -o fft -lrt -lpthread -lm -Wall -Werror

median: median.c
	gcc median.c -o median -Wall -Werror

testfft: fft median
	for i in 1 2 3 4 5 6 7 8 9 10; do \
		mpirun -np $(num_procs) ./fft $(prob_size); \
	done; \
	./median; \
	rm results.out \