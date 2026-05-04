import os

filepath = "src/armsx2/app/src/main/cpp/cmake/SearchForStuff.cmake"

with open(filepath, 'r') as f:
    lines = f.readlines()

# Prepend ZLIB injection to beginning of file
inject = """if(NOT IOS)
  find_package(ZLIB REQUIRED)
  if(ZLIB_FOUND AND NOT TARGET ZLIB::ZLIB)
    add_library(ZLIB::ZLIB UNKNOWN IMPORTED)
    set_target_properties(ZLIB::ZLIB PROPERTIES IMPORTED_LOCATION "${ZLIB_LIBRARIES}" INTERFACE_INCLUDE_DIRECTORIES "${ZLIB_INCLUDE_DIRS}")
  endif()
else()
  # iOS: ZLIB available as -lz in system
endif()
add_library(PCAP::PCAP INTERFACE IMPORTED)

"""

new_lines = inject.splitlines(keepends=True) + lines

with open(filepath, 'w') as f:
    f.writelines(new_lines)

print("Patch 4: Injected ZLIB handling at beginning of file")
