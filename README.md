# Jarvis31


JARVIS project by Marshall31.

I don't think that it will be something good
But i'll just do it


## BUILD

**Requirements:**\
-CMake 3.20 or higher\
**Libraries required:**\
-Toml++\
-Boost.process\
-Standalone Asio\
-Vorbis (You need to download miniaudio_libvorbis.h from miniaudio github and put it in src/CORE/audio)

**Build:**
```
cmake -S . -B build/ -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
cmake --build build/
```

