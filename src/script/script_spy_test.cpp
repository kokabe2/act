// Copyright(c) 2020 Ken Okabe
// This software is released under the MIT License, see LICENSE.
#include "gtest/gtest.h"

extern "C" {
#include "counting_command_stub.h"
#include "default_active_object_engine.h"
#include "script/script_spy.h"
}

class ScriptTest : public ::testing::Test {
 protected:
  ActiveObjectEngine e;
  Command c;
  Command script;

  virtual void SetUp() {
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
  }
};

TEST_F(ScriptTest, Delete) {
  scriptBase->Delete(&script);

  EXPECT_TRUE(scriptSpy->DeleteCalled(script));
}

TEST_F(ScriptTest, Run) {
  scriptBase->Run(script);

  EXPECT_TRUE(scriptSpy->RunCalled(script));
}

TEST_F(ScriptTest, SetEngine) { EXPECT_EQ(e, scriptSpy->GetEngine(script)); }

TEST_F(ScriptTest, SetNotificationCommand) { EXPECT_EQ(c, scriptSpy->GetNotificationCommand(script)); }

TEST_F(ScriptTest, GetName) { EXPECT_STREQ("test", scriptBase->GetName(script)); }

TEST_F(ScriptTest, GetErrorCode) {
  scriptSpy->SetErrorCode(script, 1234);

  EXPECT_EQ(1234, scriptBase->GetErrorCode(script));
}

TEST_F(ScriptTest, HasError) {
  scriptSpy->SetErrorCode(script, 1234);

  EXPECT_TRUE(scriptBase->HasError(script));
}
