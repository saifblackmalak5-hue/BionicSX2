import os

filepath = "src/armsx2/app/src/main/cpp/cmake/SearchForStuff.cmake"
with open(filepath, 'a') as f:
    f.write("""
# iOS: Create namespaced ALIAS targets AFTER all add_subdirectory calls have executed
if(IOS)
  # ZLIB::ZLIB - use -lz from iOS SDK
  if(NOT TARGET ZLIB::ZLIB)
    add_library(ios_zlib INTERFACE)
    target_link_libraries(ios_zlib INTERFACE "-lz")
    add_library(ZLIB::ZLIB ALIAS ios_zlib)
    message(STATUS "iOS: Created ZLIB::ZLIB ALIAS to ios_zlib")
  endif()

  # Freetype::Freetype - built from 3rdparty/freetype
  if(NOT TARGET Freetype::Freetype AND TARGET freetype)
    add_library(ios_freetype INTERFACE)
    target_link_libraries(ios_freetype INTERFACE freetype)
    add_library(Freetype::Freetype ALIAS ios_freetype)
    message(STATUS "iOS: Created Freetype::Freetype ALIAS")
  endif()

  # Zstd::Zstd - built from 3rdparty/zstd
  if(NOT TARGET Zstd::Zstd AND TARGET zstd)
    add_library(ios_zstd INTERFACE)
    target_link_libraries(ios_zstd INTERFACE zstd)
    add_library(Zstd::Zstd ALIAS ios_zstd)
    message(STATUS "iOS: Created Zstd::Zstd ALIAS")
  endif()

  # CURL::libcurl - stub for iOS
  if(NOT TARGET CURL::libcurl)
    add_library(ios_curl INTERFACE)
    add_library(CURL::libcurl ALIAS ios_curl)
    message(STATUS "iOS: Created CURL::libcurl stub ALIAS")
  endif()

  # SDL3::SDL3 - built from 3rdparty/SDL3
  if(NOT TARGET SDL3::SDL3 AND TARGET SDL3)
    add_library(ios_sdl3 INTERFACE)
    target_link_libraries(ios_sdl3 INTERFACE SDL3)
    add_library(SDL3::SDL3 ALIAS ios_sdl3)
    message(STATUS "iOS: Created SDL3::SDL3 ALIAS")
  endif()
endif()
""")

print("Patch 11: Appended iOS ALIAS targets to SearchForStuff.cmake")
