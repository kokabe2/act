// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_SCRIPT_RUNNER_H_
#define V1_SCRIPT_RUNNER_H_

#include "script_base.h"

typedef struct {
  Command (*New)(void);
  void (*AddScript)(Command self,
                    Command script);  // Added scripts will be automatically destroyed when ScriptRunner is destroyed.
} ScriptRunnerMethodStruct;
typedef const ScriptRunnerMethodStruct* ScriptRunnerMethod;

extern const ScriptRunnerMethod scriptRunner;

#endif  // V1_SCRIPT_RUNNER_H_
