#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <stdlib.h>
#include <time.h>

void show_info(struct utmp* utmpfd);
char* show_time(long timeval);
int main()
{
    struct utmp current_utmp;
    int utmpfd;
    int utmp_size = sizeof(current_utmp);

    if( (utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
        perror(UTMP_FILE);
        exit(1);
    }
    while( (read(utmpfd, &current_utmp, utmp_size))) {
        show_info(&current_utmp);
    }
    close(utmpfd);
    return 0;
}


void show_info(struct utmp* utmpbuf)
{
    printf("%-8.8s", utmpbuf->ut_user);
    printf(" ");
    printf("%-8.8s", utmpbuf->ut_line);
    printf(" ");
    show_time(utmpbuf->ut_tv.tv_sec);
    printf(" ");
#ifndef SHOWHOST
    printf("%s", utmpbuf->ut_host);
#endif
    printf("\n");
}

char* show_time(long timeval)
{
    char* cp;
    cp = ctime(&timeval);
    printf("%12.12s", cp + 4);
}