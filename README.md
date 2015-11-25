# CEGUI Windows and Mac OS X dependencies package for CEGUI 0.8.X (v0-8) and CEGUI 0.X (v0)
This package contains source code and a custom cmake build environment for the
majority of the optional dependency libraries that can be utilised by various
parts of the 'Crazy Eddie's GUI System' (CEGUI) project.

Note that none of the included source packages are in totally pristine and
unmodified form - for example, each package will contain a CEGUI-BUILD
directory that contains - at least - the custom CMakeLists.txt file.

Certain source files are also modified:

* DevIL (IL lib) files were patched to compile with the included libpng 1.4.7.
* Freetype was modified to be able to build as a DLL.
* jpeg library was modified to be able to build as a DLL.
* libtiff was modified to be able to build as a DLL.
* Some packages contain additional config header files which we copy into place
  for OS X, this is done to specify pre-configured settings and replaces an
  invocation of some ./configure script (or similar).

There may be other modifications not explicitly mentioned here, most are
identified in the original files by way of a comment containing "CEGUI"
somewhere, though it is possible - or even likely - that some modifications
are missing such identification, and this notification should suffice to
say that these libs are *not* the original code - to guarantee you're using
the original, umodified, code you should download your own copies of the
original source and perform your own build.

# Cross-compiling

CEGUI dependencies can be cross-compiled from Linux to Windows. In order to do that, you need to configure a cross-compile file and invoke that using CMake. An example of such file is the following:

```CMake
# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER i686-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER i686-w64-mingw32-g++)
SET(CMAKE_RC_COMPILER i686-w64-mingw32-windres)

# here is the target environment located
SET(CMAKE_FIND_ROOT_PATH /usr/i686-w64-mingw32 ${CMAKE_SOURCE_DIR}/install)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```

To invoke it you need to execute:
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=cross-compile.cmake ..
```

For more details on cross-compiling with CMake visit http://www.cmake.org/Wiki/CMake_Cross_Compiling .