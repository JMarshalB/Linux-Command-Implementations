//########################################################################
//# Name: Jaylen Brown                                                   #
//# Purpose: The following program does a recurrsive search of all files #
//#    insided the current directory or user specified directory         #
//#    and all sub directories within.                                   #
//########################################################################

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h> 
#include <dirent.h>
#include <string.h>

typedef struct dirent Dir;
typedef struct stat DirInfo;
DirInfo getDirInfo(char* dir) {
    DirInfo dirInfo;
    stat(dir, &dirInfo);
    return dirInfo;
}

//Determines if the current file is a directory
int isDirectory(mode_t mode){
    char fileType;
    switch (mode & S_IFMT) {     
        case S_IFDIR: //File is a directory
            fileType = 'd';
            break;
        
        default: //File is NOT a directory
            fileType = '-';
            break;
    }

    if(fileType == 'd') { return 1; } //TRUE
    else { return 0; } //FALSE
}

//Does the searching of all directories
void recursiveSearch(char* path, char name[]){
    DIR *dir;
    DirInfo dirInfo = getDirInfo(path);

    if(isDirectory(dirInfo.st_mode)){ //Determines if file is directory
        printf("Entering %s Directory:\n", name);
        dir = opendir(path);
        Dir* curr;

        while ((curr = readdir(dir)) != NULL) { //Read through all files in directory
            if (strcmp(curr->d_name,".") == 0) { continue; } //Current directory

            else if (strcmp(curr->d_name,"..") == 0) { continue; } //Parent Directory

            else {
                char path_string[1000] = "";
                strcpy(path_string, path);
                strcat(path_string,"/");
                strcat(path_string,curr->d_name);
                recursiveSearch(path_string, curr->d_name);
            }
        }
        printf("End of %s Directory:\n", name);
        closedir(dir);
    }

    else { printf("  %s\n", name); } //Not a directory

}

int main(int argc, char* argv[]) {
    char* start;

    char path[200];
    if(argc > 1) { 
        start = argv[1]; 
        getcwd(path, 200);
        printf("Current working directory (.): %s/%s\n\n", path, start);
    }
    else { 
        start = ".";
        getcwd(path, 200);
        printf("Current working directory (.): %s\n\n", path);
    }

    recursiveSearch(start, start);
    return 0;
}