#include<stdio.h>
#include"terminal.h"

int main()
{
    /* Normally, when you use scanf(), the program pauses until you press "Enter" key.
       In this demo, you will use pre-written functions to make the program accept
       a single char immediately without the need to press "Enter" key. */

    /* First, let's see the example of typical usage of scanf() on a single char. */

    char ch;
    int ii;

    printf("Please enter a character : ");
    scanf(" %c", &ch);  /* Note: A single space before %c is needed to clear the input stream from white spaces */   
    printf("you just entered %c\n\n\n", ch);


    
    
    /* Now, let us try using the functions to make the program to accept the single char immediately */

    printf("Please enter a character : ");

    disableBuffer();   /* <-- Call this just before scanf() function */
    scanf(" %c", &ch);
    enableBuffer();    /* <-- Call this after scanf() function to resume default behaviour */

    printf("--> %c <--\n\n\n", ch);



    /* You can also try it in the loop as well */

    printf("Please type any character\n");
    for(ii = 0 ; ii < 100 ; ii++)
    {
        disableBuffer();
        scanf(" %c", &ch);
        enableBuffer();

        printf("you just entered --> %c\n", ch);          
    }

    return 0;
}