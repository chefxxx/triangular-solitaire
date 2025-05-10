#
#   Load source files
#

file(GLOB GAME_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/../common/*.cpp"
)

#
#   Define static library
#

add_library(${GAME_LIB_NAME} STATIC ${GAME_SOURCES})

#
#   Link
#

target_link_libraries(${GAME_LIB_NAME} PUBLIC libExpected)

#
#   Add include directories
#

target_include_directories(${GAME_LIB_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/includes"
        "${CMAKE_CURRENT_SOURCE_DIR}/../common"
)