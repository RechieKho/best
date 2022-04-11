add_library(
    Types

    BstObj.hpp
    BstObj.cpp
    String.hpp
    String.cpp
    Integer.hpp
    Integer.cpp
    Float.hpp
    Float.cpp
    List.hpp
    List.cpp
    Object.hpp
    Object.cpp
    )

target_include_directories(Types PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Types PRIVATE Cleaner)
target_link_libraries(Types PRIVATE Log)