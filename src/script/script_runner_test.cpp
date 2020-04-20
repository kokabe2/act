// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "counting_command_stub.h"
#include "default_active_object_engine.h"
#include "script/script_spy.h"
#include "script_runner.h"
}

class ScriptRunnerTest : public ::testing::Test {
 protected:
  static const int kScriptSpysNum = 16;
  static const int kFailedScriptIndex = 8;
  RuntimeError error;
  ActiveObjectEngine e;
  Command c;
  Command script_spys[kScriptSpysNum];
  Command runner;

  virtual void SetUp() {
    NewSpyScripts();
    error = runtimeError->New(kAssertionError, "This is just a test.", 0xdeadbeef);
    e = defaultActiveObjectEngine->New();
    c = countingCommandStub->New();
    runner = scriptRunner->New();
    scriptBase->SetEngine(runner, e);
    scriptBase->SetNotificationComand(runner, c);
  }

  virtual void TearDown() {
    if (runner != NULL) runner->Delete(&runner);
    countingCommandStub->Delete(&c);
    e->Delete(&e);
    for (int i = 0; i < kScriptSpysNum; ++i) scriptSpy->Delete(&script_spys[i]);
    runtimeError->Delete(&error);
  }

  void NewSpyScripts() {
    for (int i = 0; i < kScriptSpysNum; ++i) {
      if (i == kFailedScriptIndex)
        script_spys[i] = scriptSpy->New("failed");
      else if (i == kScriptSpysNum - 1)
        script_spys[i] = scriptSpy->New("last");
      else
        script_spys[i] = scriptSpy->New("test");
    }
  }

  void AddAllScripts() {
    for (int i = 0; i < kScriptSpysNum; ++i) scriptRunner->AddScript(runner, script_spys[i]);
  }
};

TEST_F(ScriptRunnerTest, AddOneScript) {
  scriptRunner->AddScript(runner, script_spys[0]);

  e->AddCommand(e, runner);
  e->Run(e);

  EXPECT_STREQ("test", scriptBase->GetName(runner));
  EXPECT_EQ(NULL, scriptBase->GetError(runner));
  EXPECT_TRUE(scriptSpy->RunCalled(script_spys[0]));
  EXPECT_EQ(1, countingCommandStub->DoCount(c));
}

TEST_F(ScriptRunnerTest, AddScripts) {
  AddAllScripts();

  e->AddCommand(e, runner);
  e->Run(e);

  EXPECT_STREQ("last", scriptBase->GetName(runner));
  EXPECT_EQ(NULL, scriptBase->GetError(runner));
  for (int i = 0; i < kScriptSpysNum; ++i)
    EXPECT_TRUE(scriptSpy->RunCalled(script_spys[i])) << "Failure at index " << i;
  EXPECT_EQ(1, countingCommandStub->DoCount(c));
}

TEST_F(ScriptRunnerTest, RunWhenScriptErrorOccurs) {
  scriptSpy->SetError(script_spys[kFailedScriptIndex], error);
  AddAllScripts();

  e->AddCommand(e, runner);
  e->Run(e);

  EXPECT_STREQ("failed", scriptBase->GetName(runner));
  EXPECT_EQ(error, scriptBase->GetError(runner));
  for (int i = 0; i <= kFailedScriptIndex; ++i)
    EXPECT_TRUE(scriptSpy->RunCalled(script_spys[i])) << "Failure at index " << i;
  for (int i = kFailedScriptIndex + 1; i < kScriptSpysNum; ++i)
    EXPECT_FALSE(scriptSpy->RunCalled(script_spys[i])) << "Failure at index " << i;
  EXPECT_EQ(1, countingCommandStub->DoCount(c));
}

TEST_F(ScriptRunnerTest, RunWhenScriptErrorOccursInLastScript) {
  scriptSpy->SetError(script_spys[kScriptSpysNum - 1], error);
  AddAllScripts();

  e->AddCommand(e, runner);
  e->Run(e);

  EXPECT_STREQ("last", scriptBase->GetName(runner));
  EXPECT_EQ(error, scriptBase->GetError(runner));
  for (int i = 0; i <= kScriptSpysNum; ++i)
    EXPECT_TRUE(scriptSpy->RunCalled(script_spys[i])) << "Failure at index " << i;
  EXPECT_EQ(1, countingCommandStub->DoCount(c));
}

TEST_F(ScriptRunnerTest, AllScriptsAddedIsDestroyedWhenDone) {
  AddAllScripts();

  runner->Delete(&runner);

  for (int i = 0; i < kScriptSpysNum; ++i)
    EXPECT_TRUE(scriptSpy->DeleteCalled(script_spys[i])) << "Failure at index " << i;
}
