#include <stdio.h>
#include <stdlib.h>

void swap(double *p,double *q) {
   double t;
   
   t=*p; 
   *p=*q; 
   *q=t;
}

void sort(double a[],int n) { 
   int i,j;

   for(i = 0;i < n-1;i++) {
      for(j = 0;j < n-i-1;j++) {
         if(a[j] > a[j+1])
            swap(&a[j],&a[j+1]);
      }
   }
}

int main() {

   double a[10];
   
   FILE* infile;
   infile = fopen("results.out", "r");
	if (infile == NULL) return 0;
   
   for (int i = 0; i < 10; i++) {
      double temp;
		fscanf(infile, "%lf\n", &temp);
      a[i] = temp;
	}
   
   sort(a,10);
   
   printf("Median = %lf\n", (a[4]+a[5])/2);

	fclose(infile);

   return 0;
}