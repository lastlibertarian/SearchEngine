cmake_minimum_required(VERSION 3.26)

project(SearchEngine)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
# Подключение nlohmann json
FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Подключение Google Test
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(src)
add_subdirectory(tests)
