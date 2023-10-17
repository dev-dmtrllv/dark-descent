cmake_minimum_required(VERSION 3.8)

project(dark-descent)

file(GLOB dark-descent-srcs CONFIGURE_DEPENDS "include/*.h" "src/*.cpp" "include/ion/*.h" "src/ion/*.cpp" "include/game/*.h" "src/game/*.cpp")

add_executable(dark-descent WIN32 ${dark-descent-srcs})
include_directories(dark-descent include)

target_precompile_headers(dark-descent PUBLIC include/pch.hpp)

if(MSVC)
	add_definitions(-DUNICODE -D_UNICODE)
	add_compile_options(/W4 /WX)
else()
	add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

if(CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET dark-descent PROPERTY CXX_STANDARD 23)
endif()
