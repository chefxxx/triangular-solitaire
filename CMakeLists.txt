#
#   Project setup
#

set(EXEC_NAME "TriangularSolitaire")
set(LIB_NAME ${EXEC_NAME}_lib)
set(TEST_NAME "UnitTestsTarget")

cmake_minimum_required(VERSION 3.26)
project(${EXEC_NAME} CXX)

set(PROJECT_NAME ${EXEC_NAME})
set(PROJECT_VERSION "1.0")

set(CMAKE_CXX_STANDARD_REQUIRED 20)

#
#   Set variables for lib linking
#

set(GENETIC_LIB_NAME ${LIB_NAME}_genetic)

#
#   Load project
#

add_subdirectory(src)
add_subdirectory(dependencies)

#
#   Add test target
#

enable_testing()
add_subdirectory(tests)



