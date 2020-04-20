// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "counting_command_stub.h"
#include "default_active_object_engine.h"
#include "simple_script.h"
}

namespace {
bool was_ran;
RuntimeError error;

RuntimeError DoSpy(void) {
  was_ran = true;
  return error;
}
}

class SimpleScriptTest : public ::testing::Test {
 protected:
  ActiveObjectEngine e;
  Command c;
  Command script;

  virtual void SetUp() {
    was_ran = false;
    error = runtimeError->New(kAssertionError, "This is just a test.", 0xdeadbeef);
    e = defaultActiveObjectEngine->New();
    c = countingCommandStub->New();
    script = simpleScript->New("test", DoSpy);
    scriptBase->SetEngine(script, e);
    scriptBase->SetNotificationComand(script, c);
  }

  virtual void TearDown() {
    script->Delete(&script);
    c->Delete(&c);
    e->Delete(&e);
    runtimeError->Delete(&error);
  }
};

TEST_F(SimpleScriptTest, Do) {
  script->Do(script);

  EXPECT_TRUE(was_ran);
  EXPECT_EQ(error, scriptBase->GetError(script));
}

TEST_F(SimpleScriptTest, Run) {
  e->AddCommand(e, script);
  e->Run(e);

  EXPECT_EQ(1, countingCommandStub->DoCount(c));
}
