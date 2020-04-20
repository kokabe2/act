// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "counting_command_stub.h"
#include "default_active_object_engine.h"
#include "script/script_spy.h"
}

class ScriptSpyTest : public ::testing::Test {
 protected:
  RuntimeError error;
  ActiveObjectEngine e;
  Command c;
  Command script;

  virtual void SetUp() {
    error = runtimeError->New(kAssertionError, "This is just a test.", 0xdeadbeef);
    e = defaultActiveObjectEngine->New();
    c = countingCommandStub->New();
    script = scriptSpy->New("test");
    scriptBase->SetEngine(script, e);
    scriptBase->SetNotificationComand(script, c);
  }

  virtual void TearDown() {
    scriptSpy->Delete(&script);
    c->Delete(&c);
    e->Delete(&e);
    runtimeError->Delete(&error);
  }
};

TEST_F(ScriptSpyTest, Delete) {
  script->Delete(&script);

  EXPECT_TRUE(scriptSpy->DeleteCalled(script));
}

TEST_F(ScriptSpyTest, Do) {
  script->Do(script);

  EXPECT_TRUE(scriptSpy->RunCalled(script));
}

TEST_F(ScriptSpyTest, SetEngine) { EXPECT_EQ(e, scriptSpy->GetEngine(script)); }

TEST_F(ScriptSpyTest, SetNotificationCommand) { EXPECT_EQ(c, scriptSpy->GetNotificationCommand(script)); }

TEST_F(ScriptSpyTest, GetName) { EXPECT_STREQ("test", scriptBase->GetName(script)); }

TEST_F(ScriptSpyTest, HasError) {
  scriptSpy->SetError(script, error);

  EXPECT_TRUE(scriptBase->HasError(script));
}

TEST_F(ScriptSpyTest, GetError) {
  scriptSpy->SetError(script, error);

  EXPECT_EQ(error, scriptBase->GetError(script));
}
