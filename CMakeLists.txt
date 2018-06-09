cmake_minimum_required(VERSION 3.1)
project(BallMaze)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(assimp REQUIRED)
find_package(BULLET REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(include ${ASSIMP_INCLUDE_DIRS} ${BULLET_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(BallMaze ${SOURCES})

target_link_libraries(BallMaze ${ASSIMP_LIBRARIES} ${BULLET_LIBRARIES} ${FREETYPE_LIBRARIES} ${GLEW_LIBRARIES} glfw ${OPENGL_LIBRARIES})

file(INSTALL assets DESTINATION .)
