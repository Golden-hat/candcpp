#include <iostream>
#include <time.h>

using namespace std;

int main(){
    /*
        Things aren't really random in a computer.

        We need to create a seed based on time in order to generate
        a random pattern with each execution.

        time(0) provides the number of seconds elapsed since 1970, and
        srand uses the input seed to generate a new random pattern for
        the rand function.

        Without this, rand() will always provide the same result regardless
        of how many times the program is executed.
    */
    srand(time(0));

    for(int i = 0; i < 10; i++){
        /*
            rand() function invokes a random number between 0 and the
            RAND_MAX value defined in the cstdlib library.

            Moduloing is done to get the interval between 0 and n-1 that we
            desire randomized.
        */
        cout << (rand()%6) << endl;
    }
    return 0;
}