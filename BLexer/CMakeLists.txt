add_library(
    BLexer

    BToken.hpp
    BLexer.hpp
    BLexer.cpp
)

target_include_directories(BLexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})