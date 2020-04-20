include_directories(
    ${PROJECT_SOURCE_DIR}/v1
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/external
    ${PROJECT_SOURCE_DIR}/external/bleu/v1
    )

add_library(
    act
    command/null_command.c
    command/sleep_command.c
    engine/active_object_engine_task.c
    engine/default_active_object_engine.c
    script/script_base.c
    script/script_runner.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/error/runtime_error.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/heap/gcc/heap.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/heap/heap_usage.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/list/list_node.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/list/list.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/string/str.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/string/string_builder.c
    )

add_executable(
    gtests
    main.cpp
    command/counting_command_stub.c
    command/counting_command_stub_test.cpp
    command/null_command_test.cpp
    command/sleep_command_test.cpp
    engine/default_active_object_engine_test.cpp
    script/script_runner_test.cpp
    script/script_spy.c
    script/script_spy_test.cpp
    util/time_unit_stub.c
    )

add_dependencies(gtests googletest)

target_link_libraries(
    gtests
    googletest
    act
    pthread
    )

include(CTest)

add_test(act_test ${PROJECT_BINARY_DIR}/gtests)
