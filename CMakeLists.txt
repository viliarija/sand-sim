cmake_minimum_required(VERSION 3.5)

project(sandsim)

# Set the build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Add the source files to the executable
add_executable(main main.cpp screen.cpp)

# Include SDL2 headers
target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})

# Link SDL2 library
target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})

# Set compiler flags for the debug build
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(main PRIVATE -Wall -Wextra -g)
endif()
