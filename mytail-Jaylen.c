//########################################################################
//# Name: Jaylen Brown                                                   #
//# Purpose: Implements the "tail" function in linux. Reads the last N   #
//#     number of lines of a given file. "N" is also specified by        #
//#     the user.                                                        #      
//########################################################################

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>  
#include <dirent.h>  
#include <string.h>    
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    FILE* file;
    int n = 0;
    int lines = 0;
    char c;
    char* name;

    //Check if number of lines is in first argument
    if (argc > 1){
        char* str;
        str = argv[1];
        n = atoi(str);
    } 
    else {
        printf("Please run program in the following format: \"./a.out (lines) (fileName)\"\n");
        exit(EXIT_FAILURE);
    }

    //Check if file name is in second arguement
    if (argc > 2){
        name = argv[2];
        file = fopen(name, "r");
        if(file == NULL) {
            printf("File \"%s\" does not exist\n", name);
            printf("Please ensure you are using the format: \"./a.out (lines) (fileName)\"\n");
            exit(EXIT_FAILURE);
        }
    }
    else{
        printf("Please run program in the following format: \"./a.out (lines) (fileName)\"\n");
        exit(EXIT_FAILURE);
    }

    //Go through file to find number of lines
    while(c != EOF){
        c = getc(file);
        if(c == '\n'){
            lines++; 
        }
    }

    fseek(file, 0, SEEK_SET); //Restart at beginning

    //Go through file again to find the line we want to start printing from
    int i = 0;
    while (i < lines - n){
        c = getc(file);
        if(c == '\n'){
            i++;
        }
    }

    //Begin printing N number of lines
    c = getc(file);
    while (c != EOF){
        printf("%c", c);  
        c = getc(file);
    }

    fclose(file); return 0;

}