#include <stdio.h>
#include <stdlib.h>
#define LINELENGTH 512
#define PAGELENGTH 24

void do_more(FILE* fp);
int see_more(FILE* fp);

int main(int ac, char** av)
{
    FILE* fp;
    if( ac == 1) {
        do_more(stdin);
    } else {
        while( --ac ) {
            if( (fp = fopen(*++av, "r")) != NULL) {
                do_more(fp);
                fclose(fp);
            } else {
                exit(1);
            }
        }
    }
    return 0;
}

void do_more(FILE* fp)
{
    char line[LINELENGTH];
    int num_line = 0;
    int reply;
    FILE* tty = fopen("/dev/tty", "r");
    if(tty == NULL) {
        exit(1);
    } 
    while( fgets(line, LINELENGTH, fp ) != NULL) {
        if( num_line == PAGELENGTH) {
            reply = see_more(tty);
            if(reply == 0) {
                break;
            }
            num_line -= reply;
        }
        if( fputs(line, stdout) == EOF) {
            exit(1); 
        }
        num_line++;
    }    
}

int see_more(FILE* cmd)
{
    int c;
    printf("more?");
    while( (c = getc(cmd)) != EOF) {
        if( c == '\n')
            return 1;
        if( c == ' ')
            return PAGELENGTH;
        if( c == 'q')
            return 0;
    }
    return 0;
}