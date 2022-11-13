cmake_minimum_required(VERSION 3.19)

project(cai_sim VERSION 0.1.0
        DESCRIPTION "Simulateur de CAI"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/")

# Include SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Include SDL2_image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# Include SDL2_ttf
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2TTF_INCLUDE_DIRS})

# Include OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Set the source file directory
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/Sources)

# Add all .hpp files in the source directory
# Normally, we wouldn't do this, but it's easier for this project since
# not everyone is using an IDE that supports CMake
file(GLOB_RECURSE HEADERS ${SOURCE_DIR}/*.hpp)

# Add the executable
add_executable(game ${SOURCE_DIR}/main.cpp ${HEADERS})

target_link_libraries(game PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARY} ${OPENGL_LIBRARIES})
