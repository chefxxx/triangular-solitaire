SET(CMAKE_BUILD_TYPE Debug)

#
#   Add subdirs
#

add_subdirectory(genetic)
add_subdirectory(game)

#
#   Define executables
#

add_executable(${EXEC_NAME}_genetic
        genetic_main.cpp
        common/heuristic.h
        common/distance_to_center.cpp
        common/distance_to_center.h
        common/number_of_free_positions.h
        common/isolated_pegs.h
        common/isolated_pegs.cpp
        common/number_of_new_moves.h
)

#
#   Link lib to executable
#

target_link_libraries(${EXEC_NAME}_genetic PRIVATE ${GENETIC_LIB_NAME} ${GAME_LIB_NAME})