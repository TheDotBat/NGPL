# Nebula Engine
![NebulaWP](https://images-ext-2.discordapp.net/external/ACmqwZci4ce49pQy9D3p7Wi_LmVjSxh6n6IpN2SGsjQ/https/repository-images.githubusercontent.com/732112944/c2d86da1-eda5-4443-a8cf-1731a46797b9?format=webp&width=1107&height=622)

## To The Stars.

- Nebula-0.0.1 was compiled using MinGW32 GCC.
- Nebula is built upon version 2.28.5 of the SDL2 libraries.
- It is recommended that developers also install MinGW32 GCC compiler to utilize Nebula as intended.

# Installation

This guide provides step-by-step instructions on how to install Nebula on Windows.

## Step 1: Download Nebula

1. Visit the *Releases* section of the repository.
2. Download the latest version of the Nebula engine.
3. Save the file to a location on your computer, such as `Downloads`.

## Step 2: Extract Nebula

1. Navigate to the location where you downloaded Nebula (e.g., `Downloads` folder).
2. Right-click on the downloaded file (it might be a `.zip` or `tar.gz` file) and select **Extract All...**.
3. In the dialog that appears, choose the directory where you want to extract Nebula. This will be your Nebula installation directory. For example, you can create a new folder like `C:\Nebula` or `D:\MyProjects\Nebula`.

## Step 3: Add Nebula's scripts to the System PATH

Adding Nebula's scripts to the system PATH allows you to run them from any command prompt location.

1. Locate your Nebula installation directory and note its **scripts** path. 
    - For example: `C:\Nebula\Nebula_x86\scripts`
2. Press the **Windows Key**, and type `Environment Variables`.
3. Select the option that appears in the control panel.
    - If the above steps do not work, try these:
        - Right-click on the **Start** button and select **System**.
        - Under *Device Specifications*, click on **Advanced system settings**.
        - In the **System Properties** window, go to the **Advanced** tab.
        - Click on the **Environment Variables...** button at the bottom.
4. Under the **System variables** section, find and select the **Path** variable.
5. Click **Edit...**.
6. In the **Edit Environment Variable** window, click **New** and add the full path to your Nebula scripts directory (e.g., `C:\Nebula\Nebula_x86\scripts`).
7. Click **OK** to close each window.

## Step 4: Verify Installation

To verify that Nebula has been successfully added to your PATH:

1. Open a new Command Prompt window.
2. Type `echo %PATH%` and press **Enter**.
3. Check if the Nebula path is listed in the output.
4. Try running the `compile-Nebula` script by typing `compile-Nebula` followed by the project files you wish to compile.

You should now be able to use the `compile-Nebula` script from any location in the Command Prompt on your Windows 11 system.

---

### Troubleshooting

- If the `compile-Nebula` script does not run, ensure that the path you added to the PATH variable is correct and points to the directory where `compile-Nebula.bat` is located.
- Remember that changes to the PATH variable will only take effect in new Command Prompt windows. Existing windows will not reflect these changes.

### Notes

- The above instructions assume that the `compile-Nebula` script and other necessary files are included in the Nebula download and are located in the `Nebula_x86\scripts` directory of the extracted folder.
- Adjust the paths and instructions as needed based on the actual structure and requirements of the Nebula engine.

---

---

# A Look at compile-Nebula

The `compile-Nebula` script is a powerful tool designed to streamline the compilation process for projects using the Nebula engine. It simplifies the build process, allowing developers to compile their C projects with a single command and easily integrate custom libraries.

## Prerequisites

- **MinGW32 GCC Installation:** This script requires the MinGW32 GCC compiler to be properly installed and configured on your system. Ensure that GCC is accessible from the Command Prompt, meaning it should be added to your system's PATH.

## How it Works

- **`compile-Nebula.bat`** is a batch script that automates the compilation of C files using the GCC compiler.
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
   - `INCLUDE_DIR` includes Nebula's include directory and any additional specified.
   - `LIB_DIR` includes Nebula's library directory and any additional specified.
   - `LIBS` specifies libraries to link (e.g., `-lNebula` for Nebula's library) along with any custom libraries.
3. **Compilation Process:**
   - The script creates a `dist` directory if it doesn't exist.
   - It copies `SDL2.dll` from Nebula's directory to `dist`.
   - It then invokes GCC to compile the source file, including the specified directories and linking the necessary libraries, including any specified custom libraries.
4. **Outputs Executable:** The compiled executable is placed in the `dist` directory.

## Usage Example

```batch
compile-Nebula.bat "path\to\source\file.c" "-Iadditional\include\path" "-Ladditional\lib\path" "-lsomeCustomLibrary -lanotherCustomLibrary"
```

In this command:
- `"path\to\source\file.c"` is the C source file to compile.
- `"-Iadditional\include\path"` specifies additional include directories.
- `"-Ladditional\lib\path"` specifies additional library directories.
- `"-lsomeCustomLibrary -lanotherCustomLibrary"` specifies additional libraries to link against.

This command compiles `file.c`, including headers from `additional\include\path`, linking libraries from `additional\lib\path`, and linking against `someCustomLibrary` and `anotherCustomLibrary`.

---

### Customizing the Script

Developers with specific needs can modify the `compile-Nebula.bat` script to fit their project's requirements, such as adding more compiler flags, handling different file types, or integrating with different build systems.

---
