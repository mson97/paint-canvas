//
// Created by Minhee Son on 12/7/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "do.h"

void doQuit(Canvas *canvasStruct) { // stop the program, free dynamic memory
  cleanCanvas(canvasStruct);
  exit(0);
}

void doHelp() {
  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");
}

void doWrite(Canvas *canvasStruct, Command *commandStruct, char blankSpace) {
  if (!(*commandStruct).isLine) {
    drawCell(canvasStruct, commandStruct);
  } else {
    drawLine(canvasStruct, commandStruct, blankSpace);
  }
}

void drawCell(Canvas *canvasStruct, Command *commandStruct) {
  (*canvasStruct).canvas[((*canvasStruct).numRows - 1) - (*commandStruct).startRow][(*commandStruct).startCol] = horiz;
}

void drawLine(Canvas *canvasStruct, Command *commandStruct, char blankSpace) {
  /* horizontal: -, vertical: |, right diag: \, left diag: /, intersection: +
  lines that are one cell big: use -
  inform user if line's not straight, don't draw line */
  int start1, start2, end1;

  if ((*commandStruct).startRow == (*commandStruct).endRow) { // check if line is horizontal, character is '-'
    if ((*commandStruct).startCol < (*commandStruct).endCol) { // start is to the left
      start1 = (*commandStruct).startCol;
      end1 = (*commandStruct).endCol;
    } else { // start is to the right
      start1 = (*commandStruct).endCol;
      end1 = (*commandStruct).startCol;
    }
    for (int i = start1; i <= end1; ++i) {
      if ((*canvasStruct).canvas[((*canvasStruct).numRows - 1) - (*commandStruct).startRow][i] == blankSpace ||
          (*canvasStruct).canvas[((*canvasStruct).numRows - 1) - (*commandStruct).startRow][i] == horiz) {
        (*canvasStruct).canvas[((*canvasStruct).numRows - 1) - (*commandStruct).startRow][i] = horiz;
      } else {
        (*canvasStruct).canvas[((*canvasStruct).numRows - 1) - (*commandStruct).startRow][i] = intersect;
      }
    }
  } else if ((*commandStruct).startCol == (*commandStruct).endCol) { // check if line is vertical, character is '|'
    if ((*commandStruct).startRow > (*commandStruct).endRow) { // start is on top
      start1 = ((*canvasStruct).numRows - 1) - (*commandStruct).startRow;
      end1 = ((*canvasStruct).numRows - 1) - (*commandStruct).endRow;
    } else { // start is on bottom
      start1 = ((*canvasStruct).numRows - 1) - (*commandStruct).endRow;
      end1 = ((*canvasStruct).numRows - 1) - (*commandStruct).startRow;
    }
    for (int row = start1; row <= end1; ++row) {
      if ((*canvasStruct).canvas[row][(*commandStruct).startCol] == blankSpace ||
          (*canvasStruct).canvas[row][(*commandStruct).startCol] == vert) {
        (*canvasStruct).canvas[row][(*commandStruct).startCol] = vert;
      } else {
        (*canvasStruct).canvas[row][(*commandStruct).startCol] = intersect;
      }
    }
  } else if (((*commandStruct).endRow - (*commandStruct).startRow)
      == ((*commandStruct).endCol - (*commandStruct).startCol)) { // check if line is diagonal: left, character is '/'
    if ((*commandStruct).startRow > (*commandStruct).endRow) { // diag is downwards
      start1 = ((*canvasStruct).numRows - 1) - (*commandStruct).startRow; // starting row pos is at top
      start2 = (*commandStruct).startCol; // starting col pos is at left
      end1 = ((*canvasStruct).numRows - 1) - (*commandStruct).endRow; // ending row pos is at bottom
    } else { // diag is upwards
      start1 = ((*canvasStruct).numRows - 1) - (*commandStruct).endRow; // starting row pos is at top
      start2 = (*commandStruct).endCol; // starting col pos is at left
      end1 = ((*canvasStruct).numRows - 1) - (*commandStruct).startRow; // ending row pos is at bottom
    }
    for (int pos = 0; pos <= end1 - start1; ++pos) {
      if ((*canvasStruct).canvas[start1 + pos][start2 - pos] == blankSpace ||
          (*canvasStruct).canvas[start1 + pos][start2 - pos] == leftDiag) {
        (*canvasStruct).canvas[start1 + pos][start2 - pos] = leftDiag;
      } else {
        (*canvasStruct).canvas[start1 + pos][start2 - pos] = intersect;
      }
    }
  } else if (((*commandStruct).endRow - (*commandStruct).startRow)
      == -((*commandStruct).endCol - (*commandStruct).startCol)) { // line is diagonal: right, character is '\'
    if ((*commandStruct).startRow > (*commandStruct).endRow) { // diag is downwards
      start1 = ((*canvasStruct).numRows - 1) - (*commandStruct).startRow;
      start2 = (*commandStruct).startCol;
      end1 = ((*canvasStruct).numRows - 1) - (*commandStruct).endRow;
    } else { // diag is upwards
      start1 = ((*canvasStruct).numRows - 1) - (*commandStruct).endRow;
      start2 = (*commandStruct).endCol;
      end1 = ((*canvasStruct).numRows - 1) - (*commandStruct).startRow;
    }
    for (int pos = 0; pos <= end1 - start1; ++pos) {
      if ((*canvasStruct).canvas[start1 + pos][start2 + pos] == blankSpace ||
          (*canvasStruct).canvas[start1 + pos][start2 + pos] == rightDiag) {
        (*canvasStruct).canvas[start1 + pos][start2 + pos] = rightDiag;
      } else {
        (*canvasStruct).canvas[start1 + pos][start2 + pos] = intersect;
      }
    }
  } else { // line is not straight
    printf("Cannot draw the line as it is not straight.\n");
  }
}

void doErase(Canvas *canvasStruct, Command *commandStruct, char blankSpace) {
  (*canvasStruct).canvas[((*canvasStruct).numRows - 1) - (*commandStruct).startRow][(*commandStruct).startCol] =
      blankSpace;
}

void doResize(Canvas *canvasStruct, Command *commandStruct, char blankSpace) {
  if ((*commandStruct).startRow > (*canvasStruct).numRows) { // add rows
    (*canvasStruct).canvas =
        realloc((*canvasStruct).canvas, (*commandStruct).startRow * sizeof(char *)); // realloc space for extra rows
    for (int i = (*canvasStruct).numRows; i < (*commandStruct).startRow; ++i) { // create space for cols for each row
      (*canvasStruct).canvas[i] = (char *) malloc((*canvasStruct).numCols * sizeof(char));
    }
    for (int i = 0; i < (*canvasStruct).numRows; ++i) {
      for (int j = 0; j < (*canvasStruct).numCols; ++j) {
        (*canvasStruct).canvas[((*commandStruct).startRow - 1) - i][j] =
            (*canvasStruct).canvas[((*canvasStruct).numRows - 1) - i][j];
      }
    }
    for (int i = 0; i < (*commandStruct).startRow - (*canvasStruct).numRows; ++i) {
      for (int j = 0; j < (*canvasStruct).numCols; ++j) {
        (*canvasStruct).canvas[i][j] = blankSpace;
      }
    }
    (*canvasStruct).numRows = (*commandStruct).startRow; // sets new number of rows
  } else if ((*commandStruct).startRow < (*canvasStruct).numRows) { // delete rows
    for (int i = 0; i < (*commandStruct).startRow; ++i) {
      for (int j = 0; j < (*canvasStruct).numCols; ++j) {
        (*canvasStruct).canvas[i][j] =
            (*canvasStruct).canvas[(*canvasStruct).numRows - (*commandStruct).startRow + i][j];
      }
      (*canvasStruct).canvas = realloc((*canvasStruct).canvas, (*commandStruct).startRow * sizeof(char *));
    }
    (*canvasStruct).numRows = (*commandStruct).startRow; // sets new number of rows
  }
  if ((*commandStruct).startCol > (*canvasStruct).numCols) { // add a column
    for (int i = 0; i < (*canvasStruct).numRows; ++i) { // iterate thru rows top to bottom, realloc space for extra cols
      (*canvasStruct).canvas[i] = realloc((*canvasStruct).canvas[i], (*commandStruct).startCol * sizeof(char));
      for (int j = (*canvasStruct).numCols; j < (*commandStruct).startCol; ++j) {
        (*canvasStruct).canvas[i][j] = blankSpace;
      }
    }
    (*canvasStruct).numCols = (*commandStruct).startCol;
  } else if ((*commandStruct).startCol < (*canvasStruct).numCols) {   // delete a column
    for (int i = 0; i < (*canvasStruct).numRows; ++i) {
      (*canvasStruct).canvas[i] = realloc((*canvasStruct).canvas[i], (*commandStruct).startCol * sizeof(char));
    }
    (*canvasStruct).numCols = (*commandStruct).startCol;
  }
}

void doAdd(Canvas *canvasStruct, Command *commandStruct, char blankSpace) {
  if ((*commandStruct).rowOrCol == 'r') { // allocate space for new row
    (*canvasStruct).canvas = realloc((*canvasStruct).canvas, ((*canvasStruct).numRows + 1) * sizeof(char *));
    for (int i = 0; i < (*canvasStruct).numCols; ++i) { // allocate space for columns of new row
      (*canvasStruct).canvas[(*canvasStruct).numRows] = (char *) malloc((*canvasStruct).numCols * sizeof(char));
    }
    for (int i = 0; i < (*commandStruct).pos; ++i) {
      for (int j = 0; j < (*canvasStruct).numCols; ++j) {
        (*canvasStruct).canvas[(*canvasStruct).numRows - i][j] =
            (*canvasStruct).canvas[((*canvasStruct).numRows - i) - 1][j];
      }
    }
    for (int j = 0; j < (*canvasStruct).numCols; ++j) {
      (*canvasStruct).canvas[(*canvasStruct).numRows - (*commandStruct).pos][j] = blankSpace;
    }
    (*canvasStruct).numRows += 1;
  } else {
    for (int i = 0; i < (*canvasStruct).numRows; ++i) {
      (*canvasStruct).canvas[i] = realloc((*canvasStruct).canvas[i], ((*canvasStruct).numCols + 1) * sizeof(char));
    }
    if ((*commandStruct).pos != (*canvasStruct).numCols && (*commandStruct).pos != 0) {
      for (int i = 0; i <= (*commandStruct).pos; ++i) {
        for (int j = 0; j < (*canvasStruct).numRows; ++j) {
          (*canvasStruct).canvas[j][(*canvasStruct).numCols - i] =
              (*canvasStruct).canvas[j][((*canvasStruct).numCols - i) - 1];
        }
      }
    } else if ((*commandStruct).pos == 0) {
      for (int i = 0; i < (*canvasStruct).numCols; ++i) {
        for (int j = 0; j < (*canvasStruct).numRows; ++j) {
          (*canvasStruct).canvas[j][(*canvasStruct).numCols - i] =
              (*canvasStruct).canvas[j][((*canvasStruct).numCols - 1) - i];
        }
      }
    }
    for (int j = 0; j < (*canvasStruct).numRows; ++j) {
      (*canvasStruct).canvas[j][(*commandStruct).pos] = blankSpace;
    }
    (*canvasStruct).numCols += 1;
  }
}

void doDelete(Canvas *canvasStruct, Command *commandStruct) {
  if ((*commandStruct).rowOrCol == 'r') { // allocate space for new row
    for (int i = 0; i < (*commandStruct).pos; ++i) {
      for (int j = 0; j < (*canvasStruct).numCols; ++j) {
        (*canvasStruct).canvas[((*canvasStruct).numRows - 1) - (*commandStruct).pos + i][j] =
            (*canvasStruct).canvas[(*canvasStruct).numRows - (*commandStruct).pos + i][j];
      }
    } // reduce extra row
    (*canvasStruct).canvas = realloc((*canvasStruct).canvas, ((*canvasStruct).numRows - 1) * sizeof(char *));
    (*canvasStruct).numRows = (*canvasStruct).numRows - 1; // set new value of rows
  } else {
    for (int i = 0; i <= (*canvasStruct).numCols - (*commandStruct).pos; ++i) {
      for (int j = 0; j < (*canvasStruct).numRows; ++j) {
        (*canvasStruct).canvas[j][(*commandStruct).pos + i] = (*canvasStruct).canvas[j][((*commandStruct).pos + i) + 1];
      }
    }
    for (int j = 0; j < (*canvasStruct).numRows; ++j) { // reduce extra column
      (*canvasStruct).canvas[j] = realloc((*canvasStruct).canvas[j], ((*canvasStruct).numCols - 1) * sizeof(char));
    }
    (*canvasStruct).numCols -= 1; // set new value of columns
  }
}

void doSave(Canvas *canvasStruct, Command *commandStruct) {
  FILE *fp = NULL;
  fp = fopen((*commandStruct).file, "w");
  if (fp == NULL) {
    printf("Improper save command or file could not be created.\n");
  } else {
    for (int i = 0; i < (*canvasStruct).numRows; ++i) {
      for (int j = 0; j < (*canvasStruct).numCols; ++j) {
        fprintf(fp, "%c ", (*canvasStruct).canvas[i][j]);
      }
      fprintf(fp, "\n");
    }
    fclose(fp);
  }
}

void doLoad(Canvas *canvasStruct, Command *commandStruct) {
  char blankSpace = '*';
  FILE *fp = NULL;
  fp = fopen((*commandStruct).file, "r");
  if (fp == NULL) {
    printf("Improper load command or file could not be created.\n");
  } else {
    cleanCanvas(canvasStruct);
    (*canvasStruct).numRows = getNumRows(fp);
    (*canvasStruct).canvas = createCanvas(canvasStruct, blankSpace);
    (*canvasStruct).numCols = getNumCols(fp);
    while (!feof(fp)) {
      for (int i = 0; i < (*canvasStruct).numRows; ++i) {
        for (int j = 0; j < (*canvasStruct).numCols; ++j) {
          fscanf(fp, " %c", &(*canvasStruct).canvas[i][j]);
        }
      }
    }
  }
  fclose(fp);
}

int getNumRows(FILE *fp) {
  int numLines = 0;
  char c;
  fscanf(fp, "%c", &c);
  while (!feof(fp)) {
    if (c == '\n') {
      ++numLines;
    }
    fscanf(fp, "%c", &c);
  }
  fseek(fp, 0, SEEK_SET);
  return numLines;
}

int getNumCols(FILE *fp) {  // prints the contents of the file
  char *tempStr = (char *) malloc(500 * sizeof(char));
  fgets(tempStr, 499, fp);
  int numElements = 0;
  int len = strlen(tempStr);
  for (int i = 0; i <= len; ++i) {
    if (tempStr[i] == ' ') {
      ++numElements;
    }
    if (tempStr[i] == '\n') {
      break;
    }
  }
  free(tempStr);
  fseek(fp, 0, SEEK_SET);
  return numElements;
}
