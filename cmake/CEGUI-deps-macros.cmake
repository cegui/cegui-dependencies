set( _TMP_C_PLUS_PLUS_SRC_FILE_NAME "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/src.cxx" )

macro( cegui_check_mingw )
    set( CEGUI_MINGW_W64_FOUND FALSE )
    if( MINGW )
        if( CMAKE_CROSSCOMPILING )
            file( WRITE "${_TMP_C_PLUS_PLUS_SRC_FILE_NAME}" "
                #include <windef.h>
                #ifndef __MINGW64_VERSION_MAJOR
                    #error \"The compiler isn't MinGW-w64.\"
                #endif
                __MINGW64_VERSION_MAJOR;__MINGW64_VERSION_MINOR" )
            execute_process(
                COMMAND /usr/bin/env bash -c -o pipefail "''${CMAKE_CXX_COMPILER} -E ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}} \"${_TMP_C_PLUS_PLUS_SRC_FILE_NAME}\" | tail -1''"
                OUTPUT_STRIP_TRAILING_WHITESPACE
                RESULT_VARIABLE _FIND_MINGW_W64_VER__RUN_RESULT
                OUTPUT_VARIABLE _FIND_MINGW_W64_VER__RESULT
                TIMEOUT 60 )
            if( NOT _FIND_MINGW_W64_VER__RUN_RESULT EQUAL 0 )
                set( _FIND_MINGW_W64_VER__RESULT )
            endif()
        else()
            file( WRITE "${_TMP_C_PLUS_PLUS_SRC_FILE_NAME}" "
                #include <windef.h>
                #ifndef __MINGW64_VERSION_MAJOR
                    #error \"The compiler isn't MinGW-w64.\"
                #endif
                #include <iostream>
                int main()
                {
                    std::cout << __MINGW64_VERSION_MAJOR << \";\" << __MINGW64_VERSION_MINOR << std::flush;
                }" )
            try_run( _FIND_MINGW_W64_VER__RUN_RESULT
                     _FIND_MINGW_W64_VER__BUILD_RESULT
                     "${PROJECT_BINARY_DIR}"
                     "${_TMP_C_PLUS_PLUS_SRC_FILE_NAME}"
                     RUN_OUTPUT_VARIABLE _FIND_MINGW_W64_VER__RESULT )
            if( NOT (_FIND_MINGW_W64_VER__BUILD_RESULT AND (_FIND_MINGW_W64_VER__RUN_RESULT EQUAL 0) ) )
                set( _FIND_MINGW_W64_VER__RESULT )
            endif()
        endif()
        list( LENGTH _FIND_MINGW_W64_VER__RESULT _FIND_MINGW_W64_VER__RESULT__LEN )
        if( _FIND_MINGW_W64_VER__RESULT__LEN EQUAL 2 )
            set( CEGUI_MINGW_W64_FOUND TRUE )
            list( GET _FIND_MINGW_W64_VER__RESULT 0 CEGUI_MINGW_W64_VER_MAJOR )
            list( GET _FIND_MINGW_W64_VER__RESULT 1 CEGUI_MINGW_W64_VER_MINOR )
            if(     (CEGUI_MINGW_W64_VER_MAJOR LESS 3) OR
                    ((CEGUI_MINGW_W64_VER_MAJOR EQUAL 3) AND (CEGUI_MINGW_W64_VER_MINOR LESS 1)) )
                message( WARNING "If you use MinGW-w64, only version 3.1 and up is officially supported. Note: that's MinGW-w64's version, *not* GCC's version!" )
            endif()
        else()
            message( WARNING "If you use MinGW, only the MinGW-w64 flavour (version 3.1 and up) is officially supported. Note: that's MinGW-w64's version, *not* GCC's version! " )
        endif()
    endif()
endmacro()

macro( cegui_check_msvc )
    if(MSVC)
        # Older than minimally supported version of Visual Studio 2013
        if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 18.0) 
            message(FATAL_ERROR "You are trying to use a version of Visual Studio older than Visual Studio 2013. Please"
                " use Visual Studio 2013 or newer, since older versions are not supported and will neither compile nor run.")
        endif ()
    endif()
endmacro()