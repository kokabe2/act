// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "script_runner.h"

#include "bleu/v1/heap.h"
#include "bleu/v1/list.h"
#include "script/script_base_protected.h"

typedef struct {
  ScriptBaseStruct base;
  List scripts;
  int count;
} ScriptRunnerStruct, *ScriptRunner;

inline static void Delete(Command* base) {
  ScriptRunner self = (ScriptRunner)*base;
  list->Delete(&self->scripts);
  heap->Delete((void**)base);
}

inline static void SetUpNextScript(ScriptRunner self) {
  ActiveObjectEngine e = self->base.engine;
  Command script = list->Get(self->scripts, self->count++);
  scriptBase->SetEngine(script, e);
  scriptBase->SetNotificationComand(script, (Command)self);
  e->AddCommand(e, script);
}

inline static bool AllScriptsDone(ScriptRunner self) { return self->count == list->Count(self->scripts); }

inline static Command GetLastScript(ScriptRunner self) { return list->Get(self->scripts, self->count - 1); }

inline static bool HasErrorWithLastScript(ScriptRunner self) {
  return self->count != 0 ? scriptBase->HasError(GetLastScript(self)) : false;
}

inline static void CleanUp(ScriptRunner self) {
  ActiveObjectEngine e = self->base.engine;
  Command script = GetLastScript(self);
  self->base.name = scriptBase->GetName(script);
  self->base.error = scriptBase->GetError(script);
  e->AddCommand(e, self->base.notification_command);
}

static void Do(Command base) {
  ScriptRunner self = (ScriptRunner)base;
  if (AllScriptsDone(self) || HasErrorWithLastScript(self))
    CleanUp(self);
  else
    SetUpNextScript(self);
}

static void ScriptDeleter(void** self) {
  Command c = (Command)*self;
  c->Delete((Command*)self);
}

static Command New(void) {
  ScriptRunner self = heap->New(sizeof(ScriptRunnerStruct));
  self->base.impl.Delete = Delete;
  self->base.impl.Do = Do;
  self->scripts = list->New();
  list->SetItemDeleter(self->scripts, ScriptDeleter);
  return (Command)self;
}

static void AddScript(Command self, Command script) { list->Add(((ScriptRunner)self)->scripts, script); }

static const ScriptRunnerMethodStruct kTheMethod = {
    .New = New,
    .AddScript = AddScript,
};

const ScriptRunnerMethod scriptRunner = &kTheMethod;
