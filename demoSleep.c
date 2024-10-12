#include<stdio.h>
#include<unistd.h>   /* <-- library for the sleep() function */
#include"newSleep.h"

int main()
{
    /* This demonstration will show you how to make the program suspend/sleeps for any amount of seconds. */

    int ii;


    /* The simplest way is to use sleep() function from <unistd.h> (Universal Standard Header) */

    printf("before sleeping for 3 seconds\n");
    sleep(3); /* 3 seconds sleep */
    printf("after sleeping for 3 seconds");

    /* However, sleep() function is restricted to integer parameter. It means it cannot sleep for 
       fraction of a seconds. For example, 0.3 seconds. */


    /* The more flexible version is to use a system call nanosleep() which allows
       high-level precision on program suspension.
       We have provided pre-written wrapping function called newSleep() function that will use
       nanosleep system call. You only need to pass the amount of seconds as float. */   

    for( ii=0 ; ii<100 ; ii++ )
    {
        printf("%d\n", ii);
        newSleep(0.1);      /* <-- Please try different numbers (in seconds) to see the effect. */
    }


    return 0;
}