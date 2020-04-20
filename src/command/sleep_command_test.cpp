// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "counting_command_stub.h"
#include "default_active_object_engine.h"
#include "sleep_command.h"
#include "util/time_unit_stub.h"
}

class SleepCommandTest : public ::testing::Test {
 protected:
  ActiveObjectEngine e;
  Command wakeup;
  Command c;

  virtual void SetUp() {
    timeUnitStub->Reset(0, 20);
    wakeup = countingCommandStub->New();
    e = defaultActiveObjectEngine->New();
    c = sleepCommand->New(100, e, wakeup);
  }

  virtual void TearDown() {
    c->Delete(&c);
    e->Delete(&e);
    wakeup->Delete(&wakeup);
  }
};

TEST_F(SleepCommandTest, Run) {
  e->AddCommand(e, c);

  e->Run(e);

  EXPECT_EQ(1, countingCommandStub->DoCount(wakeup));
  int64_t t = timeUnit->Now(timeUnit->Millisecond);
  EXPECT_GE(t, 100);
  EXPECT_LE(t, 120);
}
