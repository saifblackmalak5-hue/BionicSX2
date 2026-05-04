import os

filepath = "src/armsx2/app/src/main/cpp/cmake/SearchForStuff.cmake"
with open(filepath, 'a') as f:
    f.write("""
# iOS: Define missing targets that the project expects
# Uses two-step approach: local target + ALIAS (CMake doesn't allow
# creating namespaced targets directly as non-IMPORTED)
if(IOS)
  # Freetype::Freetype - build from source (3rdparty/freetype)
  if(NOT TARGET Freetype::Freetype)
    if(TARGET freetype)
      # Two-step: create local target, then ALIAS with namespace
      add_library(ios_freetype INTERFACE)
      target_link_libraries(ios_freetype INTERFACE freetype)
      add_library(Freetype::Freetype ALIAS ios_freetype)
      message(STATUS "iOS: Created Freetype::Freetype ALIAS")
    else()
      message(STATUS "iOS: Freetype::Freetype will be created by add_subdirectory")
    endif()
  endif()

  # Zstd::Zstd - build from source (3rdparty/zstd)
  if(NOT TARGET Zstd::Zstd)
    if(TARGET zstd)
      add_library(ios_zstd INTERFACE)
      target_link_libraries(ios_zstd INTERFACE zstd)
      add_library(Zstd::Zstd ALIAS ios_zstd)
      message(STATUS "iOS: Created Zstd::Zstd ALIAS")
    else()
      message(STATUS "iOS: Zstd::Zstd will be created by add_subdirectory")
    endif()
  endif()

  # SDL3::SDL3 - build from source (3rdparty/SDL3)
  if(NOT TARGET SDL3::SDL3)
    if(TARGET SDL3)
      add_library(ios_sdl3 INTERFACE)
      target_link_libraries(ios_sdl3 INTERFACE SDL3)
      add_library(SDL3::SDL3 ALIAS ios_sdl3)
      message(STATUS "iOS: Created SDL3::SDL3 ALIAS")
    else()
      message(STATUS "iOS: SDL3::SDL3 will be created by add_subdirectory")
    endif()
  endif()
endif()
""")

print("Patch 6: Added iOS target definitions to SearchForStuff.cmake")
