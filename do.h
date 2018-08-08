//
// Created by Minhee Son on 12/7/17.
//

#ifndef FINAL_DO_H
#define FINAL_DO_H

#include "canvas.h"
#include "command.h"

enum characters {
  horiz = '-',
  vert = '|',
  leftDiag = '/',
  rightDiag = '\\',
  intersect = '+',
};

void doQuit(Canvas *canvasStruct);
void doWrite(Canvas *canvasStruct, Command *commandStruct, char blankSpace);
void doHelp();
void doErase(Canvas *canvasStruct, Command *commandStruct, char blankSpace);
void doResize(Canvas *canvasStruct, Command *commandStruct, char blankSpace);
void doAdd(Canvas *canvasStruct, Command *commandStruct, char blankSpace);
void doDelete(Canvas *canvasStruct, Command *commandStruct);
void doSave(Canvas *canvasStruct, Command *commandStruct);
void doLoad(Canvas *canvasStruct, Command *commandStruct);
void drawLine(Canvas *canvasStruct, Command *commandStruct, char blankSpace);
void drawCell(Canvas *canvasStruct, Command *commandStruct);
int getNumRows(FILE *fp);
int getNumCols(FILE *fp);

#endif //FINAL_DO_H
