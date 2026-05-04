# iOS CMake targets fix - pre-load script for CMake
# This defines all the targets that the project expects

# ZLIB::ZLIB - zlib is available as -lz in iOS SDK
# Create local target first, then ALIAS to namespaced target (CMake doesn't allow
# creating ZLIB::ZLIB directly as a non-IMPORTED target)
if(NOT TARGET ZLIB::ZLIB)
  add_library(ios_zlib INTERFACE)
  target_link_libraries(ios_zlib INTERFACE "-lz")
  add_library(ZLIB::ZLIB ALIAS ios_zlib)
  message(STATUS "iOS: Created ZLIB::ZLIB ALIAS to ios_zlib")
endif()

# CURL::libcurl - optional for iOS, create stub
# Same two-step approach: local target + ALIAS
if(NOT TARGET CURL::libcurl)
  add_library(ios_curl INTERFACE)
  add_library(CURL::libcurl ALIAS ios_curl)
  message(STATUS "iOS: Created CURL::libcurl ALIAS to ios_curl")
endif()
