// Pi calculated with Montecarlo method.
//$ g++ -std=c++11 omp.cpp -o openmp
//$ ./ompExe


#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <cmath>
#include <omp.h>

using namespace std;

 
int main() 
{ 
   // puntos a evaluar (precisión)
   vector<long> totalpoints = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000,
                              1000000, 5000000, 10000000, 50000000, 100000000};
   vector<short int> hilos = {1, 2, 3, 4, 5, 6};

   for(int k=0; k<hilos.size(); k++)
   {
      for (int j=0; j<totalpoints.size(); j++)
      {
         double pi;                         // valor de Pi
         double pointsIn = 0;               // valores que cumplen la condicion x<=1
         double xValue, yValue, distance;   // a, b, hipotenusa
         double start, delta;               // calculo del tiempo
         

         start = clock();
         #pragma omp parallel num_threads(hilos[k])
         {
            #pragma omp for private(xValue, yValue) reduction(+:distance, pointsIn)
            for(int i=0; i<totalpoints[j]; i++)
            { 
               xValue = (double) rand()/RAND_MAX; //Random point: x 
               yValue = (double) rand()/RAND_MAX; //Random point: y
               #pragma omp critical
               distance = (xValue * xValue) + (yValue * yValue); // |
               distance = sqrt(distance);                        // | hipotenusa = distancia
               if(distance <= 1) 
                  pointsIn++; 
            }            
         }
         delta = double(clock()-start)/CLOCKS_PER_SEC;
            
         pi = 4 * pointsIn/totalpoints[j];
         cout<<"Used threads: "<<hilos[k]<<endl;
         cout<<"Calculated points: "<<totalpoints[j]<<endl;
         cout<<"Time For{}: "<<delta<<endl;
         cout<<"The vaule of PI is: " << pi <<"\n"<<endl;       
      }
   }
      
   return 0; 
} 