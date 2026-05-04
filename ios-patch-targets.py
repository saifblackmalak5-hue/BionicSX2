import os

filepath = "src/armsx2/app/src/main/cpp/cmake/SearchForStuff.cmake"
with open(filepath, 'a') as f:
    f.write("""
# iOS: Define missing targets that the project expects
if(IOS)
  # ZLIB::ZLIB - zlib is available as -lz in iOS SDK
  if(NOT TARGET ZLIB::ZLIB)
    add_library(ZLIB::ZLIB INTERFACE)
    target_link_libraries(ZLIB::ZLIB INTERFACE "-lz")
    message(STATUS "iOS: Created ZLIB::ZLIB interface target")
  endif()

  # Freetype::Freetype - build from source (3rdparty/freetype)
  if(NOT TARGET Freetype::Freetype)
    if(TARGET freetype)
      add_library(Freetype::Freetype ALIAS freetype)
      message(STATUS "iOS: Created Freetype::Freetype ALIAS")
    else()
      message(STATUS "iOS: Freetype::Freetype will be created by add_subdirectory")
    endif()
  endif()

  # Zstd::Zstd - build from source (3rdparty/zstd)
  if(NOT TARGET Zstd::Zstd)
    if(TARGET zstd)
      add_library(Zstd::Zstd ALIAS zstd)
      message(STATUS "iOS: Created Zstd::Zstd ALIAS")
    else()
      message(STATUS "iOS: Zstd::Zstd will be created by add_subdirectory")
    endif()
  endif()

  # CURL::libcurl - optional for iOS, create stub
  if(NOT TARGET CURL::libcurl)
    add_library(CURL::libcurl INTERFACE)
    message(STATUS "iOS: Created CURL::libcurl stub interface target")
  endif()

  # SDL3::SDL3 - build from source (3rdparty/SDL3)
  if(NOT TARGET SDL3::SDL3)
    if(TARGET SDL3)
      add_library(SDL3::SDL3 ALIAS SDL3)
      message(STATUS "iOS: Created SDL3::SDL3 ALIAS")
    else()
      message(STATUS "iOS: SDL3::SDL3 will be created by add_subdirectory")
    endif()
  endif()
endif()
""")

print("Patch 6: Added iOS target definitions to SearchForStuff.cmake")
