#
#   Fetch "expected" from github...
#
message(STATUS "Adding expected...")
include(FetchContent)

FetchContent_Declare(
        expected
        GIT_REPOSITORY https://github.com/TartanLlama/expected.git
        GIT_TAG v1.1.0
)
FetchContent_MakeAvailable(expected)

# ----------------------------
# Interface Library
# ----------------------------
add_library(libExpected INTERFACE)
target_include_directories(libExpected INTERFACE ${expected_SOURCE_DIR}/include)