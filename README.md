# NGPL ( Nebula's Graphics Programming Library )
![NGPL](https://images-ext-2.discordapp.net/external/ACmqwZci4ce49pQy9D3p7Wi_LmVjSxh6n6IpN2SGsjQ/https/repository-images.githubusercontent.com/732112944/c2d86da1-eda5-4443-a8cf-1731a46797b9?format=webp&width=1107&height=622)

NGPL is a versatile graphics programming library designed to simplify the development of high-performance graphical applications and GUIs. 

Built on top of SDL2, NGPL offers a range of tools and functionalities that make it ideal for game development, interactive media, and GUI creation. 

Whether you're a seasoned developer or just starting out, NGPL provides an accessible platform to bring your graphical projects to life.

## To The Stars.
- NGPL is compiled using MinGW32 GCC.
- NGPL is built upon version 2.28.5 of the SDL2 libraries and 2.8.2 of the SDL2_Image libraries.
- It is recommended that developers also install MinGW32 GCC compiler to utilize NGPL as intended.

# Installation

This guide provides step-by-step instructions on how to install NGPL on Windows.

## Step 1: Download NGPL

1. Visit the *Releases* section of the repository ( https://github.com/TheDotBat/NGPL/releases ).
2. Download the latest version of the NGPL engine.
3. Save the file to a location on your computer, such as `Downloads`.

## Step 2: Extract NGPL

1. Navigate to the location where you downloaded NGPL (e.g., `Downloads` folder).
2. Right-click on the downloaded file (it might be a `.zip` or `tar.gz` file) and select **Extract All...**.
3. In the dialog that appears, choose the directory where you want to extract NGPL. This will be your NGPL installation directory. For example, you can create a new folder like `C:\NGPL` or `D:\MyProjects\NGPL`.

## Step 3: Add NGPL's scripts to the System PATH

Adding NGPL's scripts to the system PATH allows you to run them from any command prompt location.

1. Locate your NGPL installation directory and note its **scripts** path. 
    - For example: `C:\NGPL\NGPL\scripts`
2. Press the **Windows Key**, and type `Environment Variables`.
3. Select the option that appears in the control panel.
    - If the above steps do not work, try these:
        - Right-click on the **Start** button and select **System**.
        - Under *Device Specifications*, click on **Advanced system settings**.
        - In the **System Properties** window, go to the **Advanced** tab.
        - Click on the **Environment Variables...** button at the bottom.
4. Under the **System variables** section, find and select the **Path** variable.
5. Click **Edit...**.
6. In the **Edit Environment Variable** window, click **New** and add the full path to your NGPL scripts directory (e.g., `C:\NGPL\NGPL\scripts`).
7. Click **OK** to close each window.

## Step 4: Verify Installation

To verify that NGPL has been successfully added to your PATH:

1. Open a new Command Prompt window.
2. Type `echo %PATH%` and press **Enter**.
3. Check if the NGPL path is listed in the output.
4. Try running the `compile-NGPL` script by typing `compile-NGPL` followed by the project files you wish to compile.

    - **You Should See This Error Message**:

![NGPL](https://media.discordapp.net/attachments/1132862338521894934/1190716154096910388/image.png?ex=65a2cfd5&is=65905ad5&hm=3c5524b1c07ecd1f4cf8c275fde90eb0288f1da0b6ceadf0a73c4c2dfd063385&=&format=webp&quality=lossless&width=524&height=70)

5. Simply type the command presented in the error message. 
    - For example: ```setx NGPL_DIR "C:\Path\To\NGPL\NGPL_x86"``` and you should be all set.
6. Now try running compile-NGPL on your project files again...

![NGPL](https://media.discordapp.net/attachments/1132862338521894934/1190716154310832199/image-1.png?ex=65a2cfd5&is=65905ad5&hm=c1994fca37077e90fcc997d74c5d9dd2135258ba3ee004f5dbf3bef090153355&=&format=webp&quality=lossless&width=337&height=108)

You should now be able to use the `compile-NGPL` script from any location in the Command Prompt on your Windows system.

---

### Troubleshooting

- If the `compile-NGPL` script does not run, ensure that the path you added to the PATH variable is correct and points to the directory where `compile-NGPL.bat` is located.
- Remember that changes to the PATH variable will only take effect in new Command Prompt windows. Existing windows will not reflect these changes.

---

# A Look at compile-NGPL

The `compile-NGPL` script is a powerful tool designed to streamline the compilation process for projects using the NGPL engine. It simplifies the build process, allowing developers to compile their C projects with a single command and easily integrate custom libraries.

## Prerequisites

- **MinGW32 GCC Installation:** This script requires the MinGW32 GCC compiler to be properly installed and configured on your system. Ensure that GCC is accessible from the Command Prompt, meaning it should be added to your system's PATH.

## How it Works

- **`compile-NGPL.bat`** is a batch script that automates the compilation of C files using the GCC compiler.
- It takes a C source file as input and produces an executable in the `dist` directory.

### Script Parameters

- **Primary Argument:** The path to the C source file to compile.
- **Optional Arguments:**
  - Additional include directories (`-I`).
  - Additional library directories (`-L`).
  - Additional libraries to link against (`-l`).

These optional arguments allow developers to include their project-specific headers, link additional libraries, and specify custom libraries required by their project.

### Script Commands

1. **Checks Input:** The script first checks if a source file has been provided. If not, it displays usage instructions.
2. **Sets Variables:**
   - `INPUT_FILE` is set to the path of the source file.
   - `INCLUDE_DIR` includes NGPL's include directory and any additional specified.
   - `LIB_DIR` includes NGPL's library directory and any additional specified.
   - `LIBS` specifies libraries to link (e.g., `-NGPL` for NGPL's library) along with any custom libraries.
3. **Compilation Process:**
   - The script creates a `dist` directory if it doesn't exist.
   - It copies `SDL2.dll` from NGPL's directory to `dist`.
   - It then invokes GCC to compile the source file, including the specified directories and linking the necessary libraries, including any specified custom libraries.
4. **Outputs Executable:** The compiled executable is placed in the `dist` directory.

## Usage Example

```batch
compile-NGPL.bat "path\to\source\file.c" "-Iadditional\include\path" "-Ladditional\lib\path" "-lsomeCustomLibrary -lanotherCustomLibrary"
```

In this command:
- `"path\to\source\file.c"` is the C source file to compile.
- `"-Iadditional\include\path"` specifies additional include directories.
- `"-Ladditional\lib\path"` specifies additional library directories.
- `"-lsomeCustomLibrary -lanotherCustomLibrary"` specifies additional libraries to link against.

This command compiles `file.c`, including headers from `additional\include\path`, linking libraries from `additional\lib\path`, and linking against `someCustomLibrary` and `anotherCustomLibrary`.

---

### Customizing the Script

Developers with specific needs can modify the `compile-NGPL.bat` script to fit their project's requirements, such as adding more compiler flags, handling different file types, or integrating with different build systems.

---
