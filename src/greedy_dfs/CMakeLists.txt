#
#   Define executable
#

add_executable(greedy_dfs_main greedy_dfs_main.cpp)

#
#   Link with libs
#

target_link_libraries(greedy_dfs_main PUBLIC ${GAME_LIB_NAME})

#
#   Add includes
#

target_include_directories(greedy_dfs_main PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/includes"
        "${CMAKE_CURRENT_SOURCE_DIR}/../common")