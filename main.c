#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "shapes.h"


int main(){
    printf("Welcome to the cleanCpainter command line!, type 'help' for a list of commands\n");
    while(1){
        printf("$: ");
        char comm[200];
        fgets(comm, 200, stdin);
        comm[strcspn(comm, "\n")] = '\0';
        // divide the char into commands separated by ";"
        char *token = strtok(comm, ";");
        while(token != NULL){
            // if the input isn't spaces
            if(token[0] != ' '){
                //remove the spaces from the end of the string if there is one
                int i = strlen(token) - 1;
                while(token[i] == ' '){
                    token[i] = '\0';
                    i--;
                }
                Command* userCmd = parseCommand(token);
                executeCommand(userCmd);
                // Free the allocated memory for the command structure
                free(userCmd->parameters);
                free(userCmd->commandName);
                free(userCmd);
            }
            token = strtok(NULL, ";");
        }
        /*
        Command* userCmd = parseCommand(comm);
        // print the parameters
        executeCommand(userCmd);
        // Free the allocated memory for the command structure
        free(userCmd->parameters);
        free(userCmd->commandName);
        free(userCmd);*/
    }
    return 0;
}