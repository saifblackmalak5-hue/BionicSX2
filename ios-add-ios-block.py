import os
import re

filepath = "src/armsx2/app/src/main/cpp/cmake/SearchForStuff.cmake"

# Debug: print current directory and file existence
print(f"Current dir: {os.getcwd()}")
print(f"File exists: {os.path.exists(filepath)}")

with open(filepath, 'r') as f:
    lines = f.readlines()

# Debug: print first 50 lines to see file structure
print(f"Total lines: {len(lines)}")
print("Searching for elseif(ANDROID)...")
android_idx = -1
for i, line in enumerate(lines):
    if 'elseif(ANDROID)' in line or 'elseif(ANDROID)' in line:
        android_idx = i
        print(f"Found elseif(ANDROID) at line {i}: {line.strip()}")
        break

if android_idx == -1:
    print("ERROR: elseif(ANDROID) not found!")
    print("Searching for 'ANDROID' anywhere...")
    for i, line in enumerate(lines):
        if 'ANDROID' in line:
            print(f"  Line {i}: {line.strip()}")
            break
    # Print some context around expected location
    print("Context around line 40-60:")
    for i in range(40, min(60, len(lines))):
        print(f"  Line {i}: {lines[i].rstrip()}")
    exit(1)

# Find next else() after elseif(ANDROID)
print("Searching for else() after elseif(ANDROID)...")
insert_idx = -1
for i in range(android_idx + 1, len(lines)):
    stripped = lines[i].strip()
    if stripped == 'else()' or stripped.startswith('else()'):
        insert_idx = i
        print(f"Found else() at line {i}: {lines[i].strip()}")
        break

if insert_idx == -1:
    print("ERROR: else() after elseif(ANDROID) not found!")
    print("Searching for any 'else()' in file...")
    for i, line in enumerate(lines):
        if 'else()' in line:
            print(f"  Line {i}: {line.strip()}")
    exit(1)

# Create elseif(IOS) block with add_subdirectory AND ALIAS targets
ios_block = '''elseif(IOS)
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
\tmessage(STATUS "iOS: Added 3rdparty add_subdirectory calls")
\t# iOS: Create ALIAS targets IMMEDIATELY after add_subdirectory
\t# ZLIB::ZLIB - use -lz from iOS SDK
\tif(NOT TARGET ZLIB::ZLIB)
\t\tadd_library(ios_zlib INTERFACE)
\t\ttarget_link_libraries(ios_zlib INTERFACE "-lz")
\t\tadd_library(ZLIB::ZLIB ALIAS ios_zlib)
\t\tmessage(STATUS "iOS: Created ZLIB::ZLIB ALIAS to ios_zlib")
\tendif()
\t# CURL::libcurl - stub for iOS
\tif(NOT TARGET CURL::libcurl)
\t\tadd_library(ios_curl INTERFACE)
\t\tadd_library(CURL::libcurl ALIAS ios_curl)
\t\tmessage(STATUS "iOS: Created CURL::libcurl stub ALIAS")
\tendif()
\t# Freetype::Freetype - built from 3rdparty/freetype
\tif(TARGET freetype AND NOT TARGET Freetype::Freetype)
\t\tadd_library(ios_freetype INTERFACE)
\t\ttarget_link_libraries(ios_freetype INTERFACE freetype)
\t\tadd_library(Freetype::Freetype ALIAS ios_freetype)
\t\tmessage(STATUS "iOS: Created Freetype::Freetype ALIAS")
\tendif()
\t# Zstd::Zstd - built from 3rdparty/zstd
\tif(TARGET zstd AND NOT TARGET Zstd::Zstd)
\t\tadd_library(ios_zstd INTERFACE)
\t\ttarget_link_libraries(ios_zstd INTERFACE zstd)
\t\tadd_library(Zstd::Zstd ALIAS ios_zstd)
\t\tmessage(STATUS "iOS: Created Zstd::Zstd ALIAS")
\tendif()
\t# SDL3::SDL3 - built from 3rdparty/SDL3
\tif(TARGET SDL3 AND NOT TARGET SDL3::SDL3)
\t\tadd_library(ios_sdl3 INTERFACE)
\t\ttarget_link_libraries(ios_sdl3 INTERFACE SDL3)
\t\tadd_library(SDL3::SDL3 ALIAS ios_sdl3)
\t\tmessage(STATUS "iOS: Created SDL3::SDL3 ALIAS")
\tendif()
\t
'''

# Insert the iOS block before else()
lines.insert(insert_idx, ios_block)

# Write back
with open(filepath, 'w') as f:
    f.writelines(lines)

print("Patch: Added elseif(IOS) block with inline ALIAS targets to SearchForStuff.cmake")
