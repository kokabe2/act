// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_SIMPLE_COMMAND_H_
#define V1_SIMPLE_COMMAND_H_

#include "command.h"

typedef void (*DoCommandDelegate)(void);
typedef struct {
  Command (*New)(DoCommandDelegate delegate);  //
} SimpleCommandMethodStruct;
typedef const SimpleCommandMethodStruct* SimpleCommandMethod;

extern const SimpleCommandMethod simpleCommand;

#endif  // V1_SIMPLE_COMMAND_H_
