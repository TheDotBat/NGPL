@echo off
echo Compiling NGPL...

:: Create destination directories if they do not exist
if not exist NGPL mkdir NGPL
if not exist NGPL\NGPL_x86 mkdir NGPL\NGPL_x86
if not exist NGPL\NGPL_x86\lib mkdir NGPL\NGPL_x86\lib
if not exist NGPL\NGPL_x86\include mkdir NGPL\NGPL_x86\include
if not exist NGPL\NGPL_x86\scripts mkdir NGPL\NGPL_x86\scripts

:: Compile NGPL
gcc -c src\core\NGPL_Core.c -o NGPL\NGPL_x86\lib\NGPL_Core.o
gcc -c src\math\NGPL_Math.c -o NGPL\NGPL_x86\lib\NGPL_Math.o
gcc -c src\util\NGPL_Util.c -o NGPL\NGPL_x86\lib\NGPL_Util.o
gcc -c src\graphics\NGPL_Graphics.c -o NGPL\NGPL_x86\lib\NGPL_Graphics.o
gcc -c src\audio\NGPL_Audio.c -o NGPL\NGPL_x86\lib\NGPL_Audio.o
gcc -c src\game\NGPLG.c -o NGPL\NGPL_x86\lib\NGPLG.o
gcc -c src\game\NGPLG_Physics.c -o NGPL\NGPL_x86\lib\NGPLG_Physics.o
gcc -c cJSON\cJSON.c -o NGPL\NGPL_x86\lib\cJSON.o

:: Copy SDL2 object files before final static lib is created
cd SDL2-2.28.5\lib
xcopy *.o ..\..\NGPL\NGPL_x86\lib
cd ..
cd ..

:: Create static library
ar -rcs NGPL\NGPL_x86\lib\libNGPL.a NGPL\NGPL_x86\lib\*.o

:: Remove object files
del NGPL\NGPL_x86\lib\*.o

:: Copy headers
echo Copying headers...
xcopy include NGPL\NGPL_x86\include

:: Copy SDL2 dynamic library
xcopy SDL2-2.28.5\*.dll NGPL\NGPL_x86

:: Create compile-NGPL.bat file
echo Creating compile-NGPL.bat file...
(
    echo @echo off
    echo if "%%~1"=="^" (
    echo    echo Usage: compile-NGPL.bat [path_to_c_file] [additional_include_dirs] [additional_lib_dirs] [additional_libraries]
    echo    exit /b 1
    echo ^)
    echo.
    echo set INPUT_FILE=%%~1
    echo set ADDITIONAL_INCLUDES=%%~2
    echo set ADDITIONAL_LIBS=%%~3
    echo set CUSTOM_LIBS=%%~4
    echo.
    echo REM Check for NGPL_DIR environment variable
    echo if not defined NGPL_DIR ^(
    echo    echo NGPL directory not set. Please set the NGPL_DIR environment variable.
    echo    echo Type the following command: setx NGPL_DIR "C:\Path\To\NGPL\NGPL_x86"
    echo    exit /b 1
    echo ^)
    echo.
    echo REM Use the NGPL_DIR environment variable
    echo set INCLUDE_DIR=-I%%NGPL_DIR%%\include %%ADDITIONAL_INCLUDES%%
    echo set LIB_DIR=-L%%NGPL_DIR%%\lib %%ADDITIONAL_LIBS%%
    echo set LIBS=-lNGPL %%CUSTOM_LIBS%%
    echo.
    echo echo Compiling %%INPUT_FILE%%...
    echo if not exist dist mkdir dist
    echo xcopy %%NGPL_DIR%%\*.dll dist
    echo gcc %%INPUT_FILE%% %%INCLUDE_DIR%% %%LIB_DIR%% %%LIBS%% -o dist\%%~n1.exe
    echo.
    echo echo Compilation complete! Executable: %%~n1.exe
) > NGPL\NGPL_x86\scripts\compile-NGPL.bat

:: Create NGPL-config.txt file
echo Creating NGPL-config.txt file...
(
    echo NGPL comes with a script to compile your application for you.
    echo Assuming you have NGPL installed locally...
    echo Enter the command: .\NGPL\NGPL_x86\compile-NGPL.bat *yourCFile*.c
    echo and your project will be compiled and linked against NGPL for you.
    echo If you choose to manually compile then follow the #NGPL Configuration# porion of this document.
    echo.
    echo.
    echo.
    echo.
    echo # NGPL Configuration
    echo # Include this information in your project's build settings
    echo Include: -INGPL\NGPL_x86\include
    echo Library: -LNGPL\NGPL_x86\lib -lNGPL
) > NGPL\NGPL_x86\NGPL-config.txt

:: Copy NGPL's README to the final directory
xcopy README.txt NGPL

echo.
echo Build complete!
echo.
echo.
echo To The Stars!
echo.
echo.
