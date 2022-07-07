set(TEST_SOURCES tests_tri.cpp ${PROJECT_SOURCE_DIR}/tri.h)

add_executable(
        tests_tri
        ${TEST_SOURCES}
)

target_include_directories(tests_tri PRIVATE ${PROJECT_SOURCE_DIR} )

target_link_libraries(
        tests_tri
        gtest_main
        gtest
        pthread
)

include(GoogleTest)
gtest_discover_tests(tests_tri)