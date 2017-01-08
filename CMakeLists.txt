cmake_minimum_required(VERSION 2.8.11)
project(LedStrip)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LedStrip_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LedStrip_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LedStrip_SOURCE_DIR}/bin)

add_subdirectory(linux)
add_subdirectory(src)
