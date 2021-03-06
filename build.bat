@echo off

set PROJECT_NAME=act
for /F "tokens=*" %%A in ('"git describe HEAD --abbrev=0"') do set PROJECT_VER=%%A

cd %~dp0

set COMPILER=ccrx
set OUTPUT_DIR=bin\%COMPILER%@%PROJECT_VER%
mkdir %OUTPUT_DIR% > NUL 2>&1
%COMPILER% -output=obj -lang=c99 -nostuff -isa=rxv3 -debug -signed_char ^
           -include=v1/,src/,external/ ^
           src/command/null_command.c ^
           src/command/simple_command.c ^
           src/command/sleep_command.c ^
           src/engine/active_object_engine_task.c ^
           src/engine/default_active_object_engine.c ^
           src/script/script_base.c ^
           src/script/script_runner.c ^
           src/script/script_strategy.c ^
           src/script/simple_script.c
if %errorlevel% neq 0 exit /b

rlink -form=lib -output=%OUTPUT_DIR%/%PROJECT_NAME%.lib *.obj
del *.obj
