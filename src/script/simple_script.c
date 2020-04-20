// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "simple_script.h"

#include "bleu/v1/heap.h"
#include "script/script_base_protected.h"

typedef struct {
  ScriptBaseStruct base;
  DoScriptDelegate Do;
} SimpleScriptStruct, *SimpleScript;

static void Delete(Command* self) { heap->Delete((void**)self); }

static void Do(Command base) {
  SimpleScript self = (SimpleScript)base;
  self->base.error = self->Do();
  _scriptBase->Notify((ScriptBase)self);
}

static Command New(const char* name, DoScriptDelegate delegate) {
  SimpleScript self = (SimpleScript)heap->New(sizeof(SimpleScriptStruct));
  self->base.impl.Delete = Delete;
  self->base.impl.Do = Do;
  self->base.name = name;
  self->Do = delegate;
  return (Command)self;
}

static const SimpleScriptMethodStruct kTheMethod = {
    .New = New,
};

const SimpleScriptMethod simpleScript = &kTheMethod;
