cmake_minimum_required(VERSION 3.4)

project(BabelClient)

set(TARGET_BABEL_NAME BabelClient)

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

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)



# Find the Qt library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDES})
INCLUDE_DIRECTORIES(${Qt5Network_INCLUDES})
ADD_DEFINITIONS(${Qt5Network_DEFINITIONS} ${Qt5Widgets_DEFINITIONS})
SET(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")


#Google tests
add_subdirectory(test)

#Alfred
include(include/frameworks/alfred/CMakeLists.txt)


#Lib
if (NOT TARGET ${TARGET_BABEL_NAME})
    add_subdirectory(lib)
endif()
include_directories(lib/opus/header)
include_directories(lib/opus/header/opus)
include_directories(lib/portaudio/include)

#.LIB
#link_directories(${CMAKE_SOURCE_DIR}/lib/portaudio/lib)
link_directories(${CMAKE_SOURCE_DIR}/lib/opus/lib)

FILE (GLOB_RECURSE SRC sources/*.cpp)
FILE (GLOB_RECURSE SRC_INCLUDE include/*.hpp)

add_executable(${TARGET_BABEL_NAME} ${SRC} ${SRC_INCLUDE} main.cpp)
add_executable(Host ${SRC} ${SRC_INCLUDE} Caller1/Caller1.cpp)
add_executable(Sender ${SRC} ${SRC_INCLUDE} Caller2/Caller2.cpp)

add_subdirectory(include)

enable_testing()

# Use the Widgets module from Qt 5.
target_link_libraries(${TARGET_BABEL_NAME} Qt5::Widgets Qt5::Network ${CMAKE_REQUIRED_LIBRARIES} portaudio_static opus)
target_link_libraries(Host Qt5::Widgets Qt5::Network ${CMAKE_REQUIRED_LIBRARIES} portaudio_static opus)
target_link_libraries(Sender Qt5::Widgets Qt5::Network ${CMAKE_REQUIRED_LIBRARIES} portaudio_static opus)



#QT
if (WIN32)

    #Copy DLL (only for windows)
    #OPUS
    file(GLOB opus_DLL "${CMAKE_SOURCE_DIR}/lib/opus/lib/*.dll")
    file(COPY ${opus_DLL} DESTINATION .)

    #PORTAUDIO
    file(GLOB portaudio_DLL "${CMAKE_SOURCE_DIR}/lib/portaudio/lib/*.dll")
    file(COPY ${portaudio_DLL} DESTINATION .)

    file(GLOB qt_DLL "C:/Qt/5.9.1/msvc2017_64/bin/*.dll") ##ANCHOR 78554
    file(COPY ${qt_DLL} DESTINATION .)
endif()

#Copy SO (only linux)
