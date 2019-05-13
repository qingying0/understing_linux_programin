#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

void do_ls(char* dir_name);
void dostat(char* file_name);
void show_file_info(char* file_name, struct stat* info);
void mode_to_letter(int mode, char* str);
char* uid_to_name(uid_t uid);
char* gid_to_name(gid_t gid);

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
            dostat(direntp->d_name);
        }
        closedir(dir_ptr);
    }
}

void dostat(char* file_name)
{
    struct stat info;
    if(stat(file_name, &info) == -1)
        perror(file_name);
    else 
        show_file_info(file_name, &info);
}

void show_file_info(char* file_name, struct stat* info)
{
    char modestr[11];
    mode_to_letter(info->st_mode, modestr);

    printf("%s", modestr);
    printf("%4d",(int)info->st_nlink);
    printf("%-8s", uid_to_name(info->st_uid));
    printf("%-8s", gid_to_name(info->st_gid));
    printf("%8ld", (long)info->st_size);
    printf("%.12s", 4 + ctime(&info->st_mtime));
    printf("%s\n", file_name);
}

void mode_to_letter(int mode, char* str)
{
    strcpy(str,"----------");
    if(S_ISDIR(mode)) str[0] = 'd';
    if(S_ISCHR(mode)) str[0] = 'c';
    if(S_ISBLK(mode)) str[0] = 'b';

    if(mode & S_IRUSR) str[1] = 'r';
    if(mode & S_IWUSR) str[2] = 'w';
    if(mode & S_IXUSR) str[3] = 'x';

    if(mode & S_IRGRP) str[4] = 'r';
    if(mode & S_IWGRP) str[5] = 'w';
    if(mode & S_IXGRP) str[6] = 'x';


    if(mode & S_IROTH) str[7] = 'r';
    if(mode & S_IWOTH) str[8] = 'w';
    if(mode & S_IXOTH) str[9] = 'x';
}

char* uid_to_name(uid_t uid)
{
    struct passwd* pw_ptr;
    static char numstr[10];

    if((pw_ptr = getpwuid(uid)) == NULL) {
        sprintf(numstr, "%d", uid);
        return numstr;
    } else 
        return pw_ptr->pw_name;
}

char* gid_to_name(gid_t gid)
{
    struct group* grp_ptr;
    static char numstr[10];

    if((grp_ptr = getgrgid(gid)) == NULL) {
        sprintf(numstr, "%d", gid);
        return numstr;
    } else 
        return grp_ptr->gr_name;
}