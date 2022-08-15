#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>

/*
Below program creates a file `test`. It does this by making three 
system calls i.e. `open`, 'write` & `close`.
*/
int main(int argc, char *argv[]) {
    int fd = open("test", O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
    assert(fd > -1);
    int rc = write(fd, "hello world\n", 13);
    assert(rc == 13);
    close(fd);
    return 0;
}