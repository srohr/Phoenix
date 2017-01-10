#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

using namespace std;

double fsqrt(double guess, double val){
    return (val/guess) - guess;
}

bool isPrime(int x){
    for (int i = 2; i*i < x; i++){
        if (x%i == 0)
        return false;
    }
    return true;
}

int main(){
    //Stuff for array generation
    long t;

    //Stuff for sorting example
    const int SIZE = 50000;
    int arr [SIZE];
    bool done = false;
    int itr = 0;

    //For parallel
    int nPerThread, nPrimes = 0;


    #pragma PHOENIX_VAR {arraygen} {[arr 50000]}
    #pragma PHOENIX_START arraygen
     //Array initialization for sorting
     t = time(NULL); //Seed for RNG
     srand(t);

     for (int i = 0; i < SIZE; i++){
            arr[i] = rand();
     }
     #pragma PHOENIX_CHECKPOINT arraygen

     printf("Array now generated.\nPress <Enter> to continue...");
     cin.ignore();

     //Bubblesort. Why not?
     #pragma PHOENIX_VAR {bubblesort} {[arr 50000] done itr}
     #pragma PHOENIX_START bubblesort
     #pragma PHOENIX_LOOP bubblesort itr%500 == 0
     while(!done){
        done = true;
        for (int i = 0; i < SIZE - 1; i++){
            if (arr[i] < arr[i + 1]){
                int tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                done = false;
            }
        }
        itr++;
        if (itr % 1000 == 0)
            cout << "Sorting, iteration #" << itr << endl;
     }

     printf("Array now sorted.\nPress <Enter> to continue...");
     cin.ignore();


     cout << "Find all primes 1 - 1,000,000" << endl;
     nPerThread = 1000000/10;

    cout << "Number found: \n";
     #pragma omp parallel num_threads(10) shared (nPrimes)
     {
        int stride = 1;
        int id = omp_get_thread_num();

        #pragma PHOENIX_VAR {primecheck} {j nPrimes}
        #pragma PHOENIX_START primecheck
        #pragma PHOENIX_PARLOOP primecheck nPrimes%5000 == 0
        for (int j = id*(SIZE/10); j < id*(SIZE/10) + nPerThread; j++)
        {
            if (isPrime(j + 1))
            {
                #pragma omp critical
                {
                    nPrimes++;
                    if (nPrimes % 5000 == 0)
                        printf("%d...\n", nPrimes);
                }
            }
        }
     }

    cout << "\nThere are " << nPrimes << " between 1 and 1,000,000\n";

}