#include<stdio.h>
#include"random.h"

int main()
{
    int ii;
    int min = 3;
    int max = 99; /* <-- experiment with different numbers */

    /* In C library, there is a function that can be used to generate random integer. The details will
       be explained on the last lecture "Miscellaneous C". In this demonstration, we will show you how
       to use the random number generator without knowing the details. */

    /* Please have a look at the functions in random.c. There are two functions:
       initRandom() and randomUCP() */

    /* Before you use the random number generator, you need to call the initRandom() just once around the
       beginning of your program. (most likely main function). */

    initRandom();

    /* Once you called the initRandom, you can call randomUCP() to get random number based on given parameters*/

    for( ii=0 ; ii<10 ; ii++)
    {
        printf("random number --> %d\n", randomUCP(min, max));
    }         

    /* Try running the program multiple times, and you will always get random number sequence. */

    return 0;
}