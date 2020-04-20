// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "sleep_command.h"

#include <stdbool.h>

#include "bleu/v1/heap.h"
#include "malkt/v1/time_unit.h"

typedef struct {
  CommandInterfaceStruct impl;
  int sleep_time;
  ActiveObjectEngine engine;
  Command wakeup_command;
  bool started;
  int64_t start_time;
} SleepCommandStruct, *SleepCommand;

static void Delete(Command *self) { heap->Delete((void **)self); }

inline static bool ShouldWakeUp(SleepCommand self, int64_t current_time) {
  return current_time >= self->start_time + self->sleep_time;
}

static void Do(Command base) {
  int64_t current_time = timeUnit->Now(timeUnit->Millisecond);
  SleepCommand self = (SleepCommand)base;
  ActiveObjectEngine e = self->engine;
  if (!self->started) {
    self->started = true;
    self->start_time = current_time;
    e->AddCommand(e, base);
  } else if (ShouldWakeUp(self, current_time)) {
    e->AddCommand(e, self->wakeup_command);
  } else {
    e->AddCommand(e, base);
  }
}

static Command New(int milliseconds, ActiveObjectEngine engine, Command wakeup_command) {
  SleepCommand self = heap->New(sizeof(SleepCommandStruct));
  self->impl.Delete = Delete;
  self->impl.Do = Do;
  self->sleep_time = milliseconds;
  self->engine = engine;
  self->wakeup_command = wakeup_command;
  return (Command)self;
}

static const SleepCommandMethodStruct kTheMethod = {
    .New = New,
};

const SleepCommandMethod sleepCommand = &kTheMethod;
