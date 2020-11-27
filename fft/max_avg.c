#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* infile;
	float flops = 0, temp_flops = 0;
	infile = fopen("results.out", "r");
	if (infile == NULL) return 0;
	for (int i = 0; i < 5; i++) {
		fscanf(infile, "%f\n", &temp_flops);
		if (flops < temp_flops) flops = temp_flops;
	}
	printf("\nmax_flops = %f\n\n", flops);
	fclose(infile);
}