// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "counting_command_stub.h"
}

class CountingCommandStubTest : public ::testing::Test {
 protected:
  Command c;

  virtual void SetUp() { c = countingCommandStub->New(); }

  virtual void TearDown() { countingCommandStub->Delete(&c); }
};

TEST_F(CountingCommandStubTest, ConditionAfterCreation) {
  EXPECT_EQ(0, countingCommandStub->DeleteCount(c));
  EXPECT_EQ(0, countingCommandStub->DoCount(c));
}

TEST_F(CountingCommandStubTest, DeleteCount) {
  c->Delete(&c);
  c->Delete(&c);
  c->Delete(&c);

  EXPECT_EQ(3, countingCommandStub->DeleteCount(c));
  EXPECT_EQ(0, countingCommandStub->DoCount(c));
}

TEST_F(CountingCommandStubTest, DoCount) {
  c->Do(c);
  c->Do(c);
  c->Do(c);

  EXPECT_EQ(0, countingCommandStub->DeleteCount(c));
  EXPECT_EQ(3, countingCommandStub->DoCount(c));
}

TEST_F(CountingCommandStubTest, Count) {
  c->Do(c);
  c->Do(c);
  c->Delete(&c);

  EXPECT_EQ(1, countingCommandStub->DeleteCount(c));
  EXPECT_EQ(2, countingCommandStub->DoCount(c));
}
