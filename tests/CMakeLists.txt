enable_testing()
set(SRC ${CMAKE_SOURCE_DIR}/src)

add_executable(SearchEngineTests
        ConverterJSONTests.cpp
        ${SRC}/ConverterJSON.cpp
        InvertedIndexFunctionalityTests.cpp
        ${SRC}/InvertedIndex.cpp
        SearchServerTests.cpp
        ${SRC}/SearchServer.cpp
)

target_link_libraries(SearchEngineTests PRIVATE gtest_main nlohmann_json::nlohmann_json)
target_include_directories(SearchEngineTests PRIVATE ${CMAKE_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(SearchEngineTests)
