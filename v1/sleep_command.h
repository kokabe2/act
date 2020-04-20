// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef V1_SLEEP_COMMAND_H_
#define V1_SLEEP_COMMAND_H_

#include "active_object_engine.h"
#include "command.h"

typedef struct {
  Command (*New)(int milliseconds, ActiveObjectEngine engine, Command wakeup_command);
} SleepCommandMethodStruct;
typedef const SleepCommandMethodStruct* SleepCommandMethod;

extern const SleepCommandMethod sleepCommand;

#endif  // V1_SLEEP_COMMAND_H_
