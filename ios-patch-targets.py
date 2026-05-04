import os

filepath = "src/armsx2/app/src/main/cpp/cmake/SearchForStuff.cmake"

with open(filepath, 'r') as f:
    lines = f.readlines()

# Step 1: Remove any existing elseif(IOS) block
# (in case we're running this multiple times)
new_lines = []
skip_until_endif = False
for i, line in enumerate(lines):
    if 'elseif(IOS)' in line:
        skip_until_endif = True
        continue
    if skip_until_endif:
        if 'endif()' in line:
            skip_until_endif = False
        continue
    new_lines.append(line)

lines = new_lines

# Step 2: Find the else() that comes after elseif(ANDROID)
insert_idx = -1
android_idx = -1

for i, line in enumerate(lines):
    if 'elseif(ANDROID)' in line:
        android_idx = i
        break

if android_idx == -1:
    print("ERROR: Could not find elseif(ANDROID) block")
    exit(1)

# Find the next else() after elseif(ANDROID)
for i in range(android_idx + 1, len(lines)):
    if lines[i].strip() == 'else()':
        insert_idx = i
        break

if insert_idx == -1:
    print("ERROR: Could not find else() after elseif(ANDROID)")
    exit(1)

# Step 3: Insert elseif(IOS) block before else()
ios_block = [
    'elseif(IOS)\n',
    '\t# iOS: Build dependencies from source (same as Android)\n',
    '\tadd_subdirectory(3rdparty/zlib EXCLUDE_FROM_ALL)\n',
    '\tadd_subdirectory(3rdparty/zstd EXCLUDE_FROM_ALL)\n',
    '\tadd_subdirectory(3rdparty/lz4 EXCLUDE_FROM_ALL)\n',
    '\tadd_subdirectory(3rdparty/libwebp EXCLUDE_FROM_ALL)\n',
    '\tadd_subdirectory(3rdparty/SDL3 EXCLUDE_FROM_ALL)\n',
    '\tadd_subdirectory(3rdparty/harfbuzz EXCLUDE_FROM_ALL)\n',
    '\tadd_subdirectory(3rdparty/freetype EXCLUDE_FROM_ALL)\n',
    '\tadd_subdirectory(3rdparty/oboe EXCLUDE_FROM_ALL)\n',
    '\tadd_subdirectory(3rdparty/plutosvg1 EXCLUDE_FROM_ALL)\n',
    '\tmessage(STATUS "iOS: Added 3rdparty add_subdirectory calls")\n',
    '\n',
]

lines = lines[:insert_idx] + ios_block + lines[insert_idx:]

# Step 4: Append ALIAS targets at the END of file
ios_alias_block = '''
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
'''

lines.append(ios_alias_block)

with open(filepath, 'w') as f:
    f.writelines(lines)

print("Patch: Added elseif(IOS) block and ALIAS targets to SearchForStuff.cmake")
# iOS targets fix - trigger rebuild
