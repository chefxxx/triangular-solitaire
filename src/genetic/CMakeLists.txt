#
#   Load source files
#

file(GLOB LIB_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# Ensure mains removed from lib sources
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/gen_alg_main.cpp")

#
#   Define static lib
#

add_library(${GENETIC_LIB_NAME} STATIC
        ${LIB_SOURCES}
)

#
#   Add includes
#

target_include_directories(${GENETIC_LIB_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/includes"
)

#
#   Link "game" lib
#

target_link_libraries(${GENETIC_LIB_NAME} PRIVATE ${GAME_LIB_NAME})

#
#   Define executable
#

add_executable(gen_alg_main gen_alg_main.cpp)

#
#   Link with libs
#

target_link_libraries(gen_alg_main PRIVATE ${GENETIC_LIB_NAME} ${GAME_LIB_NAME})