# -------------------------------
# Fetch GTEST from github...
# -------------------------------

include(FetchContent)

FetchContent_Declare(
        libGTEST
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG main
        GIT_PROGRESS   TRUE
)

FetchContent_MakeAvailable(libGTEST)