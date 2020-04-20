// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "counting_command_stub.h"
#include "default_active_object_engine.h"
}

class DefaultActiveObjectEngineTest : public ::testing::Test {
 protected:
  Command c;
  ActiveObjectEngine e;

  virtual void SetUp() {
    c = countingCommandStub->New();
    e = defaultActiveObjectEngine->New();
  }

  virtual void TearDown() {
    e->Delete(&e);
    c->Delete(&c);
  }
};

TEST_F(DefaultActiveObjectEngineTest, Run) {
  e->AddCommand(e, c);

  e->Run(e);

  EXPECT_EQ(1, countingCommandStub->DoCount(c));
}

TEST_F(DefaultActiveObjectEngineTest, RunWhenNoCommandAddedHasNoEffect) {
  e->Run(e);

  SUCCEED();
}

TEST_F(DefaultActiveObjectEngineTest, AddCommandMultipleTimes) {
  e->AddCommand(e, c);
  e->AddCommand(e, c);
  e->AddCommand(e, c);

  e->Run(e);

  EXPECT_EQ(3, countingCommandStub->DoCount(c));
}
