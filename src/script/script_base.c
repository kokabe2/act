// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "script_base.h"

#include "script/script_base_protected.h"

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
