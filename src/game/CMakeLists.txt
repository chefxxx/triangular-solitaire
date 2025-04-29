#
#   Load source files
#

file(GLOB GAME_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

#
#   Remove game.cpp manually
#

list(REMOVE_ITEM GAME_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/game.cpp")

#
#   Define static library
#

add_library(${GAME_LIB_NAME} STATIC
        ${GAME_SOURCES}
)

#
#   Link
#

target_link_libraries(${GAME_LIB_NAME} PUBLIC libExpected)

#
#   Add include directories
#

target_include_directories(${GAME_LIB_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/includes"
)

#
#   Now build the executable separately
#

add_executable(Game "${CMAKE_CURRENT_SOURCE_DIR}/game.cpp")

#
#   Link executable with the game library and libExpected
#

target_link_libraries(Game PUBLIC ${GAME_LIB_NAME})

#
#   Add include directories to executable
#
target_include_directories(Game PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/includes"
)
