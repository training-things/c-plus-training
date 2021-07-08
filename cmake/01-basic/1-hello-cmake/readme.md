

c-plus git:(master) ✗ cd cmake/basic/1-hello-cmake 
➜  1-hello-cmake git:(master) ✗ 
➜  1-hello-cmake git:(master) ✗ 
➜  1-hello-cmake git:(master) ✗ ll
total 16
drwxr-xr-x  5 yixiao  staff  160  7  5 08:43 ./
drwxr-xr-x  4 yixiao  staff  128  7  5 08:37 ../
-rw-r--r--  1 yixiao  staff  242  7  5 08:37 CmakeLists.txt
-rw-r--r--  1 yixiao  staff  108  7  5 08:38 main.cc
-rw-r--r--  1 yixiao  staff    0  7  5 08:43 readme.md
➜  1-hello-cmake git:(master) ✗ 
➜  1-hello-cmake git:(master) ✗ 
➜  1-hello-cmake git:(master) ✗ pwd
/Users/develop/bootcamp2021/c-plus/cmake/basic/1-hello-cmake
➜  1-hello-cmake git:(master) ✗ 
➜  1-hello-cmake git:(master) ✗ mkdir build && cd build     
➜  build git:(master) ✗ 
➜  build git:(master) ✗ pwd
/Users/develop/bootcamp2021/c-plus/cmake/basic/1-hello-cmake/build
➜  build git:(master) ✗ 
➜  build git:(master) ✗ cmake ..                    
-- The C compiler identification is AppleClang 12.0.5.12050022
-- The CXX compiler identification is AppleClang 12.0.5.12050022
-- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc
-- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc - works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++
-- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ - works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /Users/develop/bootcamp2021/c-plus/cmake/basic/1-hello-cmake/build
➜  build git:(master) ✗ 
➜  build git:(master) ✗ 
➜  build git:(master) ✗ ll
total 56
drwxr-xr-x   6 yixiao  staff    192  7  5 08:46 ./
drwxr-xr-x   6 yixiao  staff    192  7  5 08:44 ../
-rw-r--r--   1 yixiao  staff  14342  7  5 08:46 CMakeCache.txt
drwxr-xr-x  13 yixiao  staff    416  7  5 08:46 CMakeFiles/
-rw-r--r--   1 yixiao  staff   5450  7  5 08:46 Makefile
-rw-r--r--   1 yixiao  staff   1433  7  5 08:46 cmake_install.cmake
➜  build git:(master) ✗ 
➜  build git:(master) ✗ tree
.
├── CMakeCache.txt
├── CMakeFiles
│   ├── 3.17.3
│   │   ├── CMakeCCompiler.cmake
│   │   ├── CMakeCXXCompiler.cmake
│   │   ├── CMakeDetermineCompilerABI_C.bin
│   │   ├── CMakeDetermineCompilerABI_CXX.bin
│   │   ├── CMakeSystem.cmake
│   │   ├── CompilerIdC
│   │   │   ├── CMakeCCompilerId.c
│   │   │   ├── CMakeCCompilerId.o
│   │   │   └── tmp
│   │   └── CompilerIdCXX
│   │       ├── CMakeCXXCompilerId.cpp
│   │       ├── CMakeCXXCompilerId.o
│   │       └── tmp
│   ├── CMakeDirectoryInformation.cmake
│   ├── CMakeError.log
│   ├── CMakeOutput.log
│   ├── CMakeTmp
│   ├── Makefile.cmake
│   ├── Makefile2
│   ├── TargetDirectories.txt
│   ├── cmake.check_cache
│   ├── hello_cmake.dir
│   │   ├── DependInfo.cmake
│   │   ├── build.make
│   │   ├── cmake_clean.cmake
│   │   ├── depend.make
│   │   ├── flags.make
│   │   ├── link.txt
│   │   └── progress.make
│   └── progress.marks
├── Makefile
└── cmake_install.cmake

8 directories, 27 files
➜  build git:(master) ✗ make                   
Scanning dependencies of target hello_cmake
[ 50%] Building CXX object CMakeFiles/hello_cmake.dir/main.cc.o
[100%] Linking CXX executable hello_cmake
[100%] Built target hello_cmake
➜  build git:(master) ✗ 
➜  build git:(master) ✗ ll
total 168
drwxr-xr-x   7 yixiao  staff    224  7  5 08:46 ./
drwxr-xr-x   6 yixiao  staff    192  7  5 08:44 ../
-rw-r--r--   1 yixiao  staff  14342  7  5 08:46 CMakeCache.txt
drwxr-xr-x  13 yixiao  staff    416  7  5 08:46 CMakeFiles/
-rw-r--r--   1 yixiao  staff   5450  7  5 08:46 Makefile
-rw-r--r--   1 yixiao  staff   1433  7  5 08:46 cmake_install.cmake
-rwxr-xr-x   1 yixiao  staff  56120  7  5 08:46 hello_cmake*
➜  build git:(master) ✗ 
➜  build git:(master) ✗ 
➜  build git:(master) ✗ ./hello_cmake 
hello world!
➜  build git:(master) ✗

