message(STATUS "Loading tests target...")

#
#   Load sources
#

file(GLOB TEST_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

#
#   Define executable
#

add_executable(${TEST_NAME}
        ${TEST_SOURCES}
)

#
#   Link with libs and gtest
#

target_link_libraries(
        ${TEST_NAME} PRIVATE ${GENETIC_LIB_NAME} GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TEST_NAME})