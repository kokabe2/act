// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "script/script_handle_spy.h"

#include "bleu/v1/heap.h"

typedef struct {
  ScriptHandleInterfaceStruct impl;
  bool deleted;
  bool needs;
  bool precondition;
  bool init_called;
  int count_for_done;
  int done_callde_count;
  int idle_callde_count;
  bool postcondition;
  bool clenup_called;
  RuntimeError error;
} ScriptHandleSpyStruct, *ScriptHandleSpy;

static void DeleteSpy(ScriptHandle* self) { ((ScriptHandleSpy)*self)->deleted = true; }

static bool NeedsExecute(ScriptHandle self) { return ((ScriptHandleSpy)self)->needs; }

static bool AssertPrecondition(ScriptHandle self) { return ((ScriptHandleSpy)self)->precondition; }

static void Init(ScriptHandle self) { ((ScriptHandleSpy)self)->init_called = true; }

static bool Done(ScriptHandle self) {
  return ++((ScriptHandleSpy)self)->done_callde_count >= ((ScriptHandleSpy)self)->count_for_done;
}

static void Idle(ScriptHandle self) { ((ScriptHandleSpy)self)->idle_callde_count++; }

static bool AssertPostcondition(ScriptHandle self) { return ((ScriptHandleSpy)self)->postcondition; }

static void CleanUp(ScriptHandle self) { ((ScriptHandleSpy)self)->clenup_called = true; }

static RuntimeError GetError(ScriptHandle self) { return ((ScriptHandleSpy)self)->error; }

static ScriptHandle New(void) {
  ScriptHandleSpy self = (ScriptHandleSpy)heap->New(sizeof(ScriptHandleSpyStruct));
  self->impl.Delete = DeleteSpy;
  self->impl.NeedsExecute = NeedsExecute;
  self->impl.AssertPrecondition = AssertPrecondition;
  self->impl.Init = Init;
  self->impl.Done = Done;
  self->impl.Idle = Idle;
  self->impl.AssertPostcondition = AssertPostcondition;
  self->impl.CleanUp = CleanUp;
  self->impl.GetError = GetError;
  self->needs = true;
  self->precondition = true;
  self->postcondition = true;
  return (ScriptHandle)self;
}

static void Delete(ScriptHandle* self) { heap->Delete((void**)self); }

static bool DeleteCalled(ScriptHandle self) { return ((ScriptHandleSpy)self)->deleted; }

static void NoNeedToExecute(ScriptHandle self) { ((ScriptHandleSpy)self)->needs = false; }

static void SetPreconditionError(ScriptHandle self, RuntimeError error) {
  ((ScriptHandleSpy)self)->error = error;
  ((ScriptHandleSpy)self)->precondition = false;
}

static bool InitCalled(ScriptHandle self) { return ((ScriptHandleSpy)self)->init_called; }

static void SetCountToDone(ScriptHandle self, int count) { ((ScriptHandleSpy)self)->count_for_done = count; }

static int IdleCalledCount(ScriptHandle self) { return ((ScriptHandleSpy)self)->idle_callde_count; }

static void SetPostconditionError(ScriptHandle self, RuntimeError error) {
  ((ScriptHandleSpy)self)->error = error;
  ((ScriptHandleSpy)self)->postcondition = false;
}

static bool CleanUpCalled(ScriptHandle self) { return ((ScriptHandleSpy)self)->clenup_called; }

static void SetErrorCode(ScriptHandle self, RuntimeError error) { ((ScriptHandleSpy)self)->error = error; }

static const ScriptHandleSpyMethodStruct kTheMethod = {
    .New = New,
    .Delete = Delete,
    .DeleteCalled = DeleteCalled,
    .NoNeedToExecute = NoNeedToExecute,
    .SetPreconditionError = SetPreconditionError,
    .InitCalled = InitCalled,
    .SetCountToDone = SetCountToDone,
    .IdleCalledCount = IdleCalledCount,
    .SetPostconditionError = SetPostconditionError,
    .CleanUpCalled = CleanUpCalled,
};

const ScriptHandleSpyMethod scriptHandleSpy = &kTheMethod;
