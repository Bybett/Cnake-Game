# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(CnakeMan)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specify the C standard (C23 as you mentioned earlier)
set(CMAKE_C_STANDARD 23)

set(CMAKE_C_EXTENSIONS OFF)

# Add the executable (main source file)
add_executable(cnake-man src/main.c src/level_loader.c src/arr_length.c
src/hostile_handler.c src/move_entity.c src/wall_collide.c src/set_entity.c
src/char_to_int_entity.c src/title_screen.c src/ui_element.c src/asset_loader.c
src/snake_handler.c)

target_include_directories(cnake-man PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Link against the static library
target_link_libraries(cnake-man /usr/lib/libglfw.so raylib glfw m pthread dl rt)

find_package(glfw3 REQUIRED)

# Optionally, add custom compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -pedantic -Wextra -Wshadow -g -lraylib -lm -lpthread -ldl -lrt")

