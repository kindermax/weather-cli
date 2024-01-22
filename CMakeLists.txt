cmake_minimum_required(VERSION 3.11)
project(weather_cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
    cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                          GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8)
FetchContent_MakeAvailable(cpr)

add_executable(weather_cli src/weather.cpp)
target_link_libraries(weather_cli PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(weather_cli PRIVATE cpr::cpr)