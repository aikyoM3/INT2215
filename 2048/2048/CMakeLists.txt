cmake_minimum_required(VERSION 3.10)
project(2048)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES FALSE)
set(SFML_BUILD_SHARED_LIBS TRUE)

# Add SFML include directory
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/SFML/include")

# Add executable
add_executable(2048 2048.cpp)

# Link SFML libraries
target_link_libraries(2048 PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/sfml-graphics.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/sfml-window.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/sfml-system.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/freetype.lib"
    opengl32
    winmm
    gdi32
)

# Copy SFML DLLs to output directory on Windows
if(WIN32)
    add_custom_command(TARGET 2048 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/SFML/bin"
        $<TARGET_FILE_DIR:2048>)
endif() 