#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

/*
The program allocates some memory using malloc() to an integer. 
It then prints the memory address for that integer. Then it puts number 0 in first slot of the memory.
Then it loops indefinitely doing three things for each run:
 - Waits for 1 second using Spin().
 - Increments the value for the integer.
 - Prints the process id where the program is running along with the value of integer.
*/
int main(int argc, char* argv[]) {
    int *p = malloc(sizeof(int));
    assert(p != NULL);
    printf("(%d) address pointed to by p: %p\n", getpid(), p);
    *p = 0;
    while (1) {
        Spin(1);
        *p = *p + 1;
        printf("(%d) p: %d\n", getpid(), *p);
    }
    return 0;
} 