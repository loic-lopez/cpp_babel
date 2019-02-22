cmake_minimum_required(VERSION 3.4)

project(BabelServer)

set(TARGET_BABEL_NAME BabelServer)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

include(cmake-utils/Header.cmake)
PRINT_HEADER()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)


if (CMAKE_COMPILER_IS_GNUCC)
    set(COMPILER_GCC 1)
    set(COMPILER_GCC_OR_CLANG 1)
endif ()
if (CMAKE_C_COMPILER_ID MATCHES "Clang")
    set(COMPILER_GCC_OR_CLANG 1)
endif ()


#BOOST
FIND_PACKAGE(Boost COMPONENTS regex system filesystem serialization thread REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})


#Google tests
enable_testing()
#include( CTest )
add_subdirectory(test)

#Alfred
#include(include/frameworks/alfred/CMakeLists.txt)


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#add_executable(${TARGET_BABEL_NAME} ${SRC} ${SRC_ALFRED})
add_executable(${TARGET_BABEL_NAME} main.cpp)

target_link_libraries(${TARGET_BABEL_NAME} Threads::Threads)

#Get Sources
add_subdirectory(sources)
#include(sources/CMakeLists.txt) # -> SRC

#Get Include Dir

add_subdirectory(include)

target_link_libraries(${TARGET_BABEL_NAME} ${Boost_LIBRARIES})


#if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#    message( FATAL_ERROR "YOU HAVE TO BUILD IN RELEASE MODE" )
#else ()
#    file(GLOB boost_DLL "C:/vcpkg/packages/boost_x64-windows/bin/*.dll")
#endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

#Copy boost DLL
file(COPY ${boost_DLL} DESTINATION .)
