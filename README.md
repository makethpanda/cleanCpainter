# CleanCPainter Command Line 🎨🖌️
the shape drawing programming tool

<img width="579" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/eae32cbe-006f-4fcd-9a2a-60f20383c9e8">
<img width="321" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/e0023bf6-36a7-4f0c-8a12-3132c9712090">



CleanCPainter is a command-line drawing tool realized by BOUDJEDID Julien and PHO Mattheo that allows users to create and manage a variety of simple geometric shapes in a terminal. Users can draw points, lines, circles, squares, rectangles, and polygons by entering specific commands. The shapes are then plotted on a fixed-size board, and the user can list, delete, or erase shapes as needed. The user can write instructions in files and execute them in the program.

## Table of Contents

- [Features](#features)
- [Code Structure](#code-structure)
- [Interesting Parts](#interesting-parts)
- [Challenges Faced](#challenges-faced)
- [Command Examples](#command-examples)
- [Usage](#usage)

## Features ⭐

- Create **Points** (📍), **Lines** (📏), **Circles** (⚪), **Squares** (⬛), **Rectangles** (🔲), and **Polygons** (🔺)
- Execute **multiple instruction** and includes a **verbose mode**
- **Plot** shapes on a fixed-size board (📋)
- **List** all shapes (📝)
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
<img width="563" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/d26158b9-1c7d-48c2-bbb2-ce98f319dcd5">

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

example commands can be found lower

### Shape Drawing 🖍️

<img width="561" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/4679ff90-554b-4f0a-9935-877cf5b13d5f">


The `plot()` function in `shapes.c` is responsible for drawing the shapes on the board. It first initializes an empty board and then iterates through the list of shapes to draw each one depending on its type.

```c
void plot();
```

For lines, the function uses Bresenham's line algorithm to plot the line points on the board.

```c
void drawLine(int x1, int y1, int x2, int y2, char board[BOARD_SIZE][BOARD_SIZE]);
```

## reading files 

<img width="423" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/1c097b5e-e47e-4ab9-9ffc-e81db5728722">


using our built in functions we read instructions from .ccp files 

```c

void fileCommand(char* fileName, char verbose)

```

example ccp file content:

<img width="162" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/59a85cc6-288f-47e8-985e-f364c33f151b">

## Challenges Faced 😅

- Handling command input and parsing: Implementing a command parser that can handle variable-length commands and parameters was challenging.
- Drawing shapes on the board: Implementing the logic for drawing different shapes on the board, especially lines and polygons, required a good understanding of geometry and algorithms.
- Memory management: Ensuring that memory is allocated and freed correctly for commands and shapes to avoid memory leaks.

## Command Examples 🎨

You can enter **multiple commands in a single line**, separated by semicolons. Here are some notable command examples:

### Example 1: Pentagram enclosed in a circle 🌟

```plaintext
circle 15 15 14;line 1 15 29 15;line 15 1 15 29;polygon 15 1 8 22 22 22;polygon 15 29 8 8 22 8;plot
```
<img width="422" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/9b043df4-f0ec-43c9-b0ab-4bcc86613728">


This command creates a circle with a center at (15, 15) and a radius of 14. It then draws two lines that cross the circle horizontally and vertically. Finally, it creates two polygons that together form a pentagram. The `plot` command at the end refreshes the screen to display the resulting image.

### Example 2: Smiley Face 😊

```plaintext
circle 10 10 2;circle 20 10 2;line 10 20 20 20;line 5 25 25 25;plot
```
<img width="418" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/cd72444c-7654-41d4-9f61-4272c0dd3e50">


This command creates two small circles for eyes, a line for the nose, and a line for the mouth. The `plot` command displays the resulting smiley face.

### Example 3: House 🏠

```plaintext
rectangle 5 15 20 10;polygon 5 15 15 5 25 15;line 8 20 8 25;line 22 20 22 25;plot
```
<img width="431" alt="image" src="https://github.com/makethpanda/cleanCpainter/assets/42862794/c93ffdb5-fc9d-43c6-99ee-896a30b51134">


This command creates a rectangle for the house body, a polygon for the roof, and two lines for the door. The `plot` command displays the resulting house image.

## Usage 🚀

Compile the program using a C compiler:

```sh
gcc main.c commands.c shapes.c -o cleanCPainter
```

Run the program:

```sh
./cleanCPainter
```

Enter commands to create shapes, plot them, and manage them:

```plaintext
$: point 5 5
$: plot
$: list
$: delete 0
$: help
```

For a list of available commands, type `help all` in the command prompt.
