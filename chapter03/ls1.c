#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

void do_ls(char*);

int main(int ac, char* av[])
{
     if( ac == 1) {
         do_ls(".");
    } else {
         while(--ac) {
            printf("%s", *++av);
            do_ls(*av);
        }
    }
    return 0;
}

void do_ls(char* dir_name)
{
    DIR* dir_ptr;
    struct dirent* direntp;
    if( (dir_ptr = opendir(dir_name)) == NULL ) {
        fprintf(stderr, "ls1, cann't open %s", dir_name); 
    } else {
        while( (direntp = readdir(dir_ptr)) != NULL) {
            printf("test\n");
            printf("%s\n", direntp->d_name);
        }
        closedir(dir_ptr);
    }
}