#include <iostream>
#include <cmath>

using namespace std;


double fn(double x){
    return 19 - x*x;
}

int main(){
    double low = 0,
        high = 19,
        errMax = 0.01
        err;
    double solution;

    #pragma PHOENIX_VAR {loop_test} {low high err errMax}
    #pragma PHOENIX_VAR {final_test} {solution err}

    err = 100;

    #pragma PHOENIX_START loop_test

    //Checkpoint every iteration
    #pragma PHOENIX_LOOP loop_test 1 == 1
    while (err > errMax){
        if (fn(low)*fn(0.5*(high + low)) < 0)
            high = 0.5*(low + high);
        else if (fn(high)*fn(0.5*(high + low)) < 0)
            low = 0.5*(low + high);

        err = high - low;
    }

    #pragma PHOENIX_START final_test
    result = 0.5*(high + low);

    #pragma PHOENIX_CHECKPOINT final_test
    return result;

}
