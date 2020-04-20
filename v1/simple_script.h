// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_SIMPLE_SCRIPT_H_
#define V1_SIMPLE_SCRIPT_H_

#include "script_base.h"

typedef RuntimeError (*DoScriptDelegate)(void);
typedef struct {
  Command (*New)(const char *name, DoScriptDelegate delegate);  //
} SimpleScriptMethodStruct;
typedef const SimpleScriptMethodStruct *SimpleScriptMethod;

extern const SimpleScriptMethod simpleScript;

#endif  // V1_SIMPLE_SCRIPT_H_
