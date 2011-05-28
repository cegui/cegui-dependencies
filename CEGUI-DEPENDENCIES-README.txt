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
* FreeGLUT was modified to remove the #pragma use that (may) auto-link to libs
  when using MSVC.  Having been bitten by this previously, I was taking no
  chances this time around :)
* Some packages contain additional config header files which we copy into place
  for OS X, this is done to specify pre-configured settings and replaces an
  invocation of some ./configure script (or similar).

There may be other modifications not explicitly mentioned here, most are
identified in the original files by way of a comment containing "CEGUI"
somewhere, though it is possible - or even likely - that some modifications
are missing such identification, and this notification should suffice to
say that these libs are /not/ the original code - to guarantee you're using
the original, umodified, code you should download your own copies of the
original source and perform your own build.

28th May 2011, The CEGUI Project.

