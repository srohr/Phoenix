#include <stdio.h>
#include <omp.h>
#include <unistd.h>

using namespace std;

#pragma PHOENIX_VAR {fib} {[values1 4] [values2 4] itr}

int main(){
	long long values1[4] = {0, 3, 6, 9},
	values2[4] = {1, 4, 8, 13};

	
	
	printf("Offset Fibonacci with OpenMP\n");
	printf("----------------------------------------\n");
	printf("%-3s\t%-10s\t%-10s\t%-10s\t%-10s\n", 
	"ITR", "VAL (Thread 0)", "VAL (Thread 1)", "VAL (Thread 2)", "VAL (Thread 3)");
	
	printf("%-3s\t%-10llu\t%-10llu\t%-10llu\t%-10llu\n", 
		"---", values1[0], values1[1], values1[2], values1[3]);

	printf("%-3s\t%-10llu\t%-10llu\t%-10llu\t%-10llu\n", 
		"---", values2[0], values2[1], values2[2], values2[3]);
	
	omp_set_num_threads(4);
	#pragma omp parallel shared(values1, values2)
	{
		int itr = 0;
		int myID = omp_get_thread_num();
		//printf("Hello world from thread #%d!\n", myID);
		#pragma PHOENIX_START fib
		#pragma PHOENIX_PARLOOP fib itr % 5 == 0
		while(itr < 30)
		{
			
			int tmp = values2[myID];
			//printf("Thread %d updating arrays\n", myID);
			values2[myID] += values1[myID];
			values1[myID] = tmp;
			
		
			#pragma omp barrier
			
			#pragma omp single 
			{
				printf("%-3d\t%-10llu\t%-10llu\t%-10llu\t%-10llu\n",
				itr, values2[0], values2[1], values2[2], values2[3]);
				
			}
			
			
			itr++;
			usleep(500000);
		}
	
	}
	
	#pragma PHOENIX_CLEANUP

	return 0;		

}

