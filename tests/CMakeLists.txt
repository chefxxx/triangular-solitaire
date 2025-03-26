set(PROJECT_NAME tests)

set(SOURCES
        test_gene.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC
        GTest::gtest_main

)