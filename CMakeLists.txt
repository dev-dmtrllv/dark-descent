cmake_minimum_required(VERSION 3.8)

project(dark-descent)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*.hpp")

add_executable(dark-descent WIN32 ${SOURCES})
include_directories(${OPENGL_INCLUDE_DIRS} include)

target_precompile_headers(dark-descent PUBLIC include/pch.hpp)

if(MSVC)
	add_definitions(-DUNICODE -D_UNICODE)
	add_compile_options(/W4 /WX /EHa)
else()
	add_compile_options(-Wall -Wextra -Wpedantic -Werror -fexceptions)
endif()

if(CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET dark-descent PROPERTY CXX_STANDARD 23)
endif()
