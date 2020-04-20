// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "script_base.h"

#include "script/script_base_protected.h"

static void Recurse(ScriptBase self) {
  ActiveObjectEngine e = self->engine;
  e->AddCommand(e, (Command)self);
}

static void Notify(ScriptBase self) {
  ActiveObjectEngine e = self->engine;
  e->AddCommand(e, self->notification_command);
}

static const ScriptBaseProtectedMethodStruct kProtectedMethod = {
    .Recurse = Recurse,
    .Notify = Notify,
};

const ScriptBaseProtectedMethod _scriptBase = &kProtectedMethod;

static void SetEngine(Command self, ActiveObjectEngine engine) { ((ScriptBase)self)->engine = engine; }

static void SetNotificationComand(Command self, Command notification_command) {
  ((ScriptBase)self)->notification_command = notification_command;
}

static const char* GetName(Command self) { return ((ScriptBase)self)->name; }

static bool HasError(Command self) { return ((ScriptBase)self)->error != NULL; }

static RuntimeError GetError(Command self) { return ((ScriptBase)self)->error; }

static const ScriptAbstractMethodStruct kTheMethod = {
    .SetEngine = SetEngine,
    .SetNotificationComand = SetNotificationComand,
    .GetName = GetName,
    .HasError = HasError,
    .GetError = GetError,
};

const ScriptAbstractMethod scriptBase = &kTheMethod;
