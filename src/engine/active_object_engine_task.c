// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "active_object_engine_task.h"

#include <stddef.h>

#include "bleu/v1/heap.h"
#include "malkt/v1/objectizable_task.h"
#include "malkt/v1/simple_inbox.h"

typedef struct {
  ActiveObjectEngineInterfaceStruct impl;
  Task task;
  Inbox inbox;
  bool done;
} ActiveObjectEngineTaskStruct, *ActiveObjectEngineTask;

inline static Command BlockingGetCommand(ActiveObjectEngineTask self) {
  Command* c = inbox->BlockingGet(self->inbox);
  return c != NULL ? *c : NULL;
}

static void TaskAction(void* base) {
  ActiveObjectEngineTask self = (ActiveObjectEngineTask)base;
  Command c;
  while (!self->done)
    if ((c = BlockingGetCommand(self)) != NULL) c->Do(c);
}

inline static void AddCommand(ActiveObjectEngine self, Command c) {
  inbox->BlockingPost(((ActiveObjectEngineTask)self)->inbox, &c, sizeof(Command));
}

static void Delete(ActiveObjectEngine* base) {
  ActiveObjectEngineTask self = (ActiveObjectEngineTask)*base;
  self->done = true;
  AddCommand(*base, NULL);

  inbox->Delete(&self->inbox);
  task->Delete(&self->task);
  heap->Delete((void**)base);
}

static void Run(ActiveObjectEngine self) { task->Run(((ActiveObjectEngineTask)self)->task); }

static ActiveObjectEngine New(void) {
  ActiveObjectEngineTask self = (ActiveObjectEngineTask)heap->New(sizeof(ActiveObjectEngineTaskStruct));
  self->impl.Delete = Delete;
  self->impl.Run = Run;
  self->impl.AddCommand = AddCommand;
  self->task = objectizableTask->New(TaskAction, 4, 1024, self);
  self->inbox = simpleInbox->New(1024);
  return (ActiveObjectEngine)self;
}

static const ActiveObjectEngineTaskMethodStruct kTheMethod = {
    .New = New,
};

const ActiveObjectEngineTaskMethod activeObjectEngineTask = &kTheMethod;
