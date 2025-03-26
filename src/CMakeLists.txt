#
#   Add subdirs
#

add_subdirectory(genetic)

#
#   Define executables
#

add_executable(${EXEC_NAME}_genetic
        genetic_main.cpp
)

#
#   Link lib to executable
#

target_link_libraries(${EXEC_NAME}_genetic PRIVATE ${GENETIC_LIB_NAME})