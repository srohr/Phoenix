#include <fstream>
#include <cstring>
#include <stdlib.h>
bool PHOENIX_Restore_bool = false;
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#define THREADS 8
/* the function called for each thread */
void worker(int n) {
  /* get our thread id */
  int id = omp_get_thread_num( );
  #pragma omp ordered
  printf("Thread %d says hello (%d)!\n", id, n);
}
int main ( ) {
  int i;

{
	system("mkdir -p PHOENIX_omp_test/");
	char PHOENIX_omp_test_partest_cstr [100] = "";
	strcat(PHOENIX_omp_test_partest_cstr, "PHOENIX_omp_test/");
	strcat(PHOENIX_omp_test_partest_cstr, "backup_omp_test_partest_");
	sprintf(PHOENIX_omp_test_partest_cstr, "%s_%d.txt", PHOENIX_omp_test_partest_cstr, omp_get_thread_num());
	std::ifstream PHOENIX_omp_test_ifstream_var;
	PHOENIX_omp_test_ifstream_var.open(PHOENIX_omp_test_partest_cstr);
	if (PHOENIX_omp_test_ifstream_var) goto partest;
}

PHOENIX_Restore_bool = false;
if (false) {
	partest:
	PHOENIX_Restore_bool = true;
}
  #pragma omp parallel for num_threads(THREADS) ordered private(PHOENIX_Restore_bool)
  for (i = 0; i < 250000; i++) {
if (PHOENIX_Restore_bool){
{
	std::ifstream PHOENIX_omp_testpartest_ifstream_var;
	char PHOENIX_omp_test_partest_cstr [100] = "";
	strcat(PHOENIX_omp_test_partest_cstr, "PHOENIX_omp_test/");
	strcat(PHOENIX_omp_test_partest_cstr, "backup_omp_test_partest_");
	sprintf(PHOENIX_omp_test_partest_cstr, "%s_%d.txt", PHOENIX_omp_test_partest_cstr, omp_get_thread_num());
	PHOENIX_omp_testpartest_ifstream_var.open(PHOENIX_omp_test_partest_cstr);
	PHOENIX_omp_testpartest_ifstream_var >> i;
	PHOENIX_omp_testpartest_ifstream_var.close();
}
	PHOENIX_Restore_bool = false;
}
if (i%50 == 2) {
{
	std::ofstream PHOENIX_omp_testpartest_ofstream_var;
	char PHOENIX_omp_test_partest_cstr [100] = "";
	strcat(PHOENIX_omp_test_partest_cstr, "PHOENIX_omp_test/");
	strcat(PHOENIX_omp_test_partest_cstr, "backup_omp_test_partest_");
	sprintf(PHOENIX_omp_test_partest_cstr, "%s_%d.txt", PHOENIX_omp_test_partest_cstr, omp_get_thread_num());
	PHOENIX_omp_testpartest_ofstream_var.open(PHOENIX_omp_test_partest_cstr);
	PHOENIX_omp_testpartest_ofstream_var << i << std::endl;
	PHOENIX_omp_testpartest_ofstream_var.close();
}
}
     worker(i);
  }

  return 0;
}
