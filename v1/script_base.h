﻿// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_SCRIPT_BASE_H_
#define V1_SCRIPT_BASE_H_

#include <stdbool.h>

#include "active_object_engine.h"
#include "bleu/v1/runtime_error.h"

typedef struct {
  void (*SetEngine)(Command self, ActiveObjectEngine engine);
  void (*SetNotificationComand)(Command self, Command notification_command);
  const char *(*GetName)(Command self);
  bool (*HasError)(Command self);
  RuntimeError (*GetError)(Command self);
} ScriptAbstractMethodStruct;
typedef const ScriptAbstractMethodStruct *ScriptAbstractMethod;

extern const ScriptAbstractMethod scriptBase;

#endif  // V1_SCRIPT_BASE_H_
