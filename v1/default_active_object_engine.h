// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_DEFAULT_ACTIVE_OBJECT_ENGINE_H_
#define V1_DEFAULT_ACTIVE_OBJECT_ENGINE_H_

#include "active_object_engine.h"

typedef struct {
  ActiveObjectEngine (*New)(void);  //
} DefaultActiveObjectEngineMethodStruct;
typedef const DefaultActiveObjectEngineMethodStruct* DefaultActiveObjectEngineMethod;

extern const DefaultActiveObjectEngineMethod defaultActiveObjectEngine;

#endif  // V1_DEFAULT_ACTIVE_OBJECT_ENGINE_H_
