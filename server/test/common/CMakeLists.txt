include_directories(../lib/googletest/include)
include_directories(../lib/googlemock/include)

add_library(
        teamcity OBJECT
        teamcity_messages.cpp
        teamcity_messages.h
        teamcity_gtest.cpp
        teamcity_gtest.h
  )
