#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <ctype.h>
#include <stdbool.h>


int main(int argc, char *argv[])
{
  
    /* continue with program logic here */

    int number = atoi(argv[1]);


  
        int i = 2;

        while (i <= number){

            if (i % 2 == 0) { 
                printf("\t%d\n", i);
            }

            i+= 2;
        }

    


    return 0;

}




