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
  if (!self->started) {
    if (!h->NeedsExecute(h)) {
      _scriptBase->Notify((ScriptBase)self);
    } else if (!h->AssertPrecondition(h)) {
      self->base.error = h->GetError(h);
      _scriptBase->Notify((ScriptBase)self);
    } else {
      self->started = true;
      h->Init(h);
      _scriptBase->Recurse((ScriptBase)self);
    }
  } else if (h->Done(h)) {
    if (!h->AssertPostcondition(h)) self->base.error = h->GetError(h);
    h->CleanUp(h);
    _scriptBase->Notify((ScriptBase)self);
  } else {
    h->Idle(h);
    _scriptBase->Recurse((ScriptBase)self);
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
