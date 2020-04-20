// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "script_base.h"

#include "script/script_base_protected.h"

static void Delete(Command* self) { (*self)->Delete(self); }

static void Run(Command self) { self->Do(self); }

static void SetEngine(Command self, ActiveObjectEngine engine) { ((ScriptBase)self)->engine = engine; }

static void SetNotificationComand(Command self, Command notification_command) {
  ((ScriptBase)self)->notification_command = notification_command;
}

static const char* GetName(Command self) { return ((ScriptBase)self)->name; }

static int GetErrorCode(Command self) { return ((ScriptBase)self)->error_code; }

static bool HasError(Command self) { return ((ScriptBase)self)->error_code != 0; }

static const ScriptAbstractMethodStruct kTheMethod = {
    .Delete = Delete,
    .Run = Run,
    .SetEngine = SetEngine,
    .SetNotificationComand = SetNotificationComand,
    .GetName = GetName,
    .GetErrorCode = GetErrorCode,
    .HasError = HasError,
};

const ScriptAbstractMethod scriptBase = &kTheMethod;
