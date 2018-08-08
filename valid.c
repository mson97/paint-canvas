//
// Created by Minhee Son on 12/4/17.
//

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include "valid.h"

bool isValidChar(char *inputStr, char *command) {
  char c = ' ';
  sscanf(inputStr, " %c%c", command, &c);
  if (!isspace(c)) {
    c = ' ';
    printf("Unrecognized command. Type h for help.\n");
    return false;
  } else {
    return true;
  }
}

bool isValidHelpOrQuit(Command* commandStrut, Canvas* canvasStruct) {
  char c = ' ';
  int nar = sscanf(commandStrut->string, " %c %c", &commandStrut->command, &c);
  if (nar == 2 && !(isspace(c))) {
    c = ' ';
    printf("Unrecognized command. Type h for help.\n");
    displayCanvas(canvasStruct);
    return false;
  } else {
    return true;
  }
}

bool isValidWrite(Command *commandStruct, Canvas *canvasStruct) {
  char char1 = ' ', char2 = ' ';
  int nar = sscanf(commandStruct->string, " %c %d %d%c %d %d%c",
                   &commandStruct->command, &commandStruct->startRow, &commandStruct->startCol, &char1,
                   &commandStruct->endRow, &commandStruct->endCol, &char2);
  if (!isspace(char1) || !isspace(char2)) { // checks that nothing else was at the end
    char1 = ' ';
    char2 = ' ';
    printf("Improper draw command.\n");
    return false;
  } else {
    if (nar == 4) { // drawing one cell
      if (isInBounds((*commandStruct).startRow, 0, (*canvasStruct).numRows - 1) &&
          isInBounds((*commandStruct).startCol, 0, (*canvasStruct).numCols - 1)) {
        (*commandStruct).isLine = false;
        return true;
      } else {
        printf("Improper draw command.\n");
        return false;
      }
    } else if (nar == 7) { // drawing a line
      if (isInBounds((*commandStruct).startRow, 0, (*canvasStruct).numRows - 1) && // check if in bounds
          isInBounds((*commandStruct).endRow, 0, (*canvasStruct).numRows - 1) &&
          isInBounds((*commandStruct).startCol, 0, (*canvasStruct).numCols - 1) &&
          isInBounds((*commandStruct).endCol, 0, (*canvasStruct).numCols - 1)) {
        (*commandStruct).isLine = true;
        return true;
      } else {
        printf("Improper draw command.\n");
        displayCanvas(canvasStruct);
        return false;
      }
    } else {
      printf("Improper draw command.\n");
      return false;
    }
  }
}

bool isValidErase(Command *commandStruct, Canvas *canvasStruct) {
  char c = ' ';
  int nar = sscanf(commandStruct->string, " %c %d %d%c",
                   &commandStruct->command, &commandStruct->startRow, &commandStruct->startCol, &c);
  if (!isspace(c)) { // checks that nothing else was at the end
    c = ' ';
    printf("Improper erase command.\n");
    displayCanvas(canvasStruct);
    return false;
  } else {
    if (nar == 4) {
      if (isInBounds((*commandStruct).startRow, 0, (*canvasStruct).numRows - 1) &&
          isInBounds((*commandStruct).startCol, 0, (*canvasStruct).numCols - 1)) {
        return true;
      } else {
        printf("Improper erase command.\n");
        displayCanvas(canvasStruct);
        return false;
      }
    } else {
      printf("Improper erase command.\n");
      displayCanvas(canvasStruct);
      return false;
    }
  }
}

bool isValidAdd(Command *commandStruct, Canvas *canvasStruct) {
  char c = ' ';
  int nar = sscanf(commandStruct->string,
                   "%c %c %d%c",
                   &commandStruct->command,
                   &commandStruct->rowOrCol,
                   &commandStruct->pos,
                   &c);
  if (!isspace(c)) { // checks that nothing else was at the end
    c = ' ';
    printf("Improper add command.\n");
    displayCanvas(canvasStruct);
    return false;
  } else {
    if (nar == 4) {
      if (((*commandStruct).rowOrCol == 'r' && isInBounds((*commandStruct).pos, 0, (*canvasStruct).numRows)) ||
          ((*commandStruct).rowOrCol == 'c' && isInBounds((*commandStruct).pos, 0, (*canvasStruct).numCols))) {
        return true;
      } else {
        printf("Improper add command.\n");
        displayCanvas(canvasStruct);
        return false;
      }
    } else {
      printf("Improper add command.\n");
      displayCanvas(canvasStruct);
      return false;
    }
  }
}

bool isValidDelete(Command *commandStruct, Canvas *canvasStruct) {
  char c = ' ';
  int nar = sscanf(commandStruct->string,
                   "%c %c %d%c",
                   &commandStruct->command,
                   &commandStruct->rowOrCol,
                   &commandStruct->pos,
                   &c);
  if (!isspace(c)) { // checks that nothing else was at the end
    c = ' ';
    printf("Improper delete command.\n");
    displayCanvas(canvasStruct);
    return false;
  } else {
    if (nar == 4) {
      if (((*commandStruct).rowOrCol == 'r' && isInBounds((*commandStruct).pos, 0, (*canvasStruct).numRows - 1)) ||
          ((*commandStruct).rowOrCol == 'c' && isInBounds((*commandStruct).pos, 0, (*canvasStruct).numCols - 1))) {
        return true;
      } else {
        printf("Improper delete command.\n");
        displayCanvas(canvasStruct);
        return false;
      }
    } else {
      printf("Improper delete command.\n");
      displayCanvas(canvasStruct);
      return false;
    }
  }
}

bool isValidSaveOrLoad(Command *commandStruct) {
  char c = ' ';
  int nar = sscanf(commandStruct->string, " %c %s %c", &commandStruct->command, commandStruct->file, &c);
  if (!isspace(c)) { // checks that nothing else was at the end
    printf("Improper save command or file could not be created.\n");
    return false;
  } else {
    if (nar == 2) {
      return true;
    } else {
      printf("Improper save command or file could not be created.\n");
      return false;
    }
  }
}

bool isValidResize(Command *commandStruct, Canvas *canvasStruct) {
  char c = ' ';
  int nar = sscanf(commandStruct->string, " %c %d %d%c",
                   &commandStruct->command, &commandStruct->startRow, &commandStruct->startCol, &c);
  if (!isspace(c)) { // checks that nothing else was at the end
    c = ' ';
    printf("Improper resize command.\n");
    displayCanvas(canvasStruct);
    return false;
  } else {
    if (nar == 4) {
      if ((*commandStruct).startRow > 0 && (*commandStruct).startCol > 0) {
        return true;
      } else {
        printf("Improper resize command.\n");
        displayCanvas(canvasStruct);
        return false;
      }
    } else {
      printf("Improper resize command.\n");
      displayCanvas(canvasStruct);
      return false;
    }
  }
}

bool isInBounds(const int val, const int lower_bound, const int upper_bound) {
  return (val >= lower_bound) && (val <= upper_bound);
}
