//
// Created by Minhee Son on 12/4/17.
//

#ifndef FINAL_COMMAND_H
#define FINAL_COMMAND_H

#include "canvas.h"
#include "stdbool.h"

typedef struct COMMAND_STRUCT {
  char command;
  char *string;
  char *file;
  int startRow;
  int startCol;
  int endRow;
  int endCol;
  int pos;
  bool isLine; // one cell or line
  char rowOrCol;
} Command;

enum paint {
  quit = 'q', // 1 argument: 'q'
  help = 'h', // 1 argument 'h'
  write = 'w', // 5 arguments: 'w' startRow startCol endRow endCol
  erase = 'e', // 3 arguments: 'e' row col
  resize = 'r', // 3 arguments: 'r' numRows, numCols
  add = 'a', // 3 arguments: 'a' r/c posNum
  delete = 'd', // 3 arguments: 'd' r/c posNum
  save = 's', // 2 arguments: 's' fileName
  load = 'l' // 2 arguments: 'l' fileName
};

char getCommand(Canvas *canvasStruct, Command *commandStruct, char blankSpace);
bool isValidCommand(Canvas *canvasStruct, char blankSpace, int len, Command *commandStruct);
void doCommand(char command, char blankSpace, Canvas *canvasStruct, Command *commandStruct);

#endif //FINAL_COMMAND_H
