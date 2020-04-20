// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_ACTIVE_OBJECT_ENGINE_H_
#define V1_ACTIVE_OBJECT_ENGINE_H_

#include "command.h"

typedef struct ActiveObjectEngineInterfaceStruct* ActiveObjectEngine;
typedef struct ActiveObjectEngineInterfaceStruct {
  void (*Delete)(ActiveObjectEngine* self);
  void (*Run)(ActiveObjectEngine self);
  void (*AddCommand)(ActiveObjectEngine self, Command c);
} ActiveObjectEngineInterfaceStruct;

#endif  // V1_ACTIVE_OBJECT_ENGINE_H_
