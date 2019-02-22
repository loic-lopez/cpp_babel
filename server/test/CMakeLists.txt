cmake_minimum_required(VERSION 3.2)
project(ServerGoogleTest)

####################################################################################################
#                                Settings Google Test Framework                                    #
#                                                                                                  #
####################################################################################################

IF (UNIX)
    add_subdirectory(common)
    include_directories(common)
ENDIF ()

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



set(TESTS_SOURCES
        MainGTest.cpp
        TestAddTable.cpp
        TestCreateDatabase.cpp
        TestTableFields.cpp)

add_subdirectory(lib)
include_directories(lib/googletest/include)
include_directories(lib/googlemock/include)
include_directories(../include/Database)
include_directories(../include/Network)
include_directories(../include/Protocol)
include_directories(../include/Server)
include_directories(../include/Plugin)
include_directories(../include/Framework/Random)
include_directories(../include/Framework/Logger)
include_directories(../include/Framework/Utils)
include_directories(../include/Framework/Timer)

FIND_PACKAGE(Boost COMPONENTS regex system filesystem serialization thread REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

FILE (GLOB_RECURSE SRC ../sources/*.cpp)
FILE (GLOB_RECURSE SRC_INCLUDE ../include/*.hpp)

IF (WIN32)
    add_executable(servertest ${TESTS_SOURCES} ${SRC} ${SRC_INCLUDE})
ELSE ()
    add_executable(servertest ${TESTS_SOURCES} ${SRC} ${SRC_INCLUDE} $<TARGET_OBJECTS:teamcity>)
ENDIF ()


target_link_libraries(servertest gtest ${Boost_LIBRARIES})
add_test(SERVER_TEST servertest)

#if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#    message( FATAL_ERROR "YOU HAVE TO BUILD IN RELEASE MODE" )
#else ()
#    file(GLOB boost_DLL "C:/vcpkg/packages/boost_x64-windows/bin/*.dll")
#endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

#Copy boost DLL
file(COPY ${boost_DLL} DESTINATION .)