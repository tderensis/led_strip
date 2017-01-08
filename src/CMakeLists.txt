add_library(led_strip led_strip.c led_strip_no_backend.c)

# Make sure the compiler can find include files for our library
# when other libraries or executables link to it.
target_include_directories(led_strip PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
