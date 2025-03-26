#
#   Load source files
#

file(GLOB LIB_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

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