cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Release)

project(demo)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)

include(FetchContent)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb
    GIT_TAG        master
)
FetchContent_MakeAvailable(stb)

FetchContent_Declare(
    GLAD
    URL https://gitfront.io/r/Moztanku/8s4L1GHF3Tsc/Resources/raw/glad-cmake.zip
)
FetchContent_MakeAvailable(GLAD)

file(GLOB_RECURSE SOURCES "src/**.cpp")

add_executable(demo)

target_sources(demo PRIVATE ${SOURCES})
target_include_directories(demo PRIVATE "inc")

target_link_libraries(demo PRIVATE
    OpenGL::GL
    GLAD
    glfw
    glm
    assimp
)
