#include <fstream>
#include <cstring>
#include <stdlib.h>
bool PHOENIX_Restore_bool = false;
#include <iostream>
#include <omp.h>
using namespace std;
int main (){
    const int ARRSIZE = 20;
    int arr [ARRSIZE] = {1, 0, 6, 32, 4, -17, 2, 4, -5, 99, 23, 45, 7, 15, 88, -9, 3, -85, 23, 47};
    cout << "The array: {" << arr[0];
    for (int i = 1; i < 20; i++){
        cout << ", " << arr[i];
    }
    cout << "}" << endl;
    #pragma omp parallel num_threads(10) shared(arr)
    {
        int sum = 0;
        int stride = 1;

{
	system("mkdir -p PHOENIX_test_parallel_region/");
	char PHOENIX_test_parallel_region_ckp1_cstr [100] = "";
	strcat(PHOENIX_test_parallel_region_ckp1_cstr, "PHOENIX_test_parallel_region/");
	strcat(PHOENIX_test_parallel_region_ckp1_cstr, "backup_test_parallel_region_ckp1_");
	sprintf(PHOENIX_test_parallel_region_ckp1_cstr, "%s%d.txt", PHOENIX_test_parallel_region_ckp1_cstr, omp_get_thread_num());
	std::ifstream PHOENIX_test_parallel_region_ifstream_var;
	PHOENIX_test_parallel_region_ifstream_var.open(PHOENIX_test_parallel_region_ckp1_cstr);
	if (PHOENIX_test_parallel_region_ifstream_var) goto ckp1;
}

        for (int j = 0; j< 15; j++){
            if (2*omp_get_thread_num()*stride + stride < ARRSIZE)
                arr[2*omp_get_thread_num()*stride] += arr[2*omp_get_thread_num()*stride + stride];
            if (omp_get_thread_num() == 0){
                cout << "Iteration #" << j << ": The array = {" << arr[0];
                for (int i = 1; i < 20; i++){
                    cout << ", " << arr[i];
                }
                cout << "}" << endl;
            }
            stride *= 2;
            #pragma omp barrier
        }
if (false) {
	ckp1:
{
	std::ifstream PHOENIX_test_parallel_regionckp1_ifstream_var;
	char PHOENIX_test_parallel_region_ckp1_cstr [100] = "";
	strcat(PHOENIX_test_parallel_region_ckp1_cstr, "PHOENIX_test_parallel_region/");
	strcat(PHOENIX_test_parallel_region_ckp1_cstr, "backup_test_parallel_region_ckp1_");
	sprintf(PHOENIX_test_parallel_region_ckp1_cstr, "%s%d.txt", PHOENIX_test_parallel_region_ckp1_cstr, omp_get_thread_num());
	PHOENIX_test_parallel_regionckp1_ifstream_var.open(PHOENIX_test_parallel_region_ckp1_cstr);
	PHOENIX_test_parallel_regionckp1_ifstream_var >> sum;
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[0];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[1];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[2];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[3];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[4];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[5];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[6];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[7];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[8];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[9];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[10];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[11];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[12];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[13];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[14];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[15];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[16];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[17];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[18];
	PHOENIX_test_parallel_regionckp1_ifstream_var >> arr[19];
	PHOENIX_test_parallel_regionckp1_ifstream_var.close();
}
	;
}
else {
{
	std::ofstream PHOENIX_test_parallel_regionckp1_ofstream_var;
	char PHOENIX_test_parallel_region_ckp1_cstr [100] = "";
	strcat(PHOENIX_test_parallel_region_ckp1_cstr, "PHOENIX_test_parallel_region/");
	strcat(PHOENIX_test_parallel_region_ckp1_cstr, "backup_test_parallel_region_ckp1_");
	sprintf(PHOENIX_test_parallel_region_ckp1_cstr, "%s%d.txt", PHOENIX_test_parallel_region_ckp1_cstr, omp_get_thread_num());
	PHOENIX_test_parallel_regionckp1_ofstream_var.open(PHOENIX_test_parallel_region_ckp1_cstr);
	PHOENIX_test_parallel_regionckp1_ofstream_var << sum << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[0] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[1] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[2] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[3] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[4] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[5] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[6] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[7] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[8] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[9] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[10] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[11] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[12] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[13] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[14] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[15] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[16] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[17] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[18] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var << arr[19] << std::endl;
	PHOENIX_test_parallel_regionckp1_ofstream_var.close();
}
}

        sum = arr[0];
        if (omp_get_thread_num() == 0){
            cout << "The array: {" << arr[0];
            for (int i = 1; i < 20; i++){
                cout << ", " << arr[i];
            }
            cout << "}" << endl;
            cout << "Sum of array is = " << sum << endl;
        }
    }
    return 0;
}
