// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "default_active_object_engine.h"

#include <stddef.h>

#include "bleu/v1/heap.h"
#include "bleu/v1/list.h"

typedef struct {
  ActiveObjectEngineInterfaceStruct impl;
  List commands;
} DefaultActiveObjectEngineStruct, *DefaultActiveObjectEngine;

static void Delete(ActiveObjectEngine* self) {
  list->Delete(&((DefaultActiveObjectEngine)*self)->commands);
  heap->Delete((void**)self);
}

inline static Command GetNexeCommand(DefaultActiveObjectEngine self) { return list->Pop(self->commands, 0); }

static void Run(ActiveObjectEngine self) {
  Command c;
  while ((c = GetNexeCommand((DefaultActiveObjectEngine)self)) != NULL) c->Do(c);
}

static void AddCommand(ActiveObjectEngine self, Command c) {
  list->Add(((DefaultActiveObjectEngine)self)->commands, c);
}

static ActiveObjectEngine New(void) {
  DefaultActiveObjectEngine self = (DefaultActiveObjectEngine)heap->New(sizeof(DefaultActiveObjectEngineStruct));
  self->impl.Delete = Delete;
  self->impl.Run = Run;
  self->impl.AddCommand = AddCommand;
  self->commands = list->New();
  return (ActiveObjectEngine)self;
}

static const DefaultActiveObjectEngineMethodStruct kTheMethod = {
    .New = New,
};

const DefaultActiveObjectEngineMethod defaultActiveObjectEngine = &kTheMethod;
