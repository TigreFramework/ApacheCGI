cmake_minimum_required(VERSION 3.4)
project(TigreFramework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SYSTEM_FILES
        ApacheEnv.cpp
        ApacheServiceProvider.cpp
        ApacheResponseStream.cpp
        ApacheHttpCore.cpp
        Event/RequestEvent.cpp
)

set(SOURCE_FILES ${SYSTEM_FILES})

add_library(tgApacheCgi ${SYSTEM_FILES})
target_link_libraries(tgApacheCgi String tgcore)