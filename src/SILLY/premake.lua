--
-- SILLY premake configuration script
--
project.name = "SILLY"
project.bindir = "bin"
project.libdir = "lib"

package = newpackage()
package.name = "SILLY"
package.kind = "dll"
package.language = "c++"

package.files = {
    matchfiles("src/*.cpp"),
    matchfiles("src/loaders/*.cpp"),
    matchfiles("include/*.h"),
    matchfiles("include/*.icpp"),
    matchfiles("include/loaders/*.h"),
    matchfiles("include/loaders/*.icpp"),
}

package.includepaths = {
    "include",
    "include/loaders",
    "dependencies/include",
}

package.libpaths = {
    "dependencies/lib",
}

-- windows stuff
package.defines = {
    "WIN32","_WIN32", "__WIN32__",
    "_CRT_SECURE_NO_DEPRECATE",
    "SILLY_EXPORTS",
    "SILLY_HAVE_JPG",
    "SILLY_HAVE_PNG",
    --"SILLY_OPT_INLINE",
    --"SILLY_OPT_PROFILE",
}


--
-- Debug
--

    local debug = package.config["Debug"]
    debug.defines = { "DEBUG", "_DEBUG", "SILLY_OPT_DEBUG",}
    debug.target = "SILLY_d"
    debug.links = {
        "jpeg6b_d",
        "libpngd",
        "zlibd",
    }

--
-- Release
--

    local release = package.config["Release"]
    release.buildflags =
    {
        "no-frame-pointer",
        "no-symbols",
        "optimize-speed"
    }
    release.links = {
        "jpeg6b",
        "libpng",
        "zlib",
    }
