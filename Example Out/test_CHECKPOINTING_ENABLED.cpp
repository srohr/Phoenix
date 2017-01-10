#include <fstream>
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
    err = 100;

{
	ifstream PHOENIX_test_ifstream_var.txt;
	PHOENIX_test_ifstream_var.txt.open("PHOENIX_test\\" + "backup_test_loop_test.txt");
	if (PHOENIX_test_ifstream_var.txt) goto loop_test;
}

    //Checkpoint every iteration
if (false) {
	loop_test:
	#define PHOENIX_LOOP_loop_test
}
    while (err > errMax){
#ifdef PHOENIX_LOOP_loop_test
{
	PHOENIX_testloop_test_ifstream_var.txt.open("PHOENIX_test\\" + "backup_test_loop_test.txt");
	PHOENIX_testloop_test_ifstream_var.txt >> low;
	PHOENIX_testloop_test_ifstream_var.txt >> err;
	PHOENIX_testloop_test_ifstream_var.txt >> high;
	PHOENIX_testloop_test_ifstream_var.txt >> errMax;
	PHOENIX_testloop_test_ifstream_var.txt.close();
}
#undef PHOENIX_LOOP_loop_test
#endif
if (1 == 1) {
{
	PHOENIX_testloop_test_ofstream_var.open("PHOENIX_test\\" + "backup_test_loop_test.txt");
	PHOENIX_testloop_test_ofstream_var << low << endl;
	PHOENIX_testloop_test_ofstream_var << err << endl;
	PHOENIX_testloop_test_ofstream_var << high << endl;
	PHOENIX_testloop_test_ofstream_var << errMax << endl;
	PHOENIX_testloop_test_ofstream_var.close();
}
}
        if (fn(low)*fn(0.5*(high + low)) < 0)
            high = 0.5*(low + high);
        else if (fn(high)*fn(0.5*(high + low)) < 0)
            low = 0.5*(low + high);

        err = high - low;
    }


{
	ifstream PHOENIX_test_ifstream_var.txt;
	PHOENIX_test_ifstream_var.txt.open("PHOENIX_test\\" + "backup_test_final_test.txt");
	if (PHOENIX_test_ifstream_var.txt) goto final_test;
}

    result = 0.5*(high + low);
if (false) {
	final_test:
{
	PHOENIX_testfinal_test_ifstream_var.txt.open("PHOENIX_test\\" + "backup_test_final_test.txt");
	PHOENIX_testfinal_test_ifstream_var.txt >> solution;
	PHOENIX_testfinal_test_ifstream_var.txt >> err;
	PHOENIX_testfinal_test_ifstream_var.txt.close();
}
}
else {
{
	PHOENIX_testfinal_test_ofstream_var.open("PHOENIX_test\\" + "backup_test_final_test.txt");
	PHOENIX_testfinal_test_ofstream_var << solution << endl;
	PHOENIX_testfinal_test_ofstream_var << err << endl;
	PHOENIX_testfinal_test_ofstream_var.close();
}
}
}

    return result;
}
