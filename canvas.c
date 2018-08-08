//
// Created by Minhee Son on 12/4/17.
//
#include <stdio.h>
#include <stdlib.h>
#include "canvas.h"

char **createCanvas(Canvas *canvasStruct, char blankSpace) {
  char **canvas = (char **) malloc((*canvasStruct).numRows * sizeof(char *));
  for (int row = 0; row < (*canvasStruct).numRows; ++row) {
    canvas[row] = (char *) malloc((*canvasStruct).numCols * sizeof(char));
    for (int col = 0; col < (*canvasStruct).numCols; ++col) {
      canvas[row][col] = blankSpace;
    }
  }
  return canvas;
}

void displayCanvas(Canvas *canvasStruct) {
  if ((*canvasStruct).numRows >= 10 || (*canvasStruct).numCols >= 10) {
    for (int row = 0; row < (*canvasStruct).numRows; ++row) {
      printf("%2d ", (*canvasStruct).numRows - (row + 1));
      for (int col = 0; col < (*canvasStruct).numCols; ++col) {
        printf("%2c ", (*canvasStruct).canvas[row][col]);
      }
      printf("\n");
    }
    printf("   ");
    for (int col = 0; col < (*canvasStruct).numCols; ++col) {
      printf("%2d ", col);
    }
    printf("\n");
  } else if ((*canvasStruct).numRows < 10 && (*canvasStruct).numCols < 10){
    for (int row = 0; row < (*canvasStruct).numRows; ++row) {
      printf("%d ", (*canvasStruct).numRows - (row + 1));
      for (int col = 0; col < (*canvasStruct).numCols; ++col) {
        printf("%c ", (*canvasStruct).canvas[row][col]);
      }
      printf("\n");
    }
    printf("  ");
    for (int col = 0; col < (*canvasStruct).numCols; ++col) {
      printf("%d ", col);
    }
    printf("\n");
  }
}

void cleanCanvas(Canvas *canvasStruct) {
  for (int row = 0; row < (*canvasStruct).numRows; ++row) {
    free((*canvasStruct).canvas[row]);
  }
  free((*canvasStruct).canvas);
  (*canvasStruct).canvas = NULL;
}
