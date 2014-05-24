#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "middle.h"
#include "Table.h"

///Users/jules/Library/Developer/Xcode/DerivedData/ProcessVirtualMachine_Mach_1-guybfjwskbxlutevmkslqkiexicp/Build/Products/Debug/ProcessVirtualMachine\ Mach\ 1  -R /Users/jules/Desktop/testit.txt ;

// Operands                                                 Parameters              Unique Code
// DEF - Use symbol table to store title, type, value       2 - Title, value		1
// ADD - Takes two integer params and adds them             2 - X, Y                2
// SUB - Take two integer prams and subtract them           2 - X, Y                3
// RET - Returns the value of a variable                    1 - Title               4
// EXT - Exit program                                       1 - Value               5

//ASCII code numbers
// 'space'      32
// EOL          10
// ,            44
// 0            48
// 9            57
// #            35


//Store the variables that are defined
struct variables 
{
    char* title;
    int value;
};


//If the malloc function has no more memory, quit
void fatal_error(void)
{
    printf("Fatal Error: Out of memory\n");
    exit(1);
}


//Turn single digits into a complete number
int addToInt(int z,int curr)
{
    curr = (curr*10) +z;
    return curr;
}


//3 letter hash multiplies the number of each letter, A=65
int check_function(char array[])
{
    //printf("%i\n",(int)*array*(int)*(array+1)*(int)*(array+2));
    switch ((int)*array * (int)*(array+1) * (int)*(array+2)) //3 Letter hash
    {             
        case 328440:             //DEF
            return 1;
        case 300560:             //ADD
            return 2;
        case 465630:             //SUB
            return 3;
        case 475272:             //RET
            return 4;
        case 510048:             //EXT
            return 5;
        default:                //Error
            return 0;
    }
}


//Running program
void execute(char* fname)
{
    int running = 1;                    // Run the program when ==1
    int anything = 0;                   // Count of variables
    char ch[3];                         // Operand storage
    struct variables table[100];        // Variable storage
    
    FILE *in_file;
    in_file = fopen(fname, "r");
    
    
    while (running) 
    {
        ch[0] = fgetc(in_file);         // Load operand and check which
        ch[1] = fgetc(in_file);
        ch[2] = fgetc(in_file);
        
        int op_code = check_function(ch);
        
        if (op_code != 0) 
        {
            ch[0] = '\0';
            memset( ch ,'\0', sizeof(ch));  
            
            //********** DEFINITION *****************

            if (op_code == 1)               
            {
                int buf_size = 0;                       //Get the variable name
                int buf_used = 0;
                
                char* buf = NULL;
                char* tmp = NULL;
                
                char c;
                
                while ((c = fgetc(in_file)) != 44)      // Use realloc to input variable name up to comma
                {
                    if (c == 32)                        // Ignoring initial space
                    {
                        c = fgetc(in_file);
                    }
                    if (buf_used == buf_size) 
                    {
                        buf_size++;
                        tmp = realloc(buf, buf_size);
                        if (!tmp) 
                        {
                            fatal_error();
                        }
                        buf = tmp;
                    }
                    buf[buf_used] = c;
                    ++buf_used;
                }

                table[anything].title = buf;            // Story variable name in struct
                buf = realloc(buf, 1);

                
                int value = 0;                          // Get the variable value
                int total = 0;
                
                value = fgetc(in_file);
                if (value == 44)                        // Ignore comma
                {
                    value = fgetc(in_file);
                }
            
              	while (value != 10)
                {
                    value = value-48;
                    value = addToInt(value,total);
                    total = value;
                    value = fgetc(in_file);
                }

                table[anything].value = total;          // Store value
                printf("Variable %s is now %i\n",table[anything].title,total);
                anything++;
            }
            
            //*********** ADDITION ***********
            
            else if (op_code == 2)              //Addition
            {                                   //Check if variable or int
                int x = 0;                      //If variable, access table to get value
                int y = 0;                      //Add the value and int
                int result;
                
                int value;
                
                //Get X
                
                value = fgetc(in_file);         //Check fo initial space
                if (value == 32) 
                {
                    value = fgetc(in_file);
                }
                
                if (value == 35)                //If int
                {
                    value = fgetc(in_file);
                    while (value != 44) 
                    {
                        value = value - 48;
                        value = addToInt(value, x);
                        x = value;
                        value = fgetc(in_file);
                    }
                }
                else                            //If variable
                {
                    int buf_size = 0;
                    int buf_used = 0;
                    
                    char* buf = NULL;
                    char* tmp = NULL;
                    
                    char c = value;
                    int u = 0;
                    
                    while (c != ',') 
                    {         
                        u++;
                        if (buf_used == buf_size) 
                        {
                            buf_size++;
                            tmp = realloc(buf, buf_size);
                            if (!tmp) 
                            {
                                fatal_error();
                            }
                            buf = tmp;
                        }
                        buf[buf_used] = c;
                        ++buf_used;
                        c = fgetc(in_file);
                    }
                    char tmp2[u];
                    strncpy(tmp2, buf, u);
                    
                    for(int i = 0; i < anything; i++)
                    {
                        if (strncmp(tmp2, table[i].title, u) == 0) 
                        {
                            x = table[i].value;
                        }
                    }
                    free(buf);
                }
                
                //Get Y
                
                value = fgetc(in_file);
                if (value == 35) 
                {
                    value = fgetc(in_file);
                    while (value != 10) 
                    {
                        value = value - 48;
                        value = addToInt(value, y);
                        y = value;
                        value = fgetc(in_file);
                    }
                }
                else                            //If variable
                {
                    int buf_size = 0;
                    int buf_used = 0;
                    
                    char* buf = NULL;
                    char* tmp = NULL;
                    
                    char c = (char)value;
                    int u = 0;
                    
                    while (c != 10) 
                    {
                        u++;
                        if (buf_used == buf_size) 
                        {
                            buf_size++;
                            tmp = realloc(buf, buf_size);
                            if (!tmp) 
                            {
                                fatal_error();
                            }
                            buf = tmp;
                        }
                        buf[buf_used] = c;
                        ++buf_used;
                        c = fgetc(in_file);
                    }
                    
                    char tmp2[u];
                    strncpy(tmp2, buf, u);
                    
                    for(int i = 0; i < anything; i++)
                    {
                        if (strncmp(tmp2, table[i].title, u) == 0) 
                        {
                            y = table[i].value;
                        }
                    }
                    free(buf);
                }
                
                result = x+y;
                printf("%i plus %i is %i\n", x, y, result);
            }
            
            //*********** SUBTRACTION ************
            
            else if (op_code == 3)              //Subtraction
            {
                int x = 0;                      //If variable, access table to get value
                int y = 0;                      //Subtract the value and int
                int result;
                
                int value;
                
                //Get X
                
                value = fgetc(in_file);         //Check fo initial space
                if (value == 32) 
                {
                    value = fgetc(in_file);
                }
                
                if (value == 35)                //If int
                {
                    value = fgetc(in_file);
                    while (value != 44) 
                    {
                        value = value - 48;
                        value = addToInt(value, x);
                        x = value;
                        value = fgetc(in_file);
                    }
                }
                else                            //If variable
                {
                    int buf_size = 0;
                    int buf_used = 0;
                    
                    char* buf = NULL;
                    char* tmp = NULL;
                    
                    char c = value;
                    int u = 0;
                    
                    while (c != ',') 
                    {         
                        u++;
                        if (buf_used == buf_size) 
                        {
                            buf_size++;
                            tmp = realloc(buf, buf_size);
                            if (!tmp) 
                            {
                                fatal_error();
                            }
                            buf = tmp;
                        }
                        buf[buf_used] = c;
                        ++buf_used;
                        c = fgetc(in_file);
                    }
                    char tmp2[u];
                    strncpy(tmp2, buf, u);
                    
                    for(int i = 0; i < anything; i++)
                    {
                        if (strncmp(tmp2, table[i].title, u) == 0) 
                        {
                            x = table[i].value;
                        }
                    }
                    free(buf);
                }
                
                //Get Y
                
                value = fgetc(in_file);
                if (value == 35) 
                {
                    value = fgetc(in_file);
                    while (value != 10) 
                    {
                        value = value - 48;
                        value = addToInt(value, y);
                        y = value;
                        value = fgetc(in_file);
                    }
                }
                else                            //If variable
                {
                    int buf_size = 0;
                    int buf_used = 0;
                    
                    char* buf = NULL;
                    char* tmp = NULL;
                    
                    char c = (char)value;
                    int u = 0;
                    
                    while (c != 10) 
                    {
                        u++;
                        if (buf_used == buf_size) 
                        {
                            buf_size++;
                            tmp = realloc(buf, buf_size);
                            if (!tmp) 
                            {
                                fatal_error();
                            }
                            buf = tmp;
                        }
                        buf[buf_used] = c;
                        ++buf_used;
                        c = fgetc(in_file);
                    }
                    
                    char tmp2[u];
                    strncpy(tmp2, buf, u);
                    
                    for(int i = 0; i < anything; i++)
                    {
                        if (strncmp(tmp2, table[i].title, u) == 0) 
                        {
                            y = table[i].value;
                        }
                    }
                    free(buf);
                }
                
                result = x-y;
                printf("%i minus %i is %i\n", x, y, result);
            }
            
            //************ RET *************
            
            else if (op_code == 4)
            {
                int buf_size = 0;
                int buf_used = 0;
                
                char* buf = NULL;
                char* tmp = NULL;
                
                char c;
                int u = 0;
                
                while ((c = fgetc(in_file)) != 10) 
                {
                    u++;
                    if (c == 32)
                    {
                        c = fgetc(in_file);
                    }
                    if (buf_used == buf_size) 
                    {
                        buf_size++;
                        tmp = realloc(buf, buf_size);
                        if (!tmp) 
                        {
                            fatal_error();
                        }
                        buf = tmp;
                    }
                    buf[buf_used] = c;
                    ++buf_used;
                }
                int x = 0;
                char tmp2[u];
                strncpy(tmp2, buf, u);

                for(int i = 0; i < anything; i++)
                {
                    if (strncmp(tmp2, table[i].title, u) == 0) 
                    {
                        x = table[i].value;
                    }
                }
                
                printf("Variable %.*s has value %i\n",u,tmp2,x);                
            }
            
            //************ EXIT ************
            
            else                            //Op_Code == 4, exit
            {
                running = 0;
            }
        }
        
        //********* ERROR *******
        
        else 
        {
            printf("Error: Command is not a function\n");
            running = 0;
        }
    }
    exit(0);                                //This stops the program completely
}