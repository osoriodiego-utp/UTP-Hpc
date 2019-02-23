// Pi calculated with Montecarlo method.
//$ mpicc -std=c++11 mpi.cpp -o mpiExe
//LOCAL: $ ./mpiExe
//CLUSTER: $ mpirun -n X ./mpiExe
// X : number of nodes

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <mpi.h>
#define USE_MPI

using  namespace std;


int main(int argc, char *argv[])
{
   int niter = 0;                     // iteraciones (precision)
   double pi;                         // valor de Pi
   double pointsIn = 0;               // valores que cumplen la condicion x<=1
   double xValue, yValue, distance;   // a, b, hipotenusa
   double start, delta;               // calculo del tiempo

   int i,count=0,mycount;
   int myid,numprocs,proc;
   MPI_Status status;
   int master =0;
   int tag = 123;
   const double factor = 1.0 / RAND_MAX;

   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
   MPI_Comm_rank(MPI_COMM_WORLD,&myid);

   if (argc <=1)
   {
      fprintf(stderr,"Usa: numero de iteraciones\n");
      MPI_Finalize();
      return  (-1);
   }

   sscanf(argv[1],"%d",&niter); /* 1er argumento sera el numero de stacks o iteraciones*/

   start = clock();
   mycount=0;
   for ( i=0; i<niter; i++)
   {
      xValue = rand() * factor;
      yValue = rand() * factor;
      distance = (xValue*xValue) + (yValue*yValue);
      if (distance<=1) 
         mycount++; 
   }


   if (myid ==0)
   { /* si soy el header recolecto la informacion de los workers */
      count = mycount;
      for (proc=1; proc<numprocs; proc++) 
      {
         MPI_Recv(&mycount,1,MPI_REAL,proc,tag,MPI_COMM_WORLD,&status);
         count +=mycount;
      }
      delta = double(clock()-start)/CLOCKS_PER_SEC;

      pi=(double)count/(niter*numprocs)*4;
      printf("\nCalculated points: %d \n",niter);
      printf("Time for{}:  %5.3e \n",delta);    
      printf("The value of PI is: %g \n\n",pi);
   }
   else
   { /* ftodos los workers envian reultados al header */
      printf("Processor %d sending results= %d to master process\n",myid,mycount);
      MPI_Send(&mycount,1,MPI_REAL,master,tag,MPI_COMM_WORLD);
   }

   return 0;
}
