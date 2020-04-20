include_directories(
    ${PROJECT_SOURCE_DIR}/v1
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/external
    ${PROJECT_SOURCE_DIR}/external/bleu/v1
    )

add_library(
    act
    command/null_command.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/heap/gcc/heap.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/heap/heap_usage.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/list/list_node.c
    ${PROJECT_SOURCE_DIR}/external/bleu/src/list/list.c
    )

add_executable(
    gtests
    main.cpp
    command/null_command_test.cpp
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
