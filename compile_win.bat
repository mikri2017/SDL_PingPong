@echo off

set MINGW_BIN_PATH=C:\Dev\MinGW\mingw32\bin

PATH=%PATH%;%MINGW_BIN_PATH%

set PROG_NAME=SDL_PingPong.exe

set CXX=g++.exe
set COMPILE_FILES=.\*.cpp
set CFLAGS_DEBUG=-Wall -fexceptions -g
set CFLAGS_RELEASE=-Wall -fexceptions -O2

set DEBUG_OUTPUT_FOLDER=bin\Debug
set DEBUG_OUTFILE=%DEBUG_OUTPUT_FOLDER%\%PROG_NAME%

set RELEASE_OUTPUT_FOLDER=bin\Release
set RELEASE_OUTFILE=%RELEASE_OUTPUT_FOLDER%\%PROG_NAME%

set SDL_PATH=C:\Dev\SDL
set PROC_BIT_DEPTH_PATH=x86_64-w64-mingw32

set SDL_INC_PARAM=^
-I%SDL_PATH%\MinGW_SDL3\%PROC_BIT_DEPTH_PATH%\include ^
-I%SDL_PATH%\MinGW_SDL3_image\%PROC_BIT_DEPTH_PATH%\include ^
-I%SDL_PATH%\MinGW_SDL3_mixer\%PROC_BIT_DEPTH_PATH%\include ^
-I%SDL_PATH%\MinGW_SDL3_ttf\%PROC_BIT_DEPTH_PATH%\include

set SDL_LIB_PARAM=^
-L%SDL_PATH%\MinGW_SDL3\%PROC_BIT_DEPTH_PATH%\lib ^
-L%SDL_PATH%\MinGW_SDL3_image\%PROC_BIT_DEPTH_PATH%\lib ^
-L%SDL_PATH%\MinGW_SDL3_mixer\%PROC_BIT_DEPTH_PATH%\lib ^
-L%SDL_PATH%\MinGW_SDL3_ttf\%PROC_BIT_DEPTH_PATH%\lib

set SDL_LD_PARAM=-lSDL3 -lSDL3_ttf -lSDL3_mixer

set BUILD_TYPE=%1

if "%BUILD_TYPE%" EQU "debug" (
    echo "Compiling in Debug mode"

    if not exist %DEBUG_OUTPUT_FOLDER%\*.* mkdir %DEBUG_OUTPUT_FOLDER%

    %CXX% %CFLAGS_DEBUG% %SDL_INC_PARAM% %SDL_LIB_PARAM% %COMPILE_FILES% -o %DEBUG_OUTFILE% %SDL_LD_PARAM%

    xcopy /E /Y assets %DEBUG_OUTPUT_FOLDER%\assets\
    xcopy /E /Y lang %DEBUG_OUTPUT_FOLDER%\lang\
    xcopy /E /Y deps\debug %DEBUG_OUTPUT_FOLDER%\
) else if "%BUILD_TYPE%" EQU "release" (
    echo "Compiling in Release mode"

    if not exist %RELEASE_OUTPUT_FOLDER%\*.* mkdir %RELEASE_OUTPUT_FOLDER%

    %CXX% %CFLAGS_RELEASE% %SDL_INC_PARAM% %SDL_LIB_PARAM% %COMPILE_FILES% -o %RELEASE_OUTFILE% %SDL_LD_PARAM%

    xcopy /E /Y assets %RELEASE_OUTPUT_FOLDER%\assets\
    xcopy /E /Y lang %RELEASE_OUTPUT_FOLDER%\lang\
    xcopy /E /Y deps\release %RELEASE_OUTPUT_FOLDER%\
) else if "%BUILD_TYPE%" EQU "clean" (
    echo "Clean all builds"

    if exist %DEBUG_OUTPUT_FOLDER%\*.* (
        rmdir /S /Q %DEBUG_OUTPUT_FOLDER%
    )

    if exist %RELEASE_OUTPUT_FOLDER%\*.* (
        rmdir /S /Q %RELEASE_OUTPUT_FOLDER%
    )
) else (
    echo "I don't understand you..."
)
