#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "commands.h"
#include "shapes.h"

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

    int j = 0;
    int k = 0;
    int param[12];
    while(command[i] != '\0'){
        if(command[i] == ' '){
            param[j] = k;
            j++;
            k = 0;
        }
        else{
            k = k * 10 + command[i] - '0';
        }
        i++;
    }
    Command* cmd = (Command*) malloc(sizeof(Command));
    // Allocate memory for the command name and copy the value
    cmd->commandName = (char *) malloc((strlen(commandType) + 1) * sizeof(char));
    strcpy(cmd->commandName, commandType);
    /*
    PROBLEM: the output params are not correct
    ex: square 10 10 10
    output: 0 10 10 10
    tofix we do this:
    
    //get last param
    param[j] = '-8888';
    j++;*/
    param[j] = k;
    //j++;
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

//execute the command
void executeCommand(Command* comm){
    Command cmd = *comm;
    if(strcmp(cmd.commandName, "clear") == 0){
        //clear terminal screen
        system("clear");
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
            Shape point = {.type = POINT, .point = {cmd.parameters[0], cmd.parameters[1]}};
            addShape(point);
        }
    }
    else if(strcmp(cmd.commandName, "line") == 0){
        //if number of params is not 4
        if(cmd.paramNum != 4){
            printf("Invalid number of parameters for line\n");
            return;
        }
        else{
            //allocate memory for the line

            Shape line = {.type = LINE, .line = {{cmd.parameters[0], cmd.parameters[1]}, {cmd.parameters[2], cmd.parameters[3]}}};
            addShape(line);
        }
    }
    else if(strcmp(cmd.commandName, "circle") == 0){
        // if number of params is not 3
        if(cmd.paramNum != 3){
            printf("Invalid number of parameters for circle\n");
            return;
        }
        else{
            Shape circle = {.type = CIRCLE, .circle = {{cmd.parameters[0], cmd.parameters[1]}, cmd.parameters[2]}};
            addShape(circle);
        }
    }
    else if(strcmp(cmd.commandName, "square") == 0){
        // if number of params is not 3
        if(cmd.paramNum != 3){
            printf("Invalid number of parameters for square\n");
            return;
        }
        else{
            Shape square = {.type = SQUARE, .square = {{cmd.parameters[0], cmd.parameters[1]}, cmd.parameters[2]}};
            addShape(square);
        }
    }
    else if(strcmp(cmd.commandName, "rectangle") == 0){
        // if number of params is not 4
        if(cmd.paramNum != 4){
            printf("Invalid number of parameters for rectangle\n");
            return;
        }
        else{
            Shape rectangle = {.type = RECTANGLE, .rectangle = {{cmd.parameters[0], cmd.parameters[1]}, cmd.parameters[2], cmd.parameters[3]}};
            addShape(rectangle);
        }
    }
    else if(strcmp(cmd.commandName, "polygon") == 0){
        //if num params is not even
        if(cmd.paramNum % 2 != 0){
            printf("Invalid number of parameters for polygon\n");
            return;
        }
        else{
            Polygon polygon;
            polygon.count = cmd.paramNum;

            //we need to add the points to the polygon
            int j = 0;
            for(int i = 0; i < polygon.count/2; i++){
                polygon.points[i].x = cmd.parameters[j];
                polygon.points[i].y = cmd.parameters[j + 1];
                j += 2;
            }
            
            Shape shape = {.type = POLYGON, .polygon = polygon};
            addShape(shape);
        }
    }
    else if(strcmp(cmd.commandName, "plot") == 0){
        plot();
    }
    else if(strcmp(cmd.commandName, "list") == 0){
        listShapes();
    }
    else if(strcmp(cmd.commandName, "delete") == 0){
        deleteShape(cmd.parameters[0]);
    }
    else if(strcmp(cmd.commandName, "erase") == 0){
        erase();
    }
    else if(strcmp(cmd.commandName, "help") == 0){
        printf("clear : clear the screen\n");
        printf("exit : exit the program\n");
        printf("point x y : add a point\n");
        printf("line x1 y1 x2 y2 : add a segment connecting two points (x1, y1) and (x2, y2)\n");
        printf("circle x y radius : add a circle of centre (x, y) and a radius radius\n");
        printf("square x y length : add a square whose upper left corner is (x, y) and whose side is length.\n");
        printf("rectangle x y width height : add a rectangle whose upper left corner is (x, y), whose width is width and whose height is height\n");
        printf("polygon x1 y1 x2 y2 x3 y3 ... ... : add a polygon with the list of given points\n");
        printf("plot : refresh the screen to display all the geometric shapes in the image (depending on the display rules)\n");
        printf("list : display a list of all the geometric shapes that make up the image and all their information\n");
        printf("delete id : delete a shape from its identifier id.\n");
        printf("erase : remove all shapes from an image.\n");
        printf("help : display the list of commands\n");
    }
    else{
        //return the input and say it was invalid
        printf("' %s ' is not a valid command\n", cmd.commandName);
    }
}
