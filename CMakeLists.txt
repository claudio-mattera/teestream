cmake_minimum_required(VERSION 3.7.2)
project(TeeStream VERSION 0.1 LANGUAGES CXX)

include(GNUInstallDirs)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
endif()


option(BUILD_EXAMPLES "Build examples" OFF)
if (${BUILD_EXAMPLES})
    add_subdirectory(examples)
endif()


add_subdirectory(lib)
