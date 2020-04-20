// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_SCRIPT_SCRIPT_HANDLE_SPY_H_
#define SRC_SCRIPT_SCRIPT_HANDLE_SPY_H_

#include "script_handle.h"

typedef struct {
  ScriptHandle (*New)(void);
  void (*Delete)(ScriptHandle* self);
  bool (*DeleteCalled)(ScriptHandle self);
  void (*NoNeedToExecute)(ScriptHandle self);
  void (*SetPreconditionError)(ScriptHandle self, RuntimeError error);
  bool (*InitCalled)(ScriptHandle self);
  void (*SetCountToDone)(ScriptHandle self, int count);
  int (*IdleCalledCount)(ScriptHandle self);
  void (*SetPostconditionError)(ScriptHandle self, RuntimeError error);
  bool (*CleanUpCalled)(ScriptHandle self);
} ScriptHandleSpyMethodStruct;
typedef const ScriptHandleSpyMethodStruct* ScriptHandleSpyMethod;

extern const ScriptHandleSpyMethod scriptHandleSpy;

#endif  // SRC_SCRIPT_SCRIPT_HANDLE_SPY_H_
