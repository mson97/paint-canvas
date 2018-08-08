#include <stdio.h>
#include "canvas.h"
#include "command.h"

void getDimensions(int numArgsRead, char **argsRead, Canvas *canvasStruct) {
  char c;
  if (numArgsRead != 3) {  // rows and columns weren't provided, or incorrect number of command line arguments given
    if (numArgsRead != 1) { // incorrect number or arguments entered, not 1 or 3
      printf("Wrong number of command line arguements entered.\n");
      printf("Usage: ./paint.out [num_rows num_cols]\n");
      printf("Making default board of 10 X 10.\n");
    }
    // take default values
    (*canvasStruct).numRows = 10;
    (*canvasStruct).numCols = 10;
  } else {
    int nar = sscanf(argsRead[1], " %d%c", &(canvasStruct->numRows), &c); // scans for a int and a character
    if (nar != 1) {  // print error message: row not integer
      printf("The number of rows is not an integer.\n");
      printf("Making default board of 10 X 10.\n");
      // take default values
      (*canvasStruct).numRows = 10;
      (*canvasStruct).numCols = 10;
    } else { // row was integer
      nar = sscanf(argsRead[2], "%d%c", &(canvasStruct->numCols), &c);
      if (nar != 1) { // print error message: col not integer
        printf("The number of columns is not an integer.\n");
        printf("Making default board of 10 X 10.\n");
        // take default values
        (*canvasStruct).numRows = 10;
        (*canvasStruct).numCols = 10;
      } else { // col was integer
        if ((*canvasStruct).numRows < 1) { // print error message for row: less than one
          printf("The number of rows is less than 1.\n");
          printf("Making default board of 10 X 10.\n");
          // take default values
          (*canvasStruct).numRows = 10;
          (*canvasStruct).numCols = 10;
        } else if ((*canvasStruct).numCols < 1) { // print error message for col: less than one
          printf("The number of columns is less than 1.\n");
          printf("Making default board of 10 X 10.\n");
          // take default values
          (*canvasStruct).numRows = 10;
          (*canvasStruct).numCols = 10;
        }
      }
    }
  }
}

void runPaint(Canvas *canvasStruct, Command *commandStruct, char blank) {
  do {
    displayCanvas(canvasStruct);
    (*commandStruct).command = getCommand(canvasStruct, commandStruct, blank);
    doCommand((*commandStruct).command, blank, canvasStruct, commandStruct);
  } while ((*commandStruct).command != 'q');
}

int main(int argc, char **argv) { // input will be thru command line
  Canvas canvasStruct;
  char blank = '*';
  Command commandStruct;

  getDimensions(argc, argv, &canvasStruct); // dimensions can be inputted thru command line (optional)
  canvasStruct.canvas = createCanvas(&canvasStruct, blank); // create canvas of size 10 by 10 (default), or user values
  runPaint(&canvasStruct, &commandStruct, blank); // run paint until the user enters the quit command

  return 0;
}
