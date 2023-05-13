# CleanCPainter Command Line 🎨🖌️

CleanCPainter is a command-line drawing tool that allows users to create and manage a variety of simple geometric shapes in a terminal. Users can draw points, lines, circles, squares, rectangles, and polygons by entering specific commands. The shapes are then plotted on a fixed-size board, and the user can list, delete, or erase shapes as needed.

## Table of Contents

- [Features](#features)
- [Code Structure](#code-structure)
- [Interesting Parts](#interesting-parts)
- [Challenges Faced](#challenges-faced)
- [Command Examples](#command-examples)
- [Usage](#usage)

## Features ⭐

- Create **Points** (📍), **Lines** (📏), **Circles** (⚪), **Squares** (⬛), **Rectangles** (🔲), and **Polygons** (🔺)
- **Plot** shapes on a fixed-size board (📋)
- **List** all shapes (📝)
- **Delete** shapes by ID (❌)
- **Erase** all shapes (🗑️)
- **Help** command for available commands (❓)

## Code Structure 📚

The code is organized in the following files:

- `main.c`: Contains the main loop that handles user input and command execution.
- `commands.c` and `commands.h`: Contains functions to parse and execute user-entered commands.
- `shapes.c` and `shapes.h`: Contains functions to manage, draw, list, delete, and erase shapes.

## Interesting Parts 🔍

### Command Parsing 📝

The `parseCommand()` function in `commands.c` is responsible for parsing user-entered commands. It takes a string as input and returns a pointer to a `Command` structure containing the command name, parameters, and the number of parameters.

```c
Command* parseCommand(char command[]);
```

The function first extracts the command name and then iterates through the input string to parse the parameters as integers. To handle multiple commands separated by semicolons, the `main.c` file uses the `strtok()` function to split the input string into tokens.

```c
char *token = strtok(comm, ";");
```

This makes it possible to stack multiple commands on one line, allowing for more complex drawings with a single input.

### Shape Drawing 🖍️

The `plot()` function in `shapes.c` is responsible for drawing the shapes on the board. It first initializes an empty board and then iterates through the list of shapes to draw each one depending on its type.

```c
void plot();
```

For lines, the function uses Bresenham's line algorithm to plot the line points on the board.

```c
void drawLine(int x1, int y1, int x2, int y2, char board[BOARD_SIZE][BOARD_SIZE]);
```

## Challenges Faced 😅

- Handling command input and parsing: Implementing a command parser that can handle variable-length commands and parameters was challenging.
- Drawing shapes on the board: Implementing the logic for drawing different shapes on the board, especially lines and polygons, required a good understanding of geometry and algorithms.
- Memory management: Ensuring that memory is allocated and freed correctly for commands and shapes to avoid memory leaks.

## Command Examples 🎨

You can enter multiple commands in a single line, separated by semicolons. Here are some notable command examples:

### Example 1: Pentagram enclosed in a circle 🌟

```plaintext
circle 15 15 14;line 1 15 29 15;line 15 1 15 29;polygon 15 1 8 22 22 22;polygon 15 29 8 8 22 8;plot
```

This command creates a circle with a center at (15, 15) and a radius of 14. It then draws two lines that cross the circle horizontally and vertically. Finally, it creates two polygons that together form a pentagram. The `plot` command at the end refreshes the screen to display the resulting image.

### Example 2: Smiley Face 😊

```plaintext
circle 10 10 2;circle 20 10 2;line 10 20 20 20;line 5 25 25 25;plot
```

This command creates two small circles for eyes, a line for the nose, and a line for the mouth. The `plot` command displays the resulting smiley face.

### Example 3: House 🏠

```plaintext
rectangle 5 15 20 10;polygon 5 15 15 5 25 15;line 8 20 8 25;line 22 20 22 25;plot
```

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

For a list of available commands, type `help` in the command prompt.
