# iOS CMake targets fix - pre-load script for CMake
# This defines all the targets that the project expects

# ZLIB::ZLIB - available as -lz in iOS SDK
if(NOT TARGET ZLIB::ZLIB)
  add_library(ZLIB::ZLIB INTERFACE)
  target_link_libraries(ZLIB::ZLIB INTERFACE "-lz")
  message(STATUS "iOS: Created ZLIB::ZLIB interface target")
endif()

# For other targets, we try to build from source or create stubs
# These will be handled by add_subdirectory calls in SearchForStuff.cmake

# CURL::libcurl - optional for iOS, create stub
if(NOT TARGET CURL::libcurl)
  add_library(CURL::libcurl INTERFACE)
  message(STATUS "iOS: Created CURL::libcurl stub interface target")
endif()
