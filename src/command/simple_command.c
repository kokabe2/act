// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "simple_command.h"

#include "bleu/v1/heap.h"

typedef struct {
  CommandInterfaceStruct impl;
  DoCommandDelegate Do;
} SimpleCommandStruct, *SimpleCommand;

static void Delete(Command *self) { heap->Delete((void **)self); }

static void Do(Command self) { ((SimpleCommand)self)->Do(); }

static Command New(DoCommandDelegate delegate) {
  SimpleCommand self = heap->New(sizeof(SimpleCommandStruct));
  self->impl.Delete = Delete;
  self->impl.Do = Do;
  self->Do = delegate;
  return (Command)self;
}

static const SimpleCommandMethodStruct kTheMethod = {
    .New = New,
};

const SimpleCommandMethod simpleCommand = &kTheMethod;
