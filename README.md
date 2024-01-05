# NDL ( Nebula's Development Library )
![NDL](https://images-ext-2.discordapp.net/external/ACmqwZci4ce49pQy9D3p7Wi_LmVjSxh6n6IpN2SGsjQ/https/repository-images.githubusercontent.com/732112944/c2d86da1-eda5-4443-a8cf-1731a46797b9?format=webp&width=1107&height=622)

NDL is a versatile development library designed to simplify the development of high-performance graphical applications (games) and GUIs.

Built on top of SDL2, NDL offers a range of tools and functionalities that make it ideal for game development, interactive media, and GUI creation. 

Whether you're a seasoned developer or just starting out, NDL provides an accessible platform to bring your graphical projects to life.

## To The Stars.
- NDL is compiled using MinGW32 GCC.
- NDL is built upon version 2.28.5 of the SDL2 libraries and 2.8.2 of the SDL2_Image libraries.
- NDL incorporates the cJSON JSON parser from Dave Gamble. ( https://github.com/DaveGamble/cJSON )
- It is recommended that developers also install MinGW32 GCC compiler to utilize NDL as intended.

# Installation

This guide provides step-by-step instructions on how to install NDL on Windows.

## Step 1: Download NDL

1. Visit the *Releases* section of the repository ( https://github.com/TheDotBat/NDL/releases ).
2. Download the latest version of the NDL engine.
3. Save the file to a location on your computer, such as `Downloads`.

## Step 2: Extract NDL

1. Navigate to the location where you downloaded NDL (e.g., `Downloads` folder).
2. Right-click on the downloaded file (it might be a `.zip` or `tar.gz` file) and select **Extract All...**.
3. In the dialog that appears, choose the directory where you want to extract NDL. This will be your NDL installation directory. For example, you can create a new folder like `C:\NDL` or `D:\MyProjects\NDL`.

## Step 3: Add NDL's scripts to the System PATH

Adding NDL's scripts to the system PATH allows you to run them from any command prompt location.

1. Locate your NDL installation directory and note its **scripts** path. 
    - For example: `C:\NDL\NDL\scripts`
2. Press the **Windows Key**, and type `Environment Variables`.
3. Select the option that appears in the control panel.
    - If the above steps do not work, try these:
        - Right-click on the **Start** button and select **System**.
        - Under *Device Specifications*, click on **Advanced system settings**.
        - In the **System Properties** window, go to the **Advanced** tab.
        - Click on the **Environment Variables...** button at the bottom.
4. Under the **System variables** section, find and select the **Path** variable.
5. Click **Edit...**.
6. In the **Edit Environment Variable** window, click **New** and add the full path to your NDL scripts directory (e.g., `C:\NDL\NDL\scripts`).
7. Click **OK** to close each window.

## Step 4: Verify Installation

To verify that NDL has been successfully added to your PATH:

1. Open a new Command Prompt window.
2. Type `echo %PATH%` and press **Enter**.
3. Check if the NDL path is listed in the output.
4. Try running the `compile-NDL` script by typing `compile-NDL` followed by the project files you wish to compile.

    - **You Should See This Error Message**:

![NDL](https://cdn.discordapp.com/attachments/1092575082125213859/1192797570632790016/image.png?ex=65aa624d&is=6597ed4d&hm=db94c5740d2c8d2320c1ff59cd7aeae0a0aea828ad1465b5151e4fb958fc1c8a&)

5. Simply type the command presented in the error message. 
    - For example: ```setx NDL_DIR "C:\Path\To\NDL\NDL_x86"``` and you should be all set.
6. Now try running compile-NDL on your project files again...

![NDL](https://cdn.discordapp.com/attachments/1092575082125213859/1192797570934784011/image.png?ex=65aa624e&is=6597ed4e&hm=a2c2fcee92314b42d2a8e15a063dd8b8367234062ee90c7b97fc2cd29053d65f&)

You should now be able to use the `compile-NDL` script from any location in the Command Prompt on your Windows system.

---

### Troubleshooting

- If the `compile-NDL` script does not run, ensure that the path you added to the PATH variable is correct and points to the directory where `compile-NDL.bat` is located.
- Remember that changes to the PATH variable will only take effect in new Command Prompt windows. Existing windows will not reflect these changes.

---

# A Look at compile-NDL

The `compile-NDL` script is a powerful tool designed to streamline the compilation process for projects using the NDL engine. It simplifies the build process, allowing developers to compile their C projects with a single command and easily integrate custom libraries.

## Prerequisites

- **MinGW32 GCC Installation:** This script requires the MinGW32 GCC compiler to be properly installed and configured on your system. Ensure that GCC is accessible from the Command Prompt, meaning it should be added to your system's PATH.

## How it Works

- **`compile-NDL.bat`** is a batch script that automates the compilation of C files using the GCC compiler.
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
   - `INCLUDE_DIR` includes NDL's include directory and any additional specified.
   - `LIB_DIR` includes NDL's library directory and any additional specified.
   - `LIBS` specifies libraries to link (e.g., `-NDL` for NDL's library) along with any custom libraries.
3. **Compilation Process:**
   - The script creates a `dist` directory if it doesn't exist.
   - It copies `SDL2.dll` from NDL's directory to `dist`.
   - It then invokes GCC to compile the source file, including the specified directories and linking the necessary libraries, including any specified custom libraries.
4. **Outputs Executable:** The compiled executable is placed in the `dist` directory.

## Usage Example

```batch
compile-NDL.bat "path\to\source\file.c" "-Iadditional\include\path" "-Ladditional\lib\path" "-lsomeCustomLibrary -lanotherCustomLibrary"
```

In this command:
- `"path\to\source\file.c"` is the C source file to compile.
- `"-Iadditional\include\path"` specifies additional include directories.
- `"-Ladditional\lib\path"` specifies additional library directories.
- `"-lsomeCustomLibrary -lanotherCustomLibrary"` specifies additional libraries to link against.

This command compiles `file.c`, including headers from `additional\include\path`, linking libraries from `additional\lib\path`, and linking against `someCustomLibrary` and `anotherCustomLibrary`.

---

### Customizing the Script

Developers with specific needs can modify the `compile-NDL.bat` script to fit their project's requirements, such as adding more compiler flags, handling different file types, or integrating with different build systems.

---
