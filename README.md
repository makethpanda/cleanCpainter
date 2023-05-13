# CleanCPainter Command Line 🎨

CleanCPainter is a command-line drawing tool that allows users to create simple geometric shapes in a terminal. Users can enter commands to draw points, lines, circles, squares, rectangles, and polygons. The shapes are then plotted on a fixed-size board, and the user can list, delete, or erase shapes as needed.

## Table of Contents

- [Features](#features)
- [Code Structure](#code-structure)
- [Interesting Parts](#interesting-parts)
- [Challenges Faced](#challenges-faced)
- [Command Examples](#command-examples)
- [Usage](#usage)

## Features

- Create **Points**, **Lines**, **Circles**, **Squares**, **Rectangles**, and **Polygons**
- **Plot** shapes on a fixed-size board
- **List** all shapes
- **Delete** shapes by ID
- **Erase** all shapes
- **Help** command for available commands

## Code Structure

The code is organized in the following files:

- `main.c`: Contains the main loop that handles user input and command execution.
- `commands.c` and `commands.h`: Contains functions to parse and execute user-entered commands.
- `shapes.c` and `shapes.h`: Contains functions to manage, draw, list, delete, and erase shapes.

## Interesting Parts

### Command Parsing 📝

The `parseCommand()` function in `commands.c` is responsible for parsing user-entered commands. It takes a string as input and returns a pointer to a `Command` structure containing the command name, parameters, and the number of parameters.

```c
Command* parseCommand(char command[]);
```

The function first extracts the command name and then iterates through the input string to parse the parameters as integers. To handle multiple commands separated by semicolons, the `main.c` file uses the `strtok()` function to split the input string into tokens.

```c
char *token = strtok(comm, ";");
```

### Shape Drawing 🖍

The `plot()` function in `shapes.c` is responsible for drawing the shapes on the board. It first initializes an empty board and then iterates through the list of shapes to draw each one depending on its type.

```c
void plot();
```

For lines, the function uses Bresenham's line algorithm to plot the line points on the board.

```c
void drawLine(int x1, int y1, int x2, int y2, char board[BOARD_SIZE][BOARD_SIZE]);
```

## Challenges Faced

- Handling command input and parsing: Implementing a command parser that can handle variable-length commands and parameters was challenging.
- Drawing shapes on the board: Implementing the logic for drawing different shapes on the board, especially lines and polygons, required a good understanding of geometry and algorithms.
- Memory management: Ensuring that memory is allocated and freed correctly for commands and shapes to avoid memory leaks.

## Command Examples

You can enter multiple commands in a single line, separated by semicolons. Here is a notable command example that draws a pentagram enclosed in a circle:

```plaintext
circle 15 15 14;line 1 15 29 15;line 15 1 15 29;polygon 15 1 8 22 22 22;polygon 15 29 8 8 22 8;plot
```

This command creates a circle with a center at (15, 15) and a radius of 14. It then draws two lines that cross the circle horizontally and vertically. Finally, it creates two polygons that together form a pentagram. The `plot` command at the end refreshes the screen to display the resulting image.

## Usage

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

For a list of available commands, type `help` in the command prompt.
