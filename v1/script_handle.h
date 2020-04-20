// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_SCRIPT_HANDLE_H_
#define V1_SCRIPT_HANDLE_H_

#include <stdbool.h>

#include "bleu/v1/runtime_error.h"

typedef struct ScriptHandleInterfaceStruct* ScriptHandle;
typedef struct ScriptHandleInterfaceStruct {
  void (*Delete)(ScriptHandle* self);
  bool (*NeedsExecute)(ScriptHandle self);
  bool (*AssertPrecondition)(ScriptHandle self);
  void (*Init)(ScriptHandle self);
  bool (*Done)(ScriptHandle self);
  void (*Idle)(ScriptHandle self);
  bool (*AssertPostcondition)(ScriptHandle self);
  void (*CleanUp)(ScriptHandle self);
  RuntimeError (*GetError)(ScriptHandle self);
} ScriptHandleInterfaceStruct;

#endif  // V1_SCRIPT_HANDLE_H_
