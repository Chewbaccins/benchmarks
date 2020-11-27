num_procs = 4
prob_size = 2048

fft: fft.c
	mpicc fft.c -o fft -lrt -lpthread -lm -Wall

max_avg: max_avg.c
	gcc max_avg.c -o max_avg -Wall

testfft: fft max_avg
	for i in 1 2 3 4 5; do \
		mpirun -np $(num_procs) ./fft $(prob_size); \
	done; \
	./max_avg; \
	rm results.out \