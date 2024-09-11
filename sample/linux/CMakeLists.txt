cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 11)

project(lilos_sample)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output)

add_definitions(-DLILOS_NO_INIT_CALL -DBUILD_DEBUG)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    )
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/../../src/*.c
              )

if(USE_MAKE MATCHES "cpp")
    set(SRC ${SRC} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
else()
    file(GLOB SAMPLESRC ${CMAKE_CURRENT_SOURCE_DIR}/../test/*.c
    )
    set(SRC ${SRC} ${SAMPLESRC} ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../test
                    )
endif()

add_executable(lilos_sample ${SRC})
target_link_options(lilos_sample PRIVATE -Wl,-Map=output.map)
