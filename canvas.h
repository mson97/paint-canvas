//
// Created by Minhee Son on 12/4/17.
//

#ifndef FINAL_CANVAS_H
#define FINAL_CANVAS_H

typedef struct CANVAS_STRUCT {
  int numRows;
  int numCols;
  char **canvas;
} Canvas;

char **createCanvas(Canvas *canvasStruct, char blankSpace);
void displayCanvas(Canvas *canvasStruct);
void cleanCanvas(Canvas *canvasStruct);

#endif //FINAL_CANVAS_H
