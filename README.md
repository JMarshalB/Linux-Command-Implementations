The following programs implement some of the functions that linux has
including "ls", "stat", and "tail". There is also a custom program called
"search" as shown below:

To compile the seperate programs, use the makefile provided or use the following commands:
	gcc -o myls myls-Jaylen.c
	gcc -o mysearch mysearch-Jaylen.c
	gcc -o mystat mystat-Jaylen.c
	gcc -o mytail mytail-Jaylen.c

Each program does the following:
    myls-Jaylen.c:
        Implements the "ls" function in linux, you can specify the
        the directory you want to look at as well as use the -l flag to
        show additional information in each file.
    mystat-Jaylen.c:
        Implements the "stat" function in linux. It will print
        special information about a user specified file in the current
        directory, like the name, size, UID, GID, modified date, etc. 
    mysearch-Jaylen.c:
        The following program does a recurrsive search of all files
        insided the current directory or user specified directory
        and all sub directories within.  
    mytail-Jaylen.c:
        Implements the "tail" function in linux. Reads the last N
        number of lines of a given file. "N" is also specified by
        the user. 