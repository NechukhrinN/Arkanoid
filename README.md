# Arkanoid
Arkanoid game based on SFML C++

## Building with CMake

Requires CMake 3.16+ and a C++17 compiler. If SFML 2.x is not installed,
CMake downloads and builds it automatically.

```sh
cmake -S . -B build
cmake --build build --config Release
```

The executable and a copy of the `res` folder are placed in `build/Release`
(with Visual Studio) or `build/` (with single-config generators). Run
`Arkanoid.exe` from that folder.

To use an installed SFML instead, install it first (for example with vcpkg)
or pass `-DARKANOID_FETCH_SFML=OFF`.

Toturial:
