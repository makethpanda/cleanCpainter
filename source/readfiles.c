#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "shapes.h"
#include "readfiles.h"

//function to convert a file to a command

void fileCommand(char* fileName, char verbose){
    FILE* file = fopen(fileName, "r");
    if(verbose == 1){
    printf("\033[32m[verbose]\033[0mChecking if file exists...\n");
    }
    if(file == NULL){
        //red print
        printf("\033[1;31mError: file does not exist\n\033[0m");
        return;
    }
    //make sure file extension is .ccp
    if(verbose == 1){
    printf("\033[32m[verbose]\033[0mChecking if file extension is correct\n");
    }
    char* extension = strrchr(fileName, '.');
    if(strcmp(extension, ".ccp") != 0){
        //red print
        printf("\033[1;31mError: file extension must be .ccp\n\033[0m");
        return;
    }
    if(verbose == 1){
    printf("\033[32m[verbose]\033[0mGetting file content...\n");
    }
    char line[200];
    while(fgets(line, 200, file) != NULL){
        line[strcspn(line, "\n")] = '\0';
        // divide the char into commands separated by ";"
        char *token = strtok(line, ";");
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
    }
    fclose(file);
}