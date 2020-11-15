#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#define LINE 131072
#define MAXN 131072
#define PI 3.14159265

char linie[LINE];
int i, n;
double x[MAXN];
int r;

//read file input
int readFile(FILE *f)
{
     fgets(linie, LINE, f);
     n = atoi(linie);
     for(i = 0 ; i < n ; i++)
           fscanf(f, "%lf ", &x[i]);
     return 0;
}

//functie logaritm :)
int log2_local(int p)
{
    int putere = 1;
    int i = 0;
    while (putere < p)
    {
          putere = putere << 1;
          i++;
    }
    if (putere > p)
       i--;
    return i;
}

//conversie decimamal to binar - returneaza un vector cu bitii corespunzatori reprezentarii binare
int* decimal_to_binary(int number)
{
    int* binar;
    int k = r-1;
    binar = (int*) malloc ((k + 1) * sizeof(int));


    while (number > 0)
    {
          binar[k --] = number % 2;
          number = number / 2;
    }
    while(k >= 0)
    {
        binar[k--] = 0;
    }
    return binar;
}

int main(int argc,char **argv)
{
    if (argc != 2) {
        printf("size required\n");
        return 0;
    }
    MPI_Status Stat;
    int j, p, m;
    int putere = 1;
    int i1, i2, i3;
    //int dif;
    int *b;
    int size2;
    int index;
    int  numtasks, rank, rc, tag = 1;
    //FILE *fin, *fout;
    double Rx[MAXN], Ry[MAXN], Sx[MAXN], Sy[MAXN];
    double alfa, time_start, time_finish;

    rc = MPI_Init(&argc, &argv);
    if (rc != MPI_SUCCESS)
    {
       printf ("Error starting MPI program. Terminating.\n");
       MPI_Abort(MPI_COMM_WORLD, rc);
    }
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    if(rank == 0)
    {
        //fin = fopen(argv[1], "r");
        size2 = atoi(argv[1]);
        //fout = fopen(argv[2], "w");
        n=size2;
        //printf("n = %d\n", atoi(argv[1]));
        for (i=0;i<n;i++)
        {
            x[i]=rand();
        }
        //printf("%d\n", rand());
         r = log2_local(n);
         time_start = MPI_Wtime();
         //trimit n,r, si x tuturor procesoarelor
         for(i = 1; i < numtasks; i ++)
         {
               MPI_Send(&n, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
               MPI_Send(&r, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
               MPI_Send(&x, n, MPI_DOUBLE, i, tag, MPI_COMM_WORLD);
         }

         //bucla exterioara
         for(m = 0 ; m < r ; m ++)
         {
               //astept primirea Rx, Ry de la procesoare
               for(j = 1 ; j < numtasks ; j ++)
               {
                     for(p = 0 ; p < n ; p ++)
                     {
                         if((p % (numtasks - 1) == (j - 1)))
                         {

                               MPI_Recv(&index, 1, MPI_INT, j, tag, MPI_COMM_WORLD, &Stat);
                               MPI_Recv(&Rx[index], 1, MPI_DOUBLE, j, tag, MPI_COMM_WORLD, &Stat);
                               MPI_Recv(&Ry[index], 1, MPI_DOUBLE, j, tag, MPI_COMM_WORLD, &Stat);

                         }

                     }
               }

               //trimit actualizarea Rx, Ry catre toate procesoarele
               for(j = 1 ; j < numtasks ; j ++)
               {
                     MPI_Send(&Rx, n, MPI_DOUBLE, j, tag, MPI_COMM_WORLD);
                     MPI_Send(&Ry, n, MPI_DOUBLE, j, tag, MPI_COMM_WORLD);
               }

         }
         
         time_finish = MPI_Wtime()-time_start;
         double flops = 2 * (log2(size2)) / time_finish;
         printf("size = %d procs = %d time = %lf FLOPS = %.9lf\n", size2, numtasks, time_finish, flops);
         //afisez rezultatul final
         //for(i = 0 ; i < n ; i ++)
         //{
        //       fprintf(fout, "%lf + (%lf) * j \n", Rx[i], Ry[i]);
         //}

    }
    else
    {


           //primesc de la procesorul 0 n,r si x
           MPI_Recv(&n, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
           MPI_Recv(&r, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
           MPI_Recv(&x, n, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &Stat);

           //incep alg
           for(i = 0 ; i < n ; i ++)
           {
                Rx[i] = x[i];
                Ry[i] = 0;
           }
           
           //bucla exterioara
           for (m = 0 ; m < r ; m ++)
           {
                for(i = 0; i < n; i ++)
                {
                     Sx[i] = Rx[i];
                     Sy[i] = Ry[i];
                }
                for(i = 0 ; i < n ; i ++)
                {
                      /*
                       *  fiecare procesor calculeaza doar partea ce ii revine
                       *  adica acei "i" pentru care i % numtasks == rank
                       */
                      if (i % (numtasks -1) == (rank - 1))
                      {
                            if(i == 0)
                            {
                                b = (int *) malloc (r * sizeof(int));
                                for(j = 0 ; j < r ; j ++)
                                      b[j] = 0;
                            }
                            else

                                b = decimal_to_binary(i);

                            /*
                             * i1 =  b0 ... bm-1 0 bm+1 ... br-1);
                             * i2 =  b0 ... bm-1 1 bm+1 ... br-1);
                             */
                            putere = 1;
                            i1 = 0;
                            i2 = 0;
                            for(j = r - 1; j >= m + 1 ; j --)
                            {

                                  i1 += putere * b[j];
                                  i2 += putere * b[j];
                                  putere = putere << 1;
                            }
                            i2 += putere  * 1;
                            putere = putere << 1;
                            if(m - 1 >= 0)
                            {
                                  for(j = m - 1; j >= 0 ; j--)
                                  {
                                        i1 += putere * b[j];
                                        i2 += putere * b[j];
                                        putere = putere << 1;

                                  }
                            }

                            //i3 = (bm bm-1 ... b0 0 ... 0)
                            i3 = 0;
                            putere = pow(2, r - 1);
                            for (j = 0; j <= m ; j ++)
                            {
                                i3 += putere * b[m-j];
                                putere = putere >> 1;

                            }
                            
                            //Calculez Rx si Ry dupa ce in prealabil am trasformat e^(i*alfa) = cos(alfa) + i * sin(alfa)
                            alfa = (-1) * 2 * PI * i3 / n;

                            Rx[i] = Sx[i1] + Sx[i2] * cos(alfa) - Sy[i2] * sin(alfa);
                            Ry[i] = Sy[i1] + Sx[i2] * sin(alfa) + Sy[i2] * cos(alfa);
                            index = i;

                            //trimit Rx si Ry calculat catre 0 care va trimite mai departe catre celelalte
                            MPI_Send(&index, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
                            MPI_Send(&Rx[i], 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
                            MPI_Send(&Ry[i], 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);

                      }
                }
                //primesc de la 0 actualizarea vectorilor Rx si Ry
                MPI_Recv(&Rx, n, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &Stat);
                MPI_Recv(&Ry, n, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &Stat);

           }
    }
    MPI_Finalize();
}
