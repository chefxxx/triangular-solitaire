#
#   Load source files
#

file(GLOB LIB_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

#
#   Remove main from lib sources
#

list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/greedy_dfs_main.cpp")

#
#   Define static lib
#

add_library(${GREEDY_DFS_LIB_NAME} STATIC ${LIB_SOURCES}
        test.cpp)

#
#   Add includes
#

target_include_directories(${GREEDY_DFS_LIB_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes")

#
# Link game lib
#

target_link_libraries(${GREEDY_DFS_LIB_NAME} PUBLIC ${GAME_LIB_NAME} spdlog::spdlog)

#
#   Define executable
#

add_executable(greedy_dfs_main greedy_dfs_main.cpp)

#
#   Link with libs
#

target_link_libraries(greedy_dfs_main PRIVATE ${GREEDY_DFS_LIB_NAME} ${GAME_LIB_NAME})