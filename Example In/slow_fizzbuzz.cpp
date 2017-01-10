#include <iostream>
#include <unistd.h>

using namespace std;

int main(){
    #pragma PHOENIX_VAR {checkpoint1} {i}
    #pragma PHOENIX_START checkpoint1
    #pragma PHOENIX_LOOP checkpoint1 i % 3 == 0
    for (int i = 1; i < 200; i++){
        cout << i << ": ";
        if (i%3 == 0)
            cout << "fizz";
        if (i%5 == 0)
            cout << "buzz";
        cout << endl;

        usleep(1000000);
    }
    return 0;
}