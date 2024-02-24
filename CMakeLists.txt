# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (GravitySim)

if (CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(
        -std=c++17
    )
endif()

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message("Starting compilation for Project ${CMAKE_PROJECT_NAME}")

# Create a sources variable with a link to all cpp files to compile
file(GLOB_RECURSE SOURCES
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/inc/*.hpp
)

# Add an executable with the above sources
add_executable(GravitySim ${SOURCES} )

target_link_libraries(GravitySim ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} -lSDL2_image)

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(GravitySim
        PRIVATE
        ${PROJECT_SOURCE_DIR}/inc
)
