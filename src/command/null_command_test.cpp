// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "null_command.h"
}

TEST(NullCommandTest, DoHasNoEffect) {
  Command c = nullCommand->GetInstance();

  c->Do(c);
}

TEST(NullCommandTest, DeleteHasNoEffect) {
  Command c = nullCommand->GetInstance();

  c->Delete(&c);
}
