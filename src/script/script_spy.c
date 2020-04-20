// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "script/script_spy.h"

#include "bleu/v1/heap.h"
#include "script/script_base_protected.h"

typedef struct {
  ScriptBaseStruct base;
  bool deleted;
  bool done;
} ScriptSpyStruct, *ScriptSpy;

static void DeleteSpy(Command* self) { ((ScriptSpy)*self)->deleted = true; }

static void DoSpy(Command base) {
  ScriptSpy self = (ScriptSpy)base;
  ActiveObjectEngine e = self->base.engine;
  self->done = true;
  e->AddCommand(e, self->base.notification_command);
}

static Command New(const char* name) {
  ScriptSpy self = (ScriptSpy)heap->New(sizeof(ScriptSpyStruct));
  self->base.impl.Delete = DeleteSpy;
  self->base.impl.Do = DoSpy;
  self->base.name = name;
  return (Command)self;
}

static void Delete(Command* self) { heap->Delete((void**)self); }

static bool DeleteCalled(Command self) { return ((ScriptSpy)self)->deleted; }

static bool RunCalled(Command self) { return ((ScriptSpy)self)->done; }

static ActiveObjectEngine GetEngine(Command self) { return ((ScriptBase)self)->engine; }

static Command GetNotificationCommand(Command self) { return ((ScriptBase)self)->notification_command; }

static void SetError(Command self, RuntimeError error) { ((ScriptBase)self)->error = error; }

static const ScriptSpyMethodStruct kTheMethod = {
    .New = New,
    .Delete = Delete,
    .DeleteCalled = DeleteCalled,
    .RunCalled = RunCalled,
    .GetEngine = GetEngine,
    .GetNotificationCommand = GetNotificationCommand,
    .SetError = SetError,
};

const ScriptSpyMethod scriptSpy = &kTheMethod;
