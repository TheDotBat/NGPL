@echo off
echo Compiling Nebula...

:: Create destination directories if they do not exist
if not exist Nebula mkdir Nebula
if not exist Nebula\Nebula_x86 mkdir Nebula\Nebula_x86
if not exist Nebula\Nebula_x86\lib mkdir Nebula\Nebula_x86\lib
if not exist Nebula\Nebula_x86\include mkdir Nebula\Nebula_x86\include
if not exist Nebula\Nebula_x86\scripts mkdir Nebula\Nebula_x86\scripts

:: Compile Nebula
gcc -c src\core\Nebula_Core.c -o Nebula\Nebula_x86\lib\Nebula_Core.o
gcc -c src\audio\Nebula_Audio.c -o Nebula\Nebula_x86\lib\Nebula_Audio.o
gcc -c src\graphics\Nebula_Graphics.c -o Nebula\Nebula_x86\lib\Nebula_Graphics.o
gcc -c src\math\Nebula_Math.c -o Nebula\Nebula_x86\lib\Nebula_Math.o
gcc -c src\util\Nebula_Util.c -o Nebula\Nebula_x86\lib\Nebula_Util.o

:: Copy SDL2 object files before final static lib is created
cd SDL2-2.28.5\lib
xcopy *.o ..\..\Nebula\Nebula_x86\lib
cd ..
cd ..

:: Create static library
ar -rcs Nebula\Nebula_x86\lib\libNebula.a Nebula\Nebula_x86\lib\*.o

:: Remove object files
del Nebula\Nebula_x86\lib\*.o

:: Copy headers
echo Copying headers...
xcopy include Nebula\Nebula_x86\include

:: Copy SDL2 dynamic library
xcopy SDL2-2.28.5\SDL2.dll Nebula\Nebula_x86

:: Create compile-Nebula.bat file
echo Creating compile-Nebula.bat file...
(
    echo @echo off
    echo if "%%~1"=="" ^(
    echo    echo Usage: compile-Nebula.bat [path_to_c_file] [additional_include_dirs] [additional_lib_dirs] [additional_libraries]
    echo    exit \b 1
    echo ^)
    echo.
    echo set INPUT_FILE=%%~1
    echo set ADDITIONAL_INCLUDES=%%~2
    echo set ADDITIONAL_LIBS=%%~3
    echo set CUSTOM_LIBS=%%~4
    echo set INCLUDE_DIR=-I.\Nebula\Nebula_x86\include %%ADDITIONAL_INCLUDES%%
    echo set LIB_DIR=-L.\Nebula\Nebula_x86\lib %%ADDITIONAL_LIBS%%
    echo set LIBS=-lNebula %%CUSTOM_LIBS%%
    echo.
    echo echo Compiling %%INPUT_FILE%%...
    echo if not exist dist mkdir dist
    echo xcopy Nebula\Nebula_x86\SDL2.dll dist
    echo gcc %%INPUT_FILE%% %%INCLUDE_DIR%% %%LIB_DIR%% %%LIBS%% -o dist\%%~n1.exe
    echo.
    echo echo Compilation complete! Executable: %%~n1.exe
) > Nebula\Nebula_x86\scripts\compile-Nebula.bat

:: Create nebula-config.txt file
echo Creating nebula-config.txt file...
(
    echo Nebula comes with a script to compile your application for you.
    echo Assuming you have Nebula installed locally...
    echo Enter the command: .\Nebula\Nebula_x86\compile-Nebula.bat *yourCFile*.c
    echo and your project will be compiled and linked against Nebula for you.
    echo If you choose to manually compile then follow the #Nebula Configuration# porion of this document.
    echo.
    echo.
    echo.
    echo.
    echo # Nebula Configuration
    echo # Include this information in your project's build settings
    echo Include: -INebula\Nebula_x86\include
    echo Library: -LNebula\Nebula_x86\lib -lNebula
) > Nebula\Nebula_x86\nebula-config.txt

:: Copy Nebula's README to the final directory
xcopy README.txt Nebula

echo Build complete!
