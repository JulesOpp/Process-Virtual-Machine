// Jules Oppenheim and James Spann
// March 14, 2014
// Process Virtual Machine

#include <stdio.h>
#include <string.h>
#include "middle.h"

char *filename;

void printversion()
{
    printf("Version 1.0\n");
}

void help()
{
    printf("\nAvailable commands\n");
    printf("=================\n");
    printf("-v for version\n");
    printf("-R for running a file\n");
    printf("-? for this screen\n\n");
}


int main (int argc, char *argv[]) {
    if (argv[1] == NULL)
    {
        help();
    } 
    else
    {
        if(strcmp(argv[1],"-v")==0)
        {
            printversion();
        }
        else if(strcmp(argv[1],"-R")==0)
        {
            filename=argv[2];
            
            FILE *fp = fopen(filename,"r");
            if( fp )                               //Checking if the file exists
            {           
                fclose(fp);
                execute(filename);            //Since the file exists the lexical Analysis can Begin
            } 
            else 
            {
                printf("The file doesn't exist. Make sure you have titled it correctly. \n");
            }
        }
        else if(strcmp(argv[1],"-?")==0)
        {
            help();
        }
        else
        {
            printf("Invalid command. Please enter -? for available commands.\n");
        }
    }
    return 0;
}