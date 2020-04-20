// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "counting_command_stub.h"
#include "default_active_object_engine.h"
#include "script/script_handle_spy.h"
#include "script_strategy.h"
}

class ScriptStrategyTest : public ::testing::Test {
 protected:
  RuntimeError error;
  ActiveObjectEngine e;
  Command c;
  ScriptHandle handle_spy;
  Command script;

  virtual void SetUp() {
    error = runtimeError->New(kAssertionError, "This is just a test.", 0xdeadbeef);
    e = defaultActiveObjectEngine->New();
    c = countingCommandStub->New();
    handle_spy = scriptHandleSpy->New();
    script = scriptStrategy->New("test", handle_spy);
    scriptBase->SetEngine(script, e);
    scriptBase->SetNotificationComand(script, c);
  }

  virtual void TearDown() {
    if (script != NULL) script->Delete(&script);
    countingCommandStub->Delete(&c);
    e->Delete(&e);
    scriptHandleSpy->Delete(&handle_spy);
    runtimeError->Delete(&error);
  }
};

TEST_F(ScriptStrategyTest, Run) {
  e->AddCommand(e, script);
  e->Run(e);

  EXPECT_STREQ("test", scriptBase->GetName(script));
  EXPECT_EQ(0, scriptBase->GetError(script));
  EXPECT_EQ(1, countingCommandStub->DoCount(c));
}

TEST_F(ScriptStrategyTest, RunWhenNoNeedToExecute) {
  scriptHandleSpy->NoNeedToExecute(handle_spy);

  e->AddCommand(e, script);
  e->Run(e);

  EXPECT_EQ(0, scriptBase->GetError(script));
  EXPECT_FALSE(scriptHandleSpy->InitCalled(handle_spy));
  EXPECT_EQ(0, scriptHandleSpy->IdleCalledCount(handle_spy));
  EXPECT_FALSE(scriptHandleSpy->CleanUpCalled(handle_spy));
}

TEST_F(ScriptStrategyTest, RunWhenPreconditionAssertionFailed) {
  scriptHandleSpy->SetPreconditionError(handle_spy, error);

  e->AddCommand(e, script);
  e->Run(e);

  EXPECT_EQ(error, scriptBase->GetError(script));
  EXPECT_FALSE(scriptHandleSpy->InitCalled(handle_spy));
  EXPECT_EQ(0, scriptHandleSpy->IdleCalledCount(handle_spy));
  EXPECT_FALSE(scriptHandleSpy->CleanUpCalled(handle_spy));
}

TEST_F(ScriptStrategyTest, RunWhenPostconditionAssertionFailed) {
  scriptHandleSpy->SetPostconditionError(handle_spy, error);

  e->AddCommand(e, script);
  e->Run(e);

  EXPECT_EQ(error, scriptBase->GetError(script));
  EXPECT_TRUE(scriptHandleSpy->InitCalled(handle_spy));
  EXPECT_EQ(0, scriptHandleSpy->IdleCalledCount(handle_spy));
  EXPECT_TRUE(scriptHandleSpy->CleanUpCalled(handle_spy));
}

TEST_F(ScriptStrategyTest, RunWhenTakesSomeTimeToDone) {
  scriptHandleSpy->SetCountToDone(handle_spy, 10);

  e->AddCommand(e, script);
  e->Run(e);

  EXPECT_EQ(0, scriptBase->GetError(script));
  EXPECT_TRUE(scriptHandleSpy->InitCalled(handle_spy));
  EXPECT_EQ(10 - 1, scriptHandleSpy->IdleCalledCount(handle_spy));
  EXPECT_TRUE(scriptHandleSpy->CleanUpCalled(handle_spy));
}

TEST_F(ScriptStrategyTest, DeleteDestroysCommandScriptHandle) {
  script->Delete(&script);

  EXPECT_TRUE(scriptHandleSpy->DeleteCalled(handle_spy));
}
