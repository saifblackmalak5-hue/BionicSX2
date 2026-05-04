import re

filepath = "src/armsx2/app/src/main/cpp/3rdparty/libwebp/CMakeLists.txt"

with open(filepath, 'r') as f:
    content = f.read()

# Comment out all install(TARGETS ...) lines
content = re.sub(r'^(\s*)install\(TARGETS', r'\1## install(TARGETS', content, flags=re.MULTILINE)

with open(filepath, 'w') as f:
    f.write(content)

print("Patched libwebp CMakeLists.txt to comment out install(TARGETS ...) lines")
