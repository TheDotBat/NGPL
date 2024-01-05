@echo off
echo Compiling NDL...

:: Create destination directories if they do not exist
if not exist NDL mkdir NDL
if not exist NDL\NDL_x86 mkdir NDL\NDL_x86
if not exist NDL\NDL_x86\lib mkdir NDL\NDL_x86\lib
if not exist NDL\NDL_x86\include mkdir NDL\NDL_x86\include
if not exist NDL\NDL_x86\scripts mkdir NDL\NDL_x86\scripts

:: Compile NDL
gcc -c src\core\NDL_C.c -o NDL\NDL_x86\lib\NDL_C.o
gcc -c src\math\NDL_M.c -o NDL\NDL_x86\lib\NDL_M.o
gcc -c src\util\NDL_U.c -o NDL\NDL_x86\lib\NDL_U.o
gcc -c src\graphics\NDL_G.c -o NDL\NDL_x86\lib\NDL_G.o
gcc -c src\audio\NDL_A.c -o NDL\NDL_x86\lib\NDL_A.o
gcc -c src\game\NDL_P.c -o NDL\NDL_x86\lib\NDL_P.o
gcc -c cJSON\cJSON.c -o NDL\NDL_x86\lib\cJSON.o

:: Copy SDL2 object files before final static lib is created
cd SDL2-2.28.5\lib
xcopy *.o ..\..\NDL\NDL_x86\lib
cd ..
cd ..

:: Create static library
ar -rcs NDL\NDL_x86\lib\libNDL.a NDL\NDL_x86\lib\*.o

:: Remove object files
del NDL\NDL_x86\lib\*.o

:: Copy headers
echo Copying headers...
xcopy include NDL\NDL_x86\include

:: Copy SDL2 dynamic library
xcopy SDL2-2.28.5\*.dll NDL\NDL_x86

:: Create compile-NDL.bat file
echo Creating compile-NDL.bat file...
(
    echo @echo off
    echo if "%%~1"=="^" (
    echo    echo Usage: compile-NDL.bat [path_to_c_file] [additional_include_dirs] [additional_lib_dirs] [additional_libraries]
    echo    exit /b 1
    echo ^)
    echo.
    echo set INPUT_FILE=%%~1
    echo set ADDITIONAL_INCLUDES=%%~2
    echo set ADDITIONAL_LIBS=%%~3
    echo set CUSTOM_LIBS=%%~4
    echo.
    echo REM Check for NDL_DIR environment variable
    echo if not defined NDL_DIR ^(
    echo    echo NDL directory not set. Please set the NDL_DIR environment variable.
    echo    echo. 
    echo    echo Either navigate to your NDL installation directory and run the install-NDL script as administrator
    echo    echo for use of NDL scripts system-wide without path specification.
    echo    echo.
    echo    echo OR
    echo    echo.
    echo    echo Type the following command: setx NDL_DIR "C:\Path\To\NDL\NDL_x86"
    echo    echo.
    echo    exit /b 1
    echo ^)
    echo.
    echo REM Use the NDL_DIR environment variable
    echo set INCLUDE_DIR=-I%%NDL_DIR%%\include %%ADDITIONAL_INCLUDES%%
    echo set LIB_DIR=-L%%NDL_DIR%%\lib %%ADDITIONAL_LIBS%%
    echo set LIBS=-lNDL %%CUSTOM_LIBS%%
    echo.
    echo echo Compiling %%INPUT_FILE%%...
    echo if not exist dist mkdir dist
    echo xcopy %%NDL_DIR%%\*.dll dist
    echo gcc %%INPUT_FILE%% %%INCLUDE_DIR%% %%LIB_DIR%% %%LIBS%% -o dist\%%~n1.exe
    echo.
    echo echo Compilation complete! Executable: %%~n1.exe
) > NDL\NDL_x86\scripts\compile-NDL.bat



:: Create NDL-config.txt file
echo Creating NDL-config.txt file...
(
    echo NDL comes with a script to compile your application for you.
    echo Assuming you have NDL installed locally...
    echo Enter the command: .\NDL\NDL_x86\compile-NDL.bat *yourCFile*.c
    echo and your project will be compiled and linked against NDL for you.
    echo If you choose to manually compile then follow the #NDL Configuration# porion of this document.
    echo.
    echo.
    echo # NDL Installation
    echo # Each version of NDL comes with an install-NDL script.
    echo # Simply navigate to where you installed NDL, and right-click run as administrator, if possible, and you should have system wide access to NDL scripts such as compile-NDL.
    echo.
    echo.
    echo # NDL Configuration
    echo # Include this information in your project's build settings
    echo Include: -INDL\NDL_x86\include
    echo Library: -LNDL\NDL_x86\lib -lNDL
) > NDL\NDL_x86\NDL-config.txt

:: Copy NDL's install scripts to the final directory
xcopy NewProject-NDL.bat NDL\NDL_x86\scripts
xcopy install-NDL.ps1 NDL\NDL_x86\scripts
if not exist NDL\NDL_x86\scripts\admin-perms mkdir NDL\NDL_x86\scripts\admin-perms
xcopy install-NDL-ADMIN.ps1 NDL\NDL_x86\scripts\admin-perms

:: Copy NDL's New Project Guide to the final directory
xcopy NewProjectGuide.md NDL\NDL_x86

:: Copy NDL's README to the final directory
xcopy README.txt NDL

echo.
echo Build complete!
echo.
echo.
echo To The Stars!
echo.
echo.


:: C:\Program Files (x86)\Python312-32\Scripts\;C:\Program Files (x86)\Python312-32\;C:\Program Files\Python312\Scripts\;C:\Program Files\Python312\;C:\Python311\Scripts\;C:\Python311\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\NVIDIA Corporation\NVIDIA NvDLISR;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\Git\cmd;C:\Program Files\dotnet\;C:\Program Files\nodejs\;C:\ProgramData\chocolatey\bin;C:\Program Files\WindowsPowerShell\Scripts;C:\MinGW32\bin;