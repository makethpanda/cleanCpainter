/*
commands.c 
This file contains the functions used to parse the commands and execute them
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "shapes.h"
#include "readfiles.h"

//function used to convert a string to an int, used for parsing some params
int stringToint(char* str) {
    int result = 0;
    int i = 0;
    while(str[i] != '\0') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

//checks for specific parameters
char* getCharparam(char param[]){
    if(strstr(param, "-verbose") != NULL){
        //returns the 
        return "v";
    }
    //check for "tofile"
    else if(strstr(param, "-tofile") != NULL){
        return "t";
    }
    else if (strstr(param, "-read") != NULL){
        return "r";
    }
    else if (strstr(param, "-edit") != NULL){
        return "e";
    }
    else{
        return " ";
    }
}

//function to parse a string into a command
Command* parseCommand(char command[]){
    int i = 0;
    //make sure commandType has memory allocated
    
    char commandType[11];
    memset(commandType, 0, sizeof(commandType));
    while(command[i] != ' ' && command[i] != '\0'){
        commandType[i] = command[i];
        i++;
    }
    commandType[i] = '\0';

    Command* cmd = (Command*) malloc(sizeof(Command));
    // Allocate memory for the command name and copy the value
    cmd->commandName = (char *) malloc((strlen(commandType) + 1) * sizeof(char));
    strcpy(cmd->commandName, commandType);
    //if the command is a file command
    if (strcmp(commandType, "file") == 0){
        int verbo = 0;
        // create int path and allocate memory for it
        int* path = (int *) malloc((strlen(command) + 1) * sizeof(int));
        //get command from i+5 until space
        //check for param
        int lentocommand = 5;
        int tofile = 0;
        //for i in range(2)
        for (int i = 0; i < 2; i++){
            char temp[10]; // temporary variable to store the first 10 characters
            strcpy(temp, command + lentocommand); // copy the first 10 characters of command + lentocommand into temp
            temp[9] = '\0'; // add a null terminator to ensure that temp is a valid C string
            char* param = getCharparam(temp); // pass the first 7 characters to getCharparam
            if (param == "v"){
                printf("\033[32m[verbose]\033[0mVerbose mode on\n");
                lentocommand += 9;
                verbo = 1;
            }
            else if(param == "t"){
                lentocommand += 8;
                int tofile = 1;
            }
        }
        // if verbose print the length of the command
        strcpy((char *) path, command + lentocommand);
        // copy the path to the path variable
        if (verbo) printf("\033[32m[verbose]\033[0mPath: %s\n", path);
        fileCommand((char *) path, verbo, tofile);
        // Make sure to free the allocated memory
        free(path);
        //make command
        cmd->parameters = NULL;
        cmd->paramNum = 0;
        return cmd;
    }
    if (strcmp(commandType, "list") == 0){
        //first param is the shape id and index of modified elem ex: -i 12.1
        //second param is index of the shape ex: -i 12.1 > 5
        int verbo = 0;
        int lentocommand = 5;
        int edit = 0;
        
        for (int i = 0; i < 2; i++){
            char temp[10]; // temporary variable to store the first 10 characters
            strcpy(temp, command + lentocommand); // copy the first 10 characters of command + lentocommand into temp
            temp[9] = '\0'; // add a null terminator to ensure that temp is a valid C string
            char* param = getCharparam(temp); // pass the first 7 characters to getCharparam
            if (param == "v"){
                printf("\033[32m[verbose]\033[0mVerbose mode on\n");
                lentocommand += 9;
                verbo = 1;
            }
            else if(param == "e"){
                lentocommand += 6;
                edit = 1;
            }
        }
        if (edit==0){
        }
        else{
            int i = lentocommand;
            int j = 0;
            int k = 0;
            int param[4];

            while(command[i] != '\0'){
                if(command[i] == ' ' || command[i] == '.' || command[i] == '>'){
                    if (command[i] != '>'){
                    param[j] = k;
                    j++;
                    k = 0;
                    }
                }
                else{
                    //convert the char to int
                    k = k * 10 + command[i] - '0';
                }
                i++;
            }
            //remove last param
            param[j-1] = k;
            // print all params
            if (verbo){
                printf("\033[32m[verbose]\033[0m Params:");
                for(int i = 0; i < j+1; i++){
                    printf(" %d", param[i]);
                }
            }
            //make command
            cmd->parameters = (int *) malloc(j * sizeof(int));
            memcpy(cmd->parameters, param, j * sizeof(int));
            // Set the number of parameters
            cmd->paramNum = j;
            return cmd;
        }
    }
    int j = 0;
    int k = 0;
    int param[3];
    while(command[i] != '\0'){
        if(command[i] == ' '){
            param[j] = k;
            j++;
            k = 0;
        }
        else{
            //convert the char to int
            k = k * 10 + command[i] - '0';
        }
        i++;
    }
    param[j] = k;
    //remove the first element of the array
    for(int i = 0; i < j; i++){
        param[i] = param[i + 1];
    }

    // Allocate memory for the parameters array and copy the values
    cmd->parameters = (int *) malloc(j * sizeof(int));
    memcpy(cmd->parameters, param, j * sizeof(int));
    // Set the number of parameters
    cmd->paramNum = j;
    return cmd;
}

//function to execute the command
void executeCommand(Command* comm){
    Command cmd = *comm;
    //create verbose flag
    int verbose = 0;
    //look for -verbose in the command
    if(cmd.paramNum > 0 && cmd.parameters[0] == 46017023){
        verbose = 1;
        printf("\033[32m[verbose]\033[0mVerbose mode on\n");
        //remove the element from the array
        for(int i = 0; i < cmd.paramNum; i++){
            cmd.parameters[i] = cmd.parameters[i + 1];
        }
        cmd.paramNum--;
        printf("\033[32m[verbose]\033[0mCommand: %s\n", cmd.commandName);
        //print params
        printf("\033[32m[verbose]\033[0mParameters:");
        for(int i = 0; i < cmd.paramNum; i++){
            printf("%d ", cmd.parameters[i]);
        }
        printf("\n");
    }
    if(strcmp(cmd.commandName, "file") == 0){
        if(verbose == 1){
            printf("\033[32m[verbose]\033[0mDone!\n");
        }
        return;
    }
    else if(strcmp(cmd.commandName, "clear") == 0){
        printf("\033[2J\033[1;1H");
        return;
    }
    else if(strcmp(cmd.commandName, "exit") == 0){
        printf("Exiting program...\n");
        exit(0);
    }
    else if(strcmp(cmd.commandName, "point") == 0){
        //if number of params is not 2
        if(cmd.paramNum != 2){
            printf("Invalid number of parameters for point\n");
            return;
        }
        else{
            //if verbose print
            if(verbose){
                printf("\033[32m[verbose]\033[0mCreating point: (%d, %d)\n", cmd.parameters[0], cmd.parameters[1]);
            }
            Shape point = {.type = POINT, .point = {cmd.parameters[0], cmd.parameters[1]}};
            addShape(point, verbose);
            if (verbose){
                printf("\033[32m[verbose]\033[0mPoint created\n");
            }
        }
    }
    else if(strcmp(cmd.commandName, "line") == 0){
        //if number of params is not 4
        if(cmd.paramNum != 4){
            printf("Invalid number of parameters for line\n");
            return;
        }
        else{
            if (verbose){
                printf("\033[32m[verbose]\033[0mCreating line: (%d, %d) (%d, %d)\n", cmd.parameters[0], cmd.parameters[1], cmd.parameters[2], cmd.parameters[3]);
            }
            Shape line = {.type = LINE, .line = {{cmd.parameters[0], cmd.parameters[1]}, {cmd.parameters[2], cmd.parameters[3]}}};
            addShape(line, verbose);
            if (verbose){
                printf("\033[32m[verbose]\033[0mLine created\n");
            }
        }
    }
    else if(strcmp(cmd.commandName, "circle") == 0){
        // if number of params is not 3
        if(cmd.paramNum != 3){
            printf("Invalid number of parameters for circle\n");
            return;
        }
        else{
            if (verbose){
                printf("\033[32m[verbose]\033[0mCreating circle: (%d, %d) %d\n", cmd.parameters[0], cmd.parameters[1], cmd.parameters[2]);
            }
            Shape circle = {.type = CIRCLE, .circle = {{cmd.parameters[0], cmd.parameters[1]}, cmd.parameters[2]}};
            addShape(circle, verbose);
            if (verbose){
                printf("\033[32m[verbose]\033[0mCircle created\n");
            }
        }
    }
    else if(strcmp(cmd.commandName, "square") == 0){
        // if number of params is not 3
        if(cmd.paramNum != 3){
            printf("Invalid number of parameters for square\n");
            return;
        }
        else{
            if (verbose){
                printf("\033[32m[verbose]\033[0mCreating square: (%d, %d) %d\n", cmd.parameters[0], cmd.parameters[1], cmd.parameters[2]);
            }
            Shape square = {.type = SQUARE, .square = {{cmd.parameters[0], cmd.parameters[1]}, cmd.parameters[2]}};
            addShape(square, verbose);
            if (verbose){
                printf("\033[32m[verbose]\033[0mSquare created\n");
            }
        }
    }
    else if(strcmp(cmd.commandName, "rectangle") == 0){
        // if number of params is not 4
        if(cmd.paramNum != 4){
            printf("Invalid number of parameters for rectangle\n");
            return;
        }
        else{
            if (verbose){
                printf("\033[32m[verbose]\033[0mCreating rectangle: (%d, %d) %d %d\n", cmd.parameters[0], cmd.parameters[1], cmd.parameters[2], cmd.parameters[3]);
            }
            Shape rectangle = {.type = RECTANGLE, .rectangle = {{cmd.parameters[0], cmd.parameters[1]}, cmd.parameters[2], cmd.parameters[3]}};
            addShape(rectangle, verbose);
            if (verbose){
                printf("\033[32m[verbose]\033[0mRectangle created\n");
            }
        }
    }
    else if(strcmp(cmd.commandName, "polygon") == 0){
        //if num params is not even
        if(cmd.paramNum % 2 != 0 || cmd.paramNum < 2){
            printf("Invalid number of parameters for polygon\n");
            return;
        }
        else{
            if (verbose){
                printf("\033[32m[verbose]\033[0mCreating polygon: ");
                for(int i = 0; i < cmd.paramNum; i++){
                    printf("(%d, %d) ", cmd.parameters[i], cmd.parameters[i + 1]);
                    i++;
                }
                printf("\n");
            }
            Polygon polygon;
            polygon.count = cmd.paramNum;

            //we need to add the points to the polygon
            int j = 0;
            for(int i = 0; i < polygon.count/2; i++){
                polygon.points[i].x = cmd.parameters[j];
                polygon.points[i].y = cmd.parameters[j + 1];
                j += 2;
            }
            if (verbose){
                printf("\033[32m[verbose]\033[0mPolygon created\n");
            }
            
            Shape shape = {.type = POLYGON, .polygon = polygon};
            addShape(shape, verbose);
            if (verbose){
                printf("\033[32m[verbose]\033[0mPolygon created\n");
            }
        }
    }
    else if(strcmp(cmd.commandName, "plot") == 0){
        //if first parameter is "tofile"
        plot(verbose);
    }
    else if(strcmp(cmd.commandName, "list") == 0){
        if(cmd.paramNum == 3){
            if (verbose){
                printf("\033[32m[verbose]\033[0mAttempting edit\n");
            }
            editShape(cmd.parameters[0], cmd.parameters[1], cmd.parameters[2]);
            listShapes();
        }
        else{
            listShapes();
        }
    }
    else if(strcmp(cmd.commandName, "delete") == 0){
        deleteShape(cmd.parameters[0]);
    }
    else if(strcmp(cmd.commandName, "erase") == 0){
        erase();
    }
    else if(strcmp(cmd.commandName, "help") == 0){
        //if they are no parameters display the help menu
        if(cmd.paramNum == 0){
            printf("\033[1mhelp <command>\033[0m\n");
            printf("displays the help menu for the specified command, use \033[1mall\033[0m for all commands\n");
        }
        else{
            // use the convert function to compare the command parameter to the converted string
            if (cmd.parameters[0] == stringToint("all")){
                printf("\033[1mAvailable commands:\033[0m\n");
                printf("    \033[1mclear\033[0m\n");
                printf("    \033[1mfile\033[0m\n");
                printf("    \033[1mexit\033[0m\n");
                printf("    \033[1mpoint\033[0m\n");
                printf("    \033[1mline\033[0m\n");
                printf("    \033[1mcircle\033[0m\n");
                printf("    \033[1msquare\033[0m\n");
                printf("    \033[1mrectangle\033[0m\n");
                printf("    \033[1mpolygon\033[0m\n");
                printf("    \033[1mplot\033[0m\n");
                printf("    \033[1mlist\033[0m\n");
                printf("    \033[1mdelete\033[0m\n");
                printf("    \033[1merase\033[0m\n");
                printf("    \033[1mhelp\033[0m\n");
            }
            else if (cmd.parameters[0] == stringToint("clear")){
                printf("\033[1musage:\033[0m\n");
                printf("    $:clear (-verbose)\n");
                printf("clears the screen\n");
                printf("\033[1mverbose:\033[0m optional parameter used for debugging\n");
            }
            else if (cmd.parameters[0] == stringToint("file")){
                printf("\033[1musage:\033[0m\n");
                printf("    $:file (-verbose) <file.ccp>\n");
                printf("read instructions from a file\n");
                printf("\033[1mverbose:\033[0m optional parameter used for debugging\n");
                printf("\033[1mfile.ccp:\033[0m file to read instructions from\n");
            }
            else if (cmd.parameters[0] == stringToint("exit")){
                printf("\033[1musage:\033[0m\n");
                printf("    $:exit (-verbose)\n");
                printf("exits the program\n");
                printf("\033[1mverbose:\033[0m optional parameter used for debugging\n");
            }
            else if (cmd.parameters[0] == stringToint("point")){
                printf("\033[1musage:\033[0m\n");
                printf("    $:point (-verbose) <x1> <y1>\n");
                printf("adds a point to the image\n");
                printf("\033[1mverbose:\033[0m optional parameter used for debugging\n");
                printf("\033[1mx1:\033[0m x coordinate of the point\n");
                printf("\033[1my1:\033[0m y coordinate of the point\n");
            }
            else if (cmd.parameters[0] == stringToint("line")){
                printf("\033[1musage:\033[0m\n");
                printf("    $:line (-verbose) <x1> <y1> <x2> <y2>\n");
                printf("adds a line to the image\n");
                printf("\033[1mverbose:\033[0m optional parameter used for debugging\n");
                printf("\033[1mx1:\033[0m x coordinate of the first point\n");
                printf("\033[1my1:\033[0m y coordinate of the first point\n");
                printf("\033[1mx2:\033[0m x coordinate of the second point\n");
                printf("\033[1my2:\033[0m y coordinate of the second point\n");
            }
            else if (cmd.parameters[0] == stringToint("circle")){
                printf("\033[1musage:\033[0m\n");
                printf("    $:circle (-verbose) <x1> <y1> <radius>\n");
                printf("adds a circle to the image\n");
                printf("\033[1mverbose:\033[0m optional parameter used for debugging\n");
                printf("\033[1mx1:\033[0m x coordinate of the center of the circle\n");
                printf("\033[1my1:\033[0m y coordinate of the center of the circle\n");
                printf("\033[1mradius:\033[0m radius of the circle\n");
            }
            else if (cmd.parameters[0] == stringToint("square")){
                printf("\033[1musage:\033[0m\n");
                printf("    $:square (-verbose) <x1> <y1> <length>\n");
                printf("adds a square to the image\n");
                printf("\033[1mverbose:\033[0m optional parameter used for debugging\n");
                printf("\033[1mx1:\033[0m x coordinate of the upper left corner of the square\n");
                printf("\033[1my1:\033[0m y coordinate of the upper left corner of the square\n");
                printf("\033[1mlength:\033[0m length of the square\n");
            }
            else if (cmd.parameters[0] == stringToint("rectangle")){
                printf("\033[1musage:\033[0m\n");
                printf("    $:rectangle (-verbose) <x1> <y1> <width> <height>\n");
                printf("adds a rectangle to the image\n");
                printf("\033[1mverbose:\033[0m optional parameter used for debugging\n");
                printf("\033[1mx1:\033[0m x coordinate of the upper left corner of the rectangle\n");
                printf("\033[1my1:\033[0m y coordinate of the upper left corner of the rectangle\n");
                printf("\033[1mwidth:\033[0m width of the rectangle\n");
                printf("\033[1mheight:\033[0m height of the rectangle\n");
            }
            else if (cmd.parameters[0] == stringToint("polygon")){
                printf("\033[1musage:\033[0m\n");
                printf("    $:polygon (-verbose) <x1> <y1> <x2> <y2> <x3> <y3> ...\n");
                printf("adds a polygon to the image\n");
                printf("\033[1mverbose:\033[0m optional parameter used for debugging\n");
                printf("\033[1mx1:\033[0m x coordinate of the first point\n");
                printf("\033[1my1:\033[0m y coordinate of the first point\n");
                printf("\033[1mx2:\033[0m x coordinate of the second point\n");
                printf("\033[1my2:\033[0m y coordinate of the second point\n");
                printf("...\n");
                printf("\033[1mxn:\033[0m x coordinate of the nth point\n");
                printf("\033[1myn:\033[0m y coordinate of the nth point\n");
            }
            else if (cmd.parameters[0] == stringToint("plot")){
                printf("\033[1musage:\033[0m\n");
                printf("    $:plot (-verbose)\n");
                printf("refreshes the screen to display all the geometric shapes in the image\n");
                printf("\033[1mverbose:\033[0m optional parameter used for debugging\n");
            }
            else if (cmd.parameters[0] == stringToint("list")){
                printf("\033[1musage:\033[0m\n");
                printf("    $:list (-verbose) (-edit <ID>.<index> > <newValue>)\n");
                printf("displays a list of all the geometric shapes that make up the image and all their information\n");
                printf("\033[1mverbose:\033[0m optional parameter used for debugging\n");
                printf("\033[1mID:\033[0m identifier of the shape to edit\n");
                printf("\033[1mindex:\033[0m index of the value to edit starting at 1\n");
                printf("\033[1mnewValue:\033[0m new value of the shape\n");
                printf("\033[1mexample:\033[0m\n");
                printf("    $:list -edit 1.1 > 10\n");
            }
            else if (cmd.parameters[0] == stringToint("delete")){
                printf("\033[1musage:\033[0m\n");
                printf("    $:delete (-verbose) <id>\n");
                printf("deletes a shape from its identifier id.\n");
                printf("\033[1mverbose:\033[0m optional parameter used for debugging\n");
                printf("\033[1mid:\033[0m identifier of the shape to delete\n");
            }
            else if (cmd.parameters[0] == stringToint("erase")){
                printf("\033[1musage:\033[0m\n");
                printf("    $:erase (-verbose) \n");
                printf("removes all shapes from an image.\n");
                printf("\033[1mverbose:\033[0m optional parameter used for debugging\n");
            }
            else if (cmd.parameters[0] == stringToint("help")){
                printf("\033[1musage:\033[0m\n");
                printf("    $:help (-verbose)\n");
                printf("displays the list of commands\n");
                printf("\033[1mverbose:\033[0m optional parameter used for debugging\n");
            }
            else{
                printf("\033[1mnot a valid parameter\033[0m\n");
            }

        }
    //if there is a parameter related to a function
    }
    else{
        //return the input and say it was invalid
        printf("' %s ' is not a valid command\n", cmd.commandName);
    }
}
