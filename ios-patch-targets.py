import os

filepath = "src/armsx2/app/src/main/cpp/cmake/SearchForStuff.cmake"
with open(filepath, 'r') as f:
    content = f.read()

# Step 1: Add elseif(IOS) block with add_subdirectory calls (mirroring ANDROID)
# Find the ANDROID block and add elseif(IOS) before the else() block
android_block_end = content.find('else()\n\tfind_package(CURL')
if android_block_end == -1:
    print("ERROR: Could not find ANDROID block end")
    exit(1)

ios_block = """elseif(IOS)
\t# iOS: Build dependencies from source (same as Android)
\tadd_subdirectory(3rdparty/zlib EXCLUDE_FROM_ALL)
\tadd_subdirectory(3rdparty/zstd EXCLUDE_FROM_ALL)
\tadd_subdirectory(3rdparty/lz4 EXCLUDE_FROM_ALL)
\tadd_subdirectory(3rdparty/libwebp EXCLUDE_FROM_ALL)
\tadd_subdirectory(3rdparty/SDL3 EXCLUDE_FROM_ALL)
\tadd_subdirectory(3rdparty/harfbuzz EXCLUDE_FROM_ALL)
\tadd_subdirectory(3rdparty/freetype EXCLUDE_FROM_ALL)
\tadd_subdirectory(3rdparty/oboe EXCLUDE_FROM_ALL)
\tadd_subdirectory(3rdparty/plutosvg1 EXCLUDE_FROM_ALL)
\t# iOS: ZLIB available as -lz in SDK (use system zlib instead of building)
\t# We'll create the target after add_subdirectory at the end of this file
\tmessage(STATUS "iOS: Added 3rdparty add_subdirectory calls")

"""

content = content[:android_block_end] + ios_block + content[android_block_end:]

# Step 2: Append ALIAS target creation at the END of the file (after all add_subdirectory calls)
ios_alias_block = """
# iOS: Create namespaced ALIAS targets AFTER all add_subdirectory calls have executed
if(IOS)
  # ZLIB::ZLIB - use -lz from iOS SDK (zlib not built from source for iOS)
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

  # CURL::libcurl - stub for iOS (not available)
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
"""

content += ios_alias_block

with open(filepath, 'w') as f:
    f.write(content)

print("Patch: Added elseif(IOS) block and ALIAS targets to SearchForStuff.cmake")
