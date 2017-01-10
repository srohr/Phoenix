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
        #pragma PHOENIX_VAR {ckp1} {sum [arr 20]}
        #pragma PHOENIX_START ckp1



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

        #pragma PHOENIX_OMP ckp1
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