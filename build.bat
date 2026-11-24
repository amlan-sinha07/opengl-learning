@echo off
setlocal EnableExtensions EnableDelayedExpansion

rem Build and run the OpenGL Learning project with MinGW-w64 / MSYS2.
rem Usage:
rem   build.bat        Compile and run
rem   build.bat build  Compile only
rem   build.bat clean  Remove generated build files

set "ROOT=%~dp0"
pushd "%ROOT%" >nul

if /i "%~1"=="clean" goto :clean
if not "%~1"=="" if /i not "%~1"=="build" goto :usage

set "BUILD_ONLY=0"
if /i "%~1"=="build" set "BUILD_ONLY=1"

if not defined CXX set "CXX=g++"
if not defined CC set "CC=gcc"
if not defined GLFW_LIBS set "GLFW_LIBS=-lglfw3"
if not defined OPENGL_LIBS set "OPENGL_LIBS=-lopengl32 -lgdi32"
if not defined STDLIB_EXTRA_LIBS set "STDLIB_EXTRA_LIBS=-lstdc++exp"

where "%CXX%" >nul 2>&1
if errorlevel 1 (
    echo [ERROR] C++ compiler "%CXX%" was not found in PATH.
    echo         Open an MSYS2 UCRT64 terminal or add its bin directory to PATH.
    goto :fail
)

set "CXX_EXE="
for /f "delims=" %%P in ('where "%CXX%" 2^>nul') do (
    if not defined CXX_EXE set "CXX_EXE=%%P"
)
rem MSYS2 UCRT64 installation
if not defined MSYS2_UCRT64_ROOT (
    set "MSYS2_UCRT64_ROOT=C:\msys64\ucrt64"
)

set "TOOLCHAIN_BIN=%MSYS2_UCRT64_ROOT%\bin"
set "TOOLCHAIN_LIB_DIR=%MSYS2_UCRT64_ROOT%\lib"

rem Verify GLFW installation
if not exist "%TOOLCHAIN_LIB_DIR%\libglfw3.a" (
    if not exist "%TOOLCHAIN_LIB_DIR%\libglfw3.dll.a" (
        echo [ERROR] GLFW library not found.
        echo Expected directory: %TOOLCHAIN_LIB_DIR%
        goto :fail
    )
)

if not exist "!TOOLCHAIN_LIB_DIR!\libglfw3.a" (
    if not exist "!TOOLCHAIN_LIB_DIR!\libglfw3.dll.a" (
        echo [ERROR] GLFW library not found.
        echo Expected: !TOOLCHAIN_LIB_DIR!
        goto :fail
    )
)

if not exist "%ROOT%src\main.cpp" (
    echo [ERROR] Could not find src\main.cpp.
    goto :fail
)

set "BUILD_DIR=%ROOT%build"
set "BIN_DIR=%ROOT%bin"
set "OUTPUT=%BIN_DIR%\opengl-learning.exe"
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
if not exist "%BIN_DIR%" mkdir "%BIN_DIR%"

rem Gather every C++ source file under src. This keeps the script in sync
rem when new implementation files are added to nested source directories.
set "SOURCES="
for /r "%ROOT%src" %%F in (*.cpp) do (
    set "SOURCES=!SOURCES! "%%~fF""
)
if not defined SOURCES (
    echo [ERROR] No .cpp files were found under src\.
    goto :fail
)

rem Include common project-local dependency layouts plus optional GLAD_ROOT.
set "INCLUDE_FLAGS=-I"%ROOT%src" -I"%ROOT%third_party\glad\include""
if exist "%ROOT%third_party\glad\include\glad\gl.h" (
    set "INCLUDE_FLAGS=!INCLUDE_FLAGS! -I"%ROOT%third_party\glad\include""
)
if exist "%ROOT%dependencies\glad\include\glad\gl.h" (
    set "INCLUDE_FLAGS=!INCLUDE_FLAGS! -I"%ROOT%dependencies\glad\include""
)
if defined GLAD_ROOT (
    set "INCLUDE_FLAGS=!INCLUDE_FLAGS! -I"%GLAD_ROOT%\include""
)
if defined GLAD_INCLUDE_DIR (
    set "INCLUDE_FLAGS=!INCLUDE_FLAGS! -I"%GLAD_INCLUDE_DIR%""
)
if defined GLFW_INCLUDE_DIR (
    set "INCLUDE_FLAGS=!INCLUDE_FLAGS! -I"%GLFW_INCLUDE_DIR%""
)
if defined GLM_INCLUDE_DIR (
    set "INCLUDE_FLAGS=!INCLUDE_FLAGS! -I"%GLM_INCLUDE_DIR%""
)

rem Prefer compiling the generated GLAD 2 C source when it is available.
rem Otherwise, the linker must be able to find a prebuilt library named glad.
if not defined GLAD_SOURCE_FILE if defined GLAD_ROOT if exist "%GLAD_ROOT%\src\gl.c" (
    set "GLAD_SOURCE_FILE=%GLAD_ROOT%\src\gl.c"
)
if not defined GLAD_SOURCE_FILE if exist "%ROOT%third_party\glad\src\gl.c" (
    set "GLAD_SOURCE_FILE=%ROOT%third_party\glad\src\gl.c"
)
if not defined GLAD_SOURCE_FILE if exist "%ROOT%dependencies\glad\src\gl.c" (
    set "GLAD_SOURCE_FILE=%ROOT%dependencies\glad\src\gl.c"
)
if not defined GLAD_SOURCE_FILE if exist "%ROOT%src\gl.c" (
    set "GLAD_SOURCE_FILE=%ROOT%src\gl.c"
)

set "GLAD_OBJECT_ARG="
if defined GLAD_SOURCE_FILE (
    if not exist "%GLAD_SOURCE_FILE%" (
        echo [ERROR] GLAD_SOURCE_FILE does not exist: "%GLAD_SOURCE_FILE%"
        goto :fail
    )
    where "%CC%" >nul 2>&1
    if errorlevel 1 (
        echo [ERROR] C compiler "%CC%" was not found. It is needed to compile GLAD's gl.c.
        goto :fail
    )
    echo [INFO] Compiling GLAD source: "%GLAD_SOURCE_FILE%"
    "%CC%" -std=c11 -Wall -Wextra !INCLUDE_FLAGS! -c "%GLAD_SOURCE_FILE%" -o "%BUILD_DIR%\glad.o"
    if errorlevel 1 goto :fail
    set "GLAD_OBJECT_ARG="%BUILD_DIR%\glad.o""
) else (
    if not defined GLAD_LIBS set "GLAD_LIBS=-lglad"
    echo [INFO] No GLAD source file detected; linking with !GLAD_LIBS!.
)

if not exist "%ROOT%shaders\vertex.vert" (
    echo [WARNING] shaders\vertex.vert was not found. The executable may fail when loading shaders.
)
if not exist "%ROOT%shaders\fragment.frag" (
    echo [WARNING] shaders\fragment.frag was not found. The executable may fail when loading shaders.
)

echo.
echo [INFO] Building OpenGL Learning...
echo [INFO] Compiler: %CXX%
echo [INFO] Output:   %OUTPUT%

"%CXX%" -std=c++23 -Wall -Wextra -Wpedantic -O0 -g -DDEBUG ^
    !INCLUDE_FLAGS! ^
    !SOURCES! ^
    !GLAD_OBJECT_ARG! ^
    -o "%OUTPUT%" ^
    -L"!TOOLCHAIN_LIB_DIR!" ^
    !GLFW_LIBS! !OPENGL_LIBS! !GLAD_LIBS! ^
    !STDLIB_EXTRA_LIBS!
    
if errorlevel 1 (
    echo.
    echo [ERROR] Build failed. Check the compiler output and dependency paths.
    goto :fail
)

rem Copy common MSYS2 runtime DLLs beside the executable when present.
rem Static-link configurations simply skip DLLs that do not exist.
for %%D in (glfw3.dll libstdc++-6.dll libgcc_s_seh-1.dll libwinpthread-1.dll) do (
    if exist "!TOOLCHAIN_BIN!%%D" copy /Y "!TOOLCHAIN_BIN!%%D" "%BIN_DIR%\" >nul
)

echo.
echo [SUCCESS] Build completed: %OUTPUT%
if "%BUILD_ONLY%"=="1" goto :done

echo [INFO] Running from the repository root so relative shader paths work...
echo.
"%OUTPUT%"
set "APP_EXIT_CODE=!ERRORLEVEL!"
popd >nul
endlocal & exit /b %APP_EXIT_CODE%

:clean
echo [INFO] Removing generated build output...
if exist "%ROOT%build" rmdir /s /q "%ROOT%build"
if exist "%ROOT%bin" rmdir /s /q "%ROOT%bin"
echo [SUCCESS] Clean complete.
popd >nul
endlocal & exit /b 0

:usage
echo Usage: build.bat [build^|clean]
popd >nul
endlocal & exit /b 2

:fail
popd >nul
endlocal & exit /b 1

:done
popd >nul
endlocal & exit /b 0
