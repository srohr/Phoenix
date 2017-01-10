#include <fstream>
#include <cstring>
#include <stdlib.h>
bool PHOENIX_Restore_bool = false;
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

{
	system("mkdir -p PHOENIX_example/");
	char PHOENIX_example_arraygen_cstr [100] = "";
	strcat(PHOENIX_example_arraygen_cstr, "PHOENIX_example/");
	strcat(PHOENIX_example_arraygen_cstr, "backup_example_arraygen.txt");
	std::ifstream PHOENIX_example_ifstream_var;
	PHOENIX_example_ifstream_var.open(PHOENIX_example_arraygen_cstr);
	if (PHOENIX_example_ifstream_var) goto arraygen;
}

     //Array initialization for sorting
     t = time(NULL); //Seed for RNG
     srand(t);
     for (int i = 0; i < SIZE; i++){
            arr[i] = rand();
     }
if (false) {
	arraygen:
{
	std::ifstream PHOENIX_examplearraygen_ifstream_var;
	char PHOENIX_example_arraygen_cstr [100] = "";
	strcat(PHOENIX_example_arraygen_cstr, "PHOENIX_example/");
	strcat(PHOENIX_example_arraygen_cstr, "backup_example_arraygen.txt");
	PHOENIX_examplearraygen_ifstream_var.open(PHOENIX_example_arraygen_cstr);
	for(int i = 0; i < 0 + 50000; i++)
		PHOENIX_examplearraygen_ifstream_var >> arr[i];
	PHOENIX_examplearraygen_ifstream_var.close();
}
	;
}
else {
{
	std::ofstream PHOENIX_examplearraygen_ofstream_var;
	char PHOENIX_example_arraygen_cstr [100] = "";
	strcat(PHOENIX_example_arraygen_cstr, "PHOENIX_example/");
	strcat(PHOENIX_example_arraygen_cstr, "backup_example_arraygen.txt");
	PHOENIX_examplearraygen_ofstream_var.open(PHOENIX_example_arraygen_cstr);
	for(int i = 0; i < 0 + 50000; i++)
		PHOENIX_examplearraygen_ofstream_var << arr[i] << std::endl;
	PHOENIX_examplearraygen_ofstream_var.close();
}
}

     printf("Array now generated.\nPress <Enter> to continue...");
     cin.ignore();
     //Bubblesort. Why not?

{
	char PHOENIX_example_bubblesort_cstr [100] = "";
	strcat(PHOENIX_example_bubblesort_cstr, "PHOENIX_example/");
	strcat(PHOENIX_example_bubblesort_cstr, "backup_example_bubblesort.txt");
	std::ifstream PHOENIX_example_ifstream_var;
	PHOENIX_example_ifstream_var.open(PHOENIX_example_bubblesort_cstr);
	if (PHOENIX_example_ifstream_var) goto bubblesort;
}

PHOENIX_Restore_bool = false;
if (false) {
	bubblesort:
	PHOENIX_Restore_bool = true;
}
     while(!done){
if (PHOENIX_Restore_bool){
{
	std::ifstream PHOENIX_examplebubblesort_ifstream_var;
	char PHOENIX_example_bubblesort_cstr [100] = "";
	strcat(PHOENIX_example_bubblesort_cstr, "PHOENIX_example/");
	strcat(PHOENIX_example_bubblesort_cstr, "backup_example_bubblesort.txt");
	PHOENIX_examplebubblesort_ifstream_var.open(PHOENIX_example_bubblesort_cstr);
	PHOENIX_examplebubblesort_ifstream_var >> done;
	PHOENIX_examplebubblesort_ifstream_var >> itr;
	for(int i = 0; i < 0 + 50000; i++)
		PHOENIX_examplebubblesort_ifstream_var >> arr[i];
	PHOENIX_examplebubblesort_ifstream_var.close();
}
	PHOENIX_Restore_bool = false;
}
if (itr%500 == 0) {
{
	std::ofstream PHOENIX_examplebubblesort_ofstream_var;
	char PHOENIX_example_bubblesort_cstr [100] = "";
	strcat(PHOENIX_example_bubblesort_cstr, "PHOENIX_example/");
	strcat(PHOENIX_example_bubblesort_cstr, "backup_example_bubblesort.txt");
	PHOENIX_examplebubblesort_ofstream_var.open(PHOENIX_example_bubblesort_cstr);
	PHOENIX_examplebubblesort_ofstream_var << done << std::endl;
	PHOENIX_examplebubblesort_ofstream_var << itr << std::endl;
	for(int i = 0; i < 0 + 50000; i++)
		PHOENIX_examplebubblesort_ofstream_var << arr[i] << std::endl;
	PHOENIX_examplebubblesort_ofstream_var.close();
}
}
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

{
	char PHOENIX_example_primecheck_cstr [100] = "";
	strcat(PHOENIX_example_primecheck_cstr, "PHOENIX_example/");
	strcat(PHOENIX_example_primecheck_cstr, "backup_example_primecheck_");
	sprintf(PHOENIX_example_primecheck_cstr, "%s%d.txt", PHOENIX_example_primecheck_cstr, omp_get_thread_num());
	std::ifstream PHOENIX_example_ifstream_var;
	PHOENIX_example_ifstream_var.open(PHOENIX_example_primecheck_cstr);
	if (PHOENIX_example_ifstream_var) goto primecheck;
}

PHOENIX_Restore_bool = false;
if (false) {
	primecheck:
	PHOENIX_Restore_bool = true;
}
        for (int j = id*(SIZE/10); j < id*(SIZE/10) + nPerThread; j++)
	{
if (PHOENIX_Restore_bool){
{
	std::ifstream PHOENIX_exampleprimecheck_ifstream_var;
	char PHOENIX_example_primecheck_cstr [100] = "";
	strcat(PHOENIX_example_primecheck_cstr, "PHOENIX_example/");
	strcat(PHOENIX_example_primecheck_cstr, "backup_example_primecheck_");
	sprintf(PHOENIX_example_primecheck_cstr, "%s%d.txt", PHOENIX_example_primecheck_cstr, omp_get_thread_num());
	PHOENIX_exampleprimecheck_ifstream_var.open(PHOENIX_example_primecheck_cstr);
	PHOENIX_exampleprimecheck_ifstream_var >> nPrimes;
	PHOENIX_exampleprimecheck_ifstream_var >> j;
	PHOENIX_exampleprimecheck_ifstream_var.close();
}
	PHOENIX_Restore_bool = false;
}
if (nPrimes%5000 == 0) {
{
	std::ofstream PHOENIX_exampleprimecheck_ofstream_var;
	char PHOENIX_example_primecheck_cstr [100] = "";
	strcat(PHOENIX_example_primecheck_cstr, "PHOENIX_example/");
	strcat(PHOENIX_example_primecheck_cstr, "backup_example_primecheck_");
	sprintf(PHOENIX_example_primecheck_cstr, "%s%d.txt", PHOENIX_example_primecheck_cstr, omp_get_thread_num());
	PHOENIX_exampleprimecheck_ofstream_var.open(PHOENIX_example_primecheck_cstr);
	PHOENIX_exampleprimecheck_ofstream_var << nPrimes << std::endl;
	PHOENIX_exampleprimecheck_ofstream_var << j << std::endl;
	PHOENIX_exampleprimecheck_ofstream_var.close();
}
}

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
