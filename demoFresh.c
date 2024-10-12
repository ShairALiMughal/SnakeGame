#include<stdio.h>
#include<stdlib.h>
#include"newSleep.h"

int main()
{
    int ii;

    /* This demo shows on how to print any content on the terminal while maintaining fresh look everytime.
       Please make sure you have understood how to make the program sleep before continuing any further. */


    /* First, let us try to run the following code segment: */

    for( ii=0 ; ii < 10 ; ii++ )
    {
        printf("ii --> %d\n", ii);
        newSleep(1.25);
    }

    /* As expected, this quickly fill the terminal and force it to scroll down. */



    /* What if we want to print the number on the first line/row of the terminal consistently? 
       One way to achieve this is by "clearing" the terminal screen everytime before printing it.
       This can be achieved by calling the system() function ( from <stdlib.h> )
       and we pass the command "clear" */

    for( ii=0 ; ii < 10 ; ii++ )
    {
        system("clear");
        printf("ii --> %d\n", ii);
        newSleep(1.25);
    }   

    /* You can use system("clear") for the assignment that requires fresh screen each time you print
       anything on terminal. (e.g user interface) */




    /* (OPTIONAL SEGMENT)
       You might have noticed that using system("clear") rapidly might show blinking effect due to quick
       erasing and printing. (This might or might not happen depending on your system specification).
       This blinking effect will NOT negatively impact your assignment. However, some people might prefer
       to avoid this blinking in their program.
       
       The alternative way to refresh the screen without blinking is by manually moving the terminal cursor.
       The idea is to re-position the terminal cursor back to the top left position and re-print the whole
       interface. By doing this, erasing the screen is not necessary anymore since the re-printing will
       overwrite the previous interface, hence eliminating the blinking effect.

       In order to do this, you have to use the command tput on the terminal shell. ( i.e system("tput") )
       Normally, this command should be pre-installed in Linux environment. If for any reason your system
       does not have it, please install the package with "sudo apt install ncurses-bin"    */


    system("clear");        /* <-- we still do one "clear" to start with empty terminal screen*/
    for( ii=0 ; ii < 10 ; ii++ )
    {
        system("tput cup 0 0");    /* This command moves the cursor to top left corner */
        printf("ii --> %d\n", ii);
        newSleep(1.25);
    }    


    /* Once again, it is not necessary to use tput() function for your assignment, but it can
       make the final result looks more satisfying without the blinking effect. */   

    return 0;
}