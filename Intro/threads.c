#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "common_threads.h"

volatile int counter = 0;
int loops;

/*
The below routine runs for `loops` number of times and for each run it increments the value of counter by 1.
*/
void *worker(void *arg) {
    int i;
    for (i = 0; i < loops; i++) {
        counter++;
    }
    return NULL;
}

/*
We take `loops` as input from user and then print the initial value of `counter` variable. 
Then we create two threads and run the routine `worker` for each thread and then print the final value of `counter`.

The expectation is that if we run the program n times, the value of counter should become 2n. But when we run the program for large value of n, we start seeing 
inconsistencies i.e. final value less than 2n.

This is because the increment operation actually comprises of three different operations which are as below:
    - Load value of counter from memory into register
    - Increment the value
    - Store it back to memory

As this operation is not atomic(Execute all at once), there can be overlapping when two threads try to update the value at same time and hence we see incorrect value for `counter`.
*/
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: threads <value>\n");
        exit(1);
    }
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    printf("Initial value: %d\n", counter);

    Pthread_create(&p1, NULL, worker, NULL);
    Pthread_create(&p2, NULL, worker, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);

    printf("Final value: %d\n", counter);
    return 0;
}