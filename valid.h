//
// Created by Minhee Son on 12/4/17.
//

#ifndef FINAL_VALID_H
#define FINAL_VALID_H

#include "command.h"

  bool isInBounds(const int val, const int lower_bound, const int upper_bound);
  bool isValidChar(char *inputStr, char *command);
  bool isValidHelpOrQuit(Command* commandStrut, Canvas* canvasStruct);
  bool isValidWrite(Command *commandStruct, Canvas *canvasStruct);
  bool isValidErase(Command *commandStruct, Canvas *canvasStruct);
  bool isValidResize(Command *commandStruct, Canvas *canvasStruct);
  bool isValidAdd(Command *commandStruct, Canvas *canvasStruct);
  bool isValidDelete(Command *commandStruct, Canvas *canvasStruct);
  bool isValidSaveOrLoad(Command *commandStruct);

#endif //FINAL_VALID_H
