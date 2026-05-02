BASE="src/armsx2/app/src/main/cpp/3rdparty/discord-rpc/src"
for f in discord_rpc.cpp serialization.cpp rpc_connection.cpp connection_unix.cpp dllmain.cpp discord_register_linux.cpp discord_register_osx.m; do
    echo "// BionicSX2 iOS stub" > $BASE/$f
done
echo "All Discord stubs done"
