// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#ifndef SRC_UTIL_TIME_UNIT_STUB_H_
#define SRC_UTIL_TIME_UNIT_STUB_H_

#include "malkt/v1/time_unit.h"

typedef struct {
  void (*Reset)(int64_t now, int64_t inc);  //
} TimeUnitStubMethodStruct;
typedef const TimeUnitStubMethodStruct* TimeUnitStubMethod;

extern const TimeUnitStubMethod timeUnitStub;

#endif  // SRC_UTIL_TIME_UNIT_STUB_H_
