// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_SCRIPT_STRATEGY_H_
#define V1_SCRIPT_STRATEGY_H_

#include "script_base.h"
#include "script_handle.h"

typedef struct {
  Command (*New)(
      const char *name,
      ScriptHandle handle);  // ScriptHandle will be automatically destroyed when ScriptStrategy is destroyed.
} ScriptStrategyMethodStruct;
typedef const ScriptStrategyMethodStruct *ScriptStrategyMethod;

extern const ScriptStrategyMethod scriptStrategy;

#endif  // V1_SCRIPT_STRATEGY_H_
