// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "time_unit_stub.h"

static int64_t current_time = 0;
static int64_t increment = 0;

static int64_t Now(Duration d) {
  int64_t t = current_time;
  current_time += increment;
  return t;
}

static const TimeUnitMethodStruct kTheMethod = {
    .Now = Now,
};

const TimeUnitMethod timeUnit = &kTheMethod;

static void Reset(int64_t now, int64_t inc) {
  current_time = now;
  increment = inc;
}

static const TimeUnitStubMethodStruct kStubMethod = {
    .Reset = Reset,
};

const TimeUnitStubMethod timeUnitStub = &kStubMethod;
