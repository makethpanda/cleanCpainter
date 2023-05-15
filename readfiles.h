#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "shapes.h"

// Function: read_file
// Input: char* filename, char* mode
// Output: int
// Read the file and return the number of lines
void fileCommand(char* filename, int verbose, int plotToFile);
#endif