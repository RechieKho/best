add_library(
    Types

    Getable.hpp
    Setable.hpp
    Text.hpp
    Text.cpp
    Integer.hpp
    Integer.cpp
    )

target_include_directories(Types PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
