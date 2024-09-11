#===============================================================================
# @brief    cmake file 
#===============================================================================
project(lilos)

set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

set(PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/inc
                  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(PRIVATE_HEADER 
)

set(COMPONENT_CCFLAGS
)

set(MAKE_LIB true
)

build_cmd()

add_subdirectory(lilos_codeshield)
