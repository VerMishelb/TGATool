# Building
This is supposed to work with Visual Studio for Windows Vista and higher. MinGW might works but was not tested. Linux might work. Note that the CMAKE_BUILD_TYPE=Release definition is not necessary for Visual Studio generator, but it might be necessary if you use something different, therefore it's left intact.
1. Open command prompt in the project directory.
2. Call one after another:
`cmake -B build -S . -A Win32 -D CMAKE_BUILD_TYPE=Release`
`cmake --build build --config Release -j`
3. The resulting binary will be under `./build/Release` directory.

Copyright © 2020-2025 VerMishelb <vermishelb535@gmail.com>. All rights reserved.
Licensed under the Apache License, Version 2.0. Please refer to the "LICENSE" file or an online copy.