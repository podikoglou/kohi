cmake_minimum_required(VERSION 3.20)
project(kohi)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/*.h")

# Add executable target
add_executable(kohi ${SOURCES} ${HEADERS})

# Add include directories
target_include_directories(kohi PRIVATE src)

# add libzip
find_package(PkgConfig REQUIRED)
pkg_search_module(LIBZIP REQUIRED libzip)
target_include_directories(kohi PRIVATE ${LIBZIP_INCLUDE_DIRS})
target_link_libraries(kohi PRIVATE ${LIBZIP_LIBRARIES})
