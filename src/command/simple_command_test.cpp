// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "simple_command.h"
}

namespace {
bool was_ran;

void DoSpy(void) { was_ran = true; }
}

class SimpleCommandTest : public ::testing::Test {
 protected:
  Command c;

  virtual void SetUp() {
    was_ran = false;
    c = simpleCommand->New(DoSpy);
  }

  virtual void TearDown() { c->Delete(&c); }
};

TEST_F(SimpleCommandTest, Do) {
  c->Do(c);

  EXPECT_TRUE(was_ran);
}
