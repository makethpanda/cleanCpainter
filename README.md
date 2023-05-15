<img width="300" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/e54bb6dc-ceb3-4b80-b11e-f56f2f6f3307">

# CleanCPainter Command Line 🎨🖌️
the shape drawing programming tool

<img width="428" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/3bb36c25-cdc3-48f2-b0c3-067cd7ca4b22">
<img width="385" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/d71e8b53-d31d-4510-8ce6-acd1a3b506df">



CleanCPainter is a command-line drawing tool realized by BOUDJEDID Julien and PHO Mattheo that allows users to create and manage a variety of simple geometric shapes in a terminal. Users can draw points, lines, circles, squares, rectangles, and polygons by entering specific commands. The shapes are then plotted on a fixed-size board, and the user can list, delete, or erase shapes as needed. The user can write instructions in files and execute them in the program.

## Table of Contents

- [Features](##features)
- [Code Structure](##code-structure)
- [Interesting Parts](##interesting-parts)
- [Challenges Faced](##challenges-faced)
- [Command Examples](##command-examples)
- [Usage](#usage)

## Features ⭐

- Create **Points** (📍), **Lines** (📏), **Circles** (⚪), **Squares** (⬛), **Rectangles** (🔲), and **Polygons** (🔺)
- Execute **multiple instruction** and includes a **verbose mode**
- **Plot** shapes on a fixed-size board (📋)
- **List** all shapes (📝)
- **EDIT** shape values (📋)
- **Delete** shapes by ID (❌)
- **Erase** all shapes (🗑️)
- **Help** command for available commands (❓)
- **READ FILES** read and execute files of commands  (📋📋📋)

## Code Structure 📚

The code is organized in the following files:

- `main.c`: Contains the main loop that handles user input and command execution.
- `commands.c` and `commands.h`: Contains functions to parse and execute user-entered commands.
- `shapes.c` and `shapes.h`: Contains functions to manage, draw, list, delete, and erase shapes.
- `readfiles.c` and `readfiles.h`: Contains functions to read and execute instructions from files

## Interesting Parts 🔍

### Command Parsing 📝

<img width="478" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/51d0753c-748d-4d50-b882-cb3c555328f9">


The `parseCommand()` function in `commands.c` is responsible for parsing user-entered commands. It takes a string as input and returns a pointer to a `Command` structure containing the command name, parameters, and the number of parameters.

```c
typedef struct Command{
    char* commandName;
    int* parameters;
    int paramNum;
} Command;
```

```c
Command* parseCommand(char command[]);
```

The function first extracts the command name and then iterates through the input string to parse the parameters as integers. To handle multiple commands separated by semicolons, the `main.c` file uses the `strtok()` function to split the input string into tokens.

```c
char *token = strtok(comm, ";");
```

This makes it possible to stack multiple commands on one line, allowing for more complex drawings with a single input.

However, we also have some special parameters, such as '-verbose', that can be used on any command to show the inner workings of the program

<img width="339" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/8c03018a-3116-455f-af7d-49958acb02df">


example commands can be found lower

### Shape Drawing 🖍️

<img width="348" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/43ebf354-984d-4584-9fb8-a91fbdc56b08">


The `plot()` function in `shapes.c` is responsible for drawing the shapes on the board. It first initializes an empty board and then iterates through the list of shapes to draw each one depending on its type.

```c
void plot();
```

For lines, the function uses Bresenham's line algorithm to plot the line points on the board.

```c
void drawLine(int x1, int y1, int x2, int y2, char board[BOARD_SIZE][BOARD_SIZE]);
```

## reading files 

<img width="418" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/0411b012-f3ff-4b57-b1c0-7514d5ee5472">


using our built in functions we read instructions from .ccp files using fopens

```c

void fileCommand(char* fileName, char verbose)

```

we then divide text into commands like in the terminal:

```c
char line[200];
    while(fgets(line, 200, file) != NULL){
        line[strcspn(line, "\n")] = '\0';
        // divide the text lines into commands separated by ";"
```

example ccp file content:

<img width="162" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/59a85cc6-288f-47e8-985e-f364c33f151b">

# recursive file calling

Here is an example of what happens when you call a file that calls other files:
<img width="338" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/824f605e-9e59-4b74-872c-165e50c86ed7">

HW.ccp:
```c
file -verbose tests\hello.ccp;
file -verbose tests\world.ccp;
plot
```

## Modifying values of already placed objects 

Using our list function we can easily access all objects on the board:

<img width="326" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/67ae0934-a720-43f5-83ef-a4d4d31ad44d">


However, we can modify or delete content using either:

    - the delete function
    <img width="326" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/182f7e52-0c0b-4547-a689-2785829d5c4f">

Or actually ***modify*** values using the special -edit parameter for the list command

<img width="328" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/3ced8225-633b-429a-ae94-cf0e5bcc067e">


## A useful help menu for each command

<img width="655" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/da02546a-95b2-4c4a-a16f-c22d210d45bc">

hint: typing 'help all' returns a list of all the usable commands

## Challenges Faced 😅

- Handling command input and parsing: Implementing a command parser that can handle variable-length commands and parameters was challenging.
- Drawing shapes on the board: Implementing the logic for drawing different shapes on the board, especially lines and polygons, required a good understanding of geometry and algorithms.
- Memory management: Ensuring that memory is allocated and freed correctly for commands and shapes to avoid memory leaks.

## Command Examples 🎨

### full demo file

included in the source code is a tests folder containing many test commands, running demo.ccp runs all of them

`file tests/demo.ccp`

<img width="159" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/2f48b4ad-e95f-4def-a896-a8d2a0546932">

hello world:

<img width="418" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/531c408e-8c16-4c5d-8045-f4e40e0b8d10">

pentagram:

<img width="418" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/a23d59c1-4464-473d-8770-7da9ca0c3a73">

dog:

<img width="346" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/c76de667-2fc8-4397-9f99-83110399db73">


Hint: feel free to just open the files and type the commands in the terminal 

## Usage 🚀

Compile the program using a C compiler, or use our precompiled version in /release:

```sh
gcc *.c -o cleanCPainter
```
Run the program

Enter 'help' to see a list of commands:


For a list of available commands, type `help all` in the command prompt.
