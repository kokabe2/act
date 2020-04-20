// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_SCRIPT_SCRIPT_SPY_H_
#define SRC_SCRIPT_SCRIPT_SPY_H_

#include "script_base.h"

typedef struct {
  Command (*New)(const char* name);
  void (*Delete)(Command* self);
  bool (*DeleteCalled)(Command self);
  bool (*RunCalled)(Command self);
  ActiveObjectEngine (*GetEngine)(Command self);
  Command (*GetNotificationCommand)(Command self);
  void (*SetErrorCode)(Command self, int error_code);
} ScriptSpyMethodStruct;
typedef const ScriptSpyMethodStruct* ScriptSpyMethod;

extern const ScriptSpyMethod scriptSpy;

#endif  // SRC_SCRIPT_SCRIPT_SPY_H_
