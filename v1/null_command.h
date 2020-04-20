// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_NULL_COMMAND_H_
#define V1_NULL_COMMAND_H_

#include "command.h"

typedef struct {
  Command (*GetInstance)(void);  //
} NullCommandMethodStruct;
typedef const NullCommandMethodStruct* NullCommandMethod;

extern const NullCommandMethod nullCommand;

#endif  // V1_NULL_COMMAND_H_
