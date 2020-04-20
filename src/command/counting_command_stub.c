// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "counting_command_stub.h"

#include "bleu/v1/heap.h"

typedef struct {
  CommandInterfaceStruct impl;
  int delete_count;
  int do_count;
} CountingCommandStubStruct, *CountingCommandStub;

static void DeleteSpy(Command *self) { ++((CountingCommandStub)*self)->delete_count; }

static void DoSpy(Command self) { ++((CountingCommandStub)self)->do_count; }

static Command New(void) {
  CountingCommandStub self = (CountingCommandStub)heap->New(sizeof(CountingCommandStubStruct));
  self->impl.Delete = DeleteSpy;
  self->impl.Do = DoSpy;
  return (Command)self;
}

static void Delete(Command *self) { heap->Delete((void **)self); }

static int DeleteCount(Command self) { return ((CountingCommandStub)self)->delete_count; }

static int DoCount(Command self) { return ((CountingCommandStub)self)->do_count; }

static const CountingCommandStubMethodStruct kTheMethod = {
    .New = New,
    .Delete = Delete,
    .DeleteCount = DeleteCount,
    .DoCount = DoCount,
};

const CountingCommandStubMethod countingCommandStub = &kTheMethod;
