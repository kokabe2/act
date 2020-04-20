# Act [![pipeline status](https://gitlab.com/kokabe/act/badges/master/pipeline.svg)](https://gitlab.com/kokabe/act/commits/master) [![coverage report](https://gitlab.com/kokabe/act/badges/master/coverage.svg)](https://gitlab.com/kokabe/act/commits/master) [![License](https://img.shields.io/badge/license-MIT-green.svg)](./LICENSE)

Act is a simple library for active object pattern and command pattern.

## Overview

- Written in C
- For embedded systems
- Every feature comes with tests
- Developer Friendly
- MIT license

## How To Use

This is just a example.

```c
#include "act/v1/default_active_object_engine.h"
#include "act/v1/sleep_command.h"
#include "user/test_command.h"

void main(void) {
  ActiveObjectEngine e = defaultActiveObjectEngine->New();
  Command wakeup = testCommand->New();
  Command c = sleepCommand->New(5000, e, wakeup);
  e->AddCommand(e, c);
  e->Run(e);  // 5 seconds later, TestCommand will be executed.
}
```
