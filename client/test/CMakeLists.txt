cmake_minimum_required(VERSION 3.2)
project(ServerGoogleTest)

####################################################################################################
#                                Settings Google Test Framework                                    #
#                                                                                                  #
####################################################################################################

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

add_subdirectory(common)
include_directories(common)

if (MSVC)
    foreach (flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if (${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif (${flag_var} MATCHES "/MD")
        if (${flag_var} MATCHES "/MDd")
            string(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
        endif (${flag_var} MATCHES "/MDd")
    endforeach (flag_var)
endif (MSVC)


#### PERSONAL INCLUDE
include_directories(
        ../include/Controller
        ../include/frameworks
        ../include/Model
        ../include/Network
        ../include/Plugin
        ../include/protocol
        ../include/View
        ../include/frameworks/alfred/Logger
        ../include/frameworks/alfred/Random
        ../include/frameworks/alfred/Utils
        ../include/frameworks/alfred/Timer
)

# Find the Qt library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Network REQUIRED)
INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDES})
INCLUDE_DIRECTORIES(${Qt5Network_INCLUDES})
ADD_DEFINITIONS(${Qt5Network_DEFINITIONS} ${Qt5Widgets_DEFINITIONS})
SET(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

add_subdirectory(lib)
include_directories(lib/googletest/include)
include_directories(lib/googlemock/include)
include_directories(../include/frameworks/Sound/)

#Lib
include_directories(../lib/opus/header)
include_directories(../lib/opus/header/opus)
include_directories(portaudio/include)
add_subdirectory(portaudio)

#.LIB
link_directories(portaudio)
link_directories(../lib/opus)


FILE (GLOB_RECURSE SRC
        ../sources/Controller/*.cpp
        ../sources/Framework/*.cpp
        ../sources/Network/*.cpp
        ../sources/View/*.cpp
        )
FILE(GLOB_RECURSE SRC_INCLUDE
        ../include/*.hpp
        ../include/frameworks/*.hpp
        ../include/frameworks/Sound/*.hpp
        ../include/Model/*.hpp
        ../include/Network/*.hpp
        ../include/Plugin/*.hpp
        ../include/protocol/*.hpp
        ../include/View/*.hpp
        )

set(TESTS_SOURCES MainGTest.cpp TestQtNetwork.cpp ../include/frameworks/Sound/ISoundCodec.hpp)

iF (WIN32)
    add_executable(clienttest ${TESTS_SOURCES} ${SRC} ${SRC_INCLUDE})
ELSE ()
    add_executable(clienttest ${SRC} ${SRC_INCLUDE} ${TESTS_SOURCES}  $<TARGET_OBJECTS:teamcity>)
ENDIF ()

FIND_PACKAGE(Boost COMPONENTS thread system filesystem REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

target_link_libraries(clienttest gtest Qt5::Widgets Qt5::Network ${CMAKE_REQUIRED_LIBRARIES} portaudio_static_test opus ${Boost_LIBRARIES})