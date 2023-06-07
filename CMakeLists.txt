cmake_minimum_required(VERSION 3.23)
project(labwork_10_rurkk)

set(CMAKE_CXX_STANDARD 23)

add_executable(labwork_10_rurkk
        main.cpp
        WeatherForecast.h
        WeatherConstants.h
        )

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(labwork_10_rurkk PRIVATE nlohmann_json::nlohmann_json)

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba)
FetchContent_MakeAvailable(cpr)

target_link_libraries(labwork_10_rurkk PRIVATE cpr::cpr)

if(WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601) # or newer
endif()
target_link_libraries(labwork_10_rurkk PRIVATE kernel32)