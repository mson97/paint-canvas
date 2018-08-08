//
// Created by Minhee Son on 12/4/17.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "valid.h"
#include "do.h"

char getCommand(Canvas *canvasStruct, Command *commandStruct, char blankSpace) {
  (*commandStruct).string = (char *) malloc(sizeof(char));
  int len = 0;
  char str[200];
  do {
    printf("Enter your command: ");
    fgets(str, 200, stdin);
    (*commandStruct).string = realloc((*commandStruct).string, sizeof(str) + sizeof(char));
    strcpy((*commandStruct).string, str);
    (*commandStruct).command = str[0];
  } while (!isValidCommand(canvasStruct, blankSpace, len, commandStruct));
  return (*commandStruct).command;
}

bool isValidCommand(Canvas *canvasStruct, char blankSpace, int len, Command *commandStruct) {
  if ((*commandStruct).command == quit) {
    return isValidHelpOrQuit(commandStruct, canvasStruct);
  } else if ((*commandStruct).command == help) {
    return isValidHelpOrQuit(commandStruct, canvasStruct);
  } else if ((*commandStruct).command == write) { // valid integer, between 0 and numRows - 1, between 0 and numCols - 1
    if (isValidChar((*commandStruct).string, &commandStruct->command)) {
      return isValidWrite(commandStruct, canvasStruct);
    } else {
      return false;
    }
  } else if ((*commandStruct).command == erase) {
    //  valid integers, between 0 and numRows - 1, between 0 and numCols - 1
    if (isValidChar((*commandStruct).string, &commandStruct->command)) {
      return isValidErase(commandStruct, canvasStruct);
    } else {
      return false;
    }
  } else if ((*commandStruct).command == resize) { // valid integers above 0
    if (isValidChar((*commandStruct).string, &commandStruct->command)) {
      return isValidResize(commandStruct, canvasStruct);
    } else {
      return false;
    }
  } else if ((*commandStruct).command == add) {
    // must be char: either r or c, must be integer between 0 and numRows - 1/ numCols - 1
    // make sure 3 arguments entered
    if (isValidChar((*commandStruct).string, &commandStruct->command)) {
      return isValidAdd(commandStruct, canvasStruct);
    } else { // invalid input
      return false;
    }
  } else if ((*commandStruct).command == delete) { // same as above
    // make sure 3 arguments entered
    if (isValidChar((*commandStruct).string, &commandStruct->command)) {
      return isValidDelete(commandStruct, canvasStruct);
    } else { // invalid input
      return false;
    }
  } else if ((*commandStruct).command == save) {
    (*commandStruct).file = (char *) malloc(sizeof((*commandStruct).string));
    if (isValidChar((*commandStruct).string, &commandStruct->command)) {
      return isValidSaveOrLoad(commandStruct);
    } else {
      return false;
    }
  } else if ((*commandStruct).command == load) {
    (*commandStruct).file = (char *) malloc(sizeof((*commandStruct).string));
    if (isValidChar((*commandStruct).string, &commandStruct->command)) {
      return isValidSaveOrLoad(commandStruct);
    } else {
      return false;
    }
  } else {
    printf("Unrecognized command. Type h for help.\n");
    displayCanvas(canvasStruct);
    return false;
  }
  free((*commandStruct).string);
  return true;
}

void doCommand(char command, char blankSpace, Canvas *canvasStruct, Command *commandStruct) {
  if (command == 'q') {
    doQuit(canvasStruct);
  } else if (command == help) {
    doHelp();
  } else if (command == write) {
    doWrite(canvasStruct, commandStruct, blankSpace);
  } else if (command == erase) {
    doErase(canvasStruct, commandStruct, blankSpace);
  } else if (command == add) {
    doAdd(canvasStruct, commandStruct, blankSpace);
  } else if (command == resize) {
    doResize(canvasStruct, commandStruct, blankSpace);
  } else if (command == delete) {
    doDelete(canvasStruct, commandStruct);
  } else if (command == save) {
    doSave(canvasStruct, commandStruct);
  } else if (command == load) {
    doLoad(canvasStruct, commandStruct);
  }
}
