// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "null_command.h"

#include <stddef.h>

#include "bleu/v1/heap.h"

static Command INSTANCE = NULL;

static void Delete(Command *self) {}

static void Do(Command self) {}

static Command New(void) {
  Command self = heap->New(sizeof(CommandInterfaceStruct));
  self->Delete = Delete;
  self->Do = Do;
  return self;
}

static Command GetInstance(void) {
  if (INSTANCE == NULL) INSTANCE = New();
  return INSTANCE;
}

static const NullCommandMethodStruct kTheMethod = {
    .GetInstance = GetInstance,
};

const NullCommandMethod nullCommand = &kTheMethod;
