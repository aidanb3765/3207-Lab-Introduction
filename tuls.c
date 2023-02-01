#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#define MAX_LEN 1000

/* Program is invoked with zero or one argument in the command line

    ^After reviewing the manual for errno, number of last error, I found 
    ENOTDIR which determines that the found error is not a directory.
*/

//Check if the location chosen is really a directory
int isDirectory (char* location)
{
    DIR* directory = opendir(location);     //Pulls the information at the location found

    if(directory != NULL)       //Validates that the directory is not null
    {
        closedir(directory);    //Closes the directory for finding something, returning 1
        return 1;
    }

    else if (errno == ENOTDIR)
    {
        return 0;   //The pulled location is not a directory per the findings of ENOTDIR^
    }

    else
    {
        return -1;
    }
}

//Prints a list of directory information with numbers to keep track
void printDirectory (char* directoryName, int counter)
{
    int findings = isDirectory(directoryName);  //Pulls the found directory

    if (findings != -1)
    {
        if (findings == 1)
        {
            struct dirent **names;
            int num = scandir(directoryName, &names, 0, alphasort);

            if (num == -1)
            {
                perror("Can't open the directory.");
                exit(1);
            }

            while (num--)
            {
                for (int i = 0; i < counter; i++)
                {
                    printf("\t");       //Separates the information to look clean
                }

                printf("%s\n", names[num]->d_name);    //prints the various names of the files
                char fileLocation[MAX_LEN] = "";       //Creates a current file location variable
                strcpy(fileLocation, directoryName);    //Copies a string pointed by the directory name (including the null character) to the file location
                strcat(fileLocation, "/");              //Appends the string pointed to the directory name to the end of the string pointed to the file location
                strcat(fileLocation, names[num]->d_name);  //Appends the string pointed to the file names to the end of the string pointed to the file location

                if(strcmp(names[num]->d_name, ".") != 0 && strcmp(names[num]->d_name, "..") != 0)
                {
                    if(isDirectory(fileLocation) == 1)
                    {
                        printDirectory(fileLocation, counter + 1);
                    }
                }

                free(names[num]);    //Deallocated the memory location for file names pointer
            }

        }

        else
        {
            perror("Directory not found.");
            exit(1);
        }
    }

    else
    {
        perror("Directory not found.");
        exit(1);
    }
}

int main(int argc, char** argv)
{
    if (argv > 2)
    {
        perror("Too many arguments. Can't Continue! \n");
        exit(1);
    }

    else
    {
        if (argc == 1)
        {
            printDirectory(".", 0);     //Prints the general directory
        }

        else
        {
            printDirectory(argv[1], 0);     //Prints the specified directory that's given
        }
    }

}
