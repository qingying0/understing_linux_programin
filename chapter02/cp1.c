#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFERSIZE 4096
#define OOPYMODE 0644

void oops(char* s1, char* s2);

int main(int ac, char** av)
{
    int in_fd, out_fd;
    int num_char;
    char buf[BUFFERSIZE];

    if(ac != 3) {
        fprintf(stderr, "error number argv");
        exit(0);
    } 

    if( (in_fd = open(av[1], O_RDONLY)) == -1 ) {
        oops("open error", av[1]);
    }   

    if( (out_fd = creat(av[2], OOPYMODE)) == -1 ) {
        oops("write error", av[1]);
    } 

    while( (num_char = (read(in_fd, buf, BUFFERSIZE))) > 0 ) {
        if( (write(out_fd, buf, num_char)!= num_char)) {
            oops("write error", av[2]);
        }
    }

    if( num_char == -1 ) {
        oops("read error from", av[1]);
    }

    if( close(in_fd) == -1 | close(out_fd) == -1) {
        oops("close error files", "");
    }

    return 0;
}


void oops(char* s1, char* s2)
{
    fprintf(stderr, "%s", s1);
    perror(s2);
    exit(1);
}