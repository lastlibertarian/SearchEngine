set(INCLUDE ${CMAKE_SOURCE_DIR}/include)

add_executable(SearchEngine
        main.cpp
        ConverterJSON.cpp
        InvertedIndex.cpp
        SearchServer.cpp
)

target_link_libraries(SearchEngine PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(SearchEngine PUBLIC ${INCLUDE})
