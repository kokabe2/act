// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "script_strategy.h"

#include "bleu/v1/heap.h"
#include "script/script_base_protected.h"

typedef struct {
  ScriptBaseStruct base;
  ScriptHandle handle;
  bool started;
} ScriptStrategyStruct, *ScriptStrategy;

static void Delete(Command* base) {
  ScriptHandle h = ((ScriptStrategy)*base)->handle;
  h->Delete(&h);
  heap->Delete((void**)base);
}

static void Do(Command base) {
  ScriptStrategy self = (ScriptStrategy)base;
  ScriptHandle h = (ScriptHandle)self->handle;
  ActiveObjectEngine e = (ActiveObjectEngine)self->base.engine;
  if (!self->started) {
    if (!h->NeedsExecute(h)) {
      e->AddCommand(e, self->base.notification_command);
    } else if (!h->AssertPrecondition(h)) {
      self->base.error = h->GetError(h);
      e->AddCommand(e, self->base.notification_command);
    } else {
      self->started = true;
      h->Init(h);
      e->AddCommand(e, base);
    }
  } else if (h->Done(h)) {
    if (!h->AssertPostcondition(h)) self->base.error = h->GetError(h);
    h->CleanUp(h);
    e->AddCommand(e, self->base.notification_command);
  } else {
    h->Idle(h);
    e->AddCommand(e, base);
  }
}

static Command New(const char* name, ScriptHandle handle) {
  ScriptStrategy self = heap->New(sizeof(ScriptStrategyStruct));
  self->base.impl.Delete = Delete;
  self->base.impl.Do = Do;
  self->base.name = name;
  self->handle = handle;
  return (Command)self;
}

static const ScriptStrategyMethodStruct kTheMethod = {
    .New = New,
};

const ScriptStrategyMethod scriptStrategy = &kTheMethod;
