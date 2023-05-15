#include <stdlib.h>
#include <stdio.h>

#ifndef COMMANDS
#define COMMANDS
typedef struct Command{
    char* commandName;
    int* parameters;
    //number of parameters
    int paramNum;
} Command;
int stringToint(char* str);
char* getCharparam(char param[]);
Command* parseCommand(char command[]);
void executeCommand(Command* comm);
#endif 