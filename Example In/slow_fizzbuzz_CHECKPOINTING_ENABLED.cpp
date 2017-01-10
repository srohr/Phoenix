#include <fstream>
#include <cstring>
#include <stdlib.h>
bool PHOENIX_Restore_bool = false;
#include <iostream>
#include <unistd.h>
using namespace std;
int main(){

{
	system("mkdir -p PHOENIX_slow_fizzbuzz/");
	char PHOENIX_slow_fizzbuzz_checkpoint1_cstr [100] = "";
	strcat(PHOENIX_slow_fizzbuzz_checkpoint1_cstr, "PHOENIX_slow_fizzbuzz/");
	strcat(PHOENIX_slow_fizzbuzz_checkpoint1_cstr, "backup_slow_fizzbuzz_checkpoint1.txt");
	ifstream PHOENIX_slow_fizzbuzz_ifstream_var;
	PHOENIX_slow_fizzbuzz_ifstream_var.open(PHOENIX_slow_fizzbuzz_checkpoint1_cstr);
	if (PHOENIX_slow_fizzbuzz_ifstream_var) goto checkpoint1;
}

if (false) {
	checkpoint1:
	PHOENIX_Restore_bool = true;
}
    for (int i = 1; i < 200; i++){
{
if (PHOENIX_Restore_bool){
{
	ifstream PHOENIX_slow_fizzbuzzcheckpoint1_ifstream_var;
	char PHOENIX_slow_fizzbuzz_checkpoint1_cstr [100] = "";
	strcat(PHOENIX_slow_fizzbuzz_checkpoint1_cstr, "PHOENIX_slow_fizzbuzz/");
	strcat(PHOENIX_slow_fizzbuzz_checkpoint1_cstr, "backup_slow_fizzbuzz_checkpoint1.txt");
	PHOENIX_slow_fizzbuzzcheckpoint1_ifstream_var.open(PHOENIX_slow_fizzbuzz_checkpoint1_cstr);
	PHOENIX_slow_fizzbuzzcheckpoint1_ifstream_var >> i;
	PHOENIX_slow_fizzbuzzcheckpoint1_ifstream_var.close();
}
	PHOENIX_Restore_bool = false;
}
}
if (i % 3 == 0) {
{
	ofstream PHOENIX_slow_fizzbuzzcheckpoint1_ofstream_var;
	char PHOENIX_slow_fizzbuzz_checkpoint1_cstr [100] = "";
	strcat(PHOENIX_slow_fizzbuzz_checkpoint1_cstr, "PHOENIX_slow_fizzbuzz/");
	strcat(PHOENIX_slow_fizzbuzz_checkpoint1_cstr, "backup_slow_fizzbuzz_checkpoint1.txt");
	PHOENIX_slow_fizzbuzzcheckpoint1_ofstream_var.open(PHOENIX_slow_fizzbuzz_checkpoint1_cstr);
	PHOENIX_slow_fizzbuzzcheckpoint1_ofstream_var << i << endl;
	PHOENIX_slow_fizzbuzzcheckpoint1_ofstream_var.close();
}
}
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
