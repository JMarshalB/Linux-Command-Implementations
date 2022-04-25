//########################################################################
//# Name: Jaylen Brown                                                   #
//# Purpose: Implements the "ls" function in linux, you can specify the  #
//#    the directory you want to look at as well as use the -l flag to   #
//#    show additional information in each file.                         #
//########################################################################

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

typedef struct dirent Dir;
typedef struct stat DirInfo;
DirInfo getDirInfo(char* dir) {
    DirInfo dirInfo;
    stat(dir, &dirInfo);
    return dirInfo;
}

int main(int argc, char* argv[]){
    DIR* rootDir;
    char* name;
    char *permissions = malloc(sizeof(char) * 9 + 1);
    char fileType;

    if(argc > 2){ //User specifies directory
        name = argv[2];
        rootDir = opendir(name);
    }
    else
        rootDir = opendir(".");

    Dir* dir = readdir(rootDir);


    for(; dir != NULL; dir = readdir(rootDir)){ //Read through all files in directory
        if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) { continue; } //Skip the current directory file and parent directory file
        
        //This gets the set of permission for each group
        DirInfo dirInfo = getDirInfo(dir->d_name);
        permissions[0] = (dirInfo.st_mode & S_IRUSR) ? 'r' : '-';
        permissions[1] = (dirInfo.st_mode & S_IWUSR) ? 'w' : '-';
        permissions[2] = (dirInfo.st_mode & S_IXUSR) ? 'x' : '-';
        permissions[3] = (dirInfo.st_mode & S_IRGRP) ? 'r' : '-';
        permissions[4] = (dirInfo.st_mode & S_IWGRP) ? 'w' : '-';
        permissions[5] = (dirInfo.st_mode & S_IXGRP) ? 'x' : '-';
        permissions[6] = (dirInfo.st_mode & S_IROTH) ? 'r' : '-';
        permissions[7] = (dirInfo.st_mode & S_IWOTH) ? 'w' : '-';
        permissions[8] = (dirInfo.st_mode & S_IXOTH) ? 'x' : '-';
        permissions[9] = '\0';

        //Determines if file is a directory, link, or "other" file
        switch (dirInfo.st_mode & S_IFMT) {
            case S_IFLNK:
                fileType = 'i';
                break;
            
            case S_IFDIR:
                fileType = 'd';
                break;
            
            default:
                fileType = '-';
                break;
        }
        
        //If -l flag is used, print additional information
        if(argc > 1){
            if(strcmp(argv[1], "-l") == 0)
                printf("File:%s  Permissions:%c%s NLINKS:%ld UID:%d GID:%d SIZE:%ld Time:%s\n", dir->d_name, fileType, permissions, dirInfo.st_nlink, dirInfo.st_uid, dirInfo.st_gid, dirInfo.st_size, ctime(&dirInfo.st_ctime));
            else
                printf("%s\n", dir->d_name);
        }
        else
            printf("%s\n", dir->d_name);
    }

    closedir(rootDir); return 0;
}
