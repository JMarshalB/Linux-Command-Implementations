//########################################################################
//# Name: Jaylen Brown                                                   #
//# Purpose: Implements the "stat" function in linux. It will print      #
//#     special information about a user specified file in the current   #
//#     directory, like the name, size, UID, GID, modified date, etc.    #
//########################################################################

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

typedef struct dirent Dir;
typedef struct stat DirInfo;
DirInfo getDirInfo(char* dir) {
    DirInfo dirInfo;
    stat(dir, &dirInfo);
    return dirInfo;
}

int main(int argc, char *argv[]) {
    char* name;
    if(argc > 1)
        name = argv[1];
    char *permissions = malloc(sizeof(char) * 9 + 1);
    char fileType;

    DIR* rootDir = opendir(".");
    Dir* dir = readdir(rootDir);

    //Prints out all files in current directory
    for(; dir != NULL; dir = readdir(rootDir)){
        if(strcmp(name, dir->d_name) == 0){ //If user specified name is found
            printf("Here are the stats of %s: \n", name);
            printf("-------------------------------\n");
            DirInfo dirInfo = getDirInfo(dir->d_name); 
            printf("File Size: %ld Bytes\n", dirInfo.st_size);
            printf("Number of Blocks Allocated: %ld\n", dirInfo.st_blocks);
            printf("Number of Links: %ld\n", dirInfo.st_nlink);
            
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

            //This gets the set of permission for each group
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

            printf("File Permissions: %c%s\n", fileType, permissions);
            printf("File Inode: %ld\n", dirInfo.st_ino);
        }
    }

    closedir(rootDir); return 0;
}