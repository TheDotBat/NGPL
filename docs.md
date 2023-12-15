
# Nebula Engine Documentation

## Core Module (`core.py`)

The `core.py` module serves as a Python wrapper for the `core.dll` C library, facilitating the use of its functions in Python through the `ctypes` module.

### Functions

#### `add`
- **Description**: Adds two integers.
- **Arguments**: 
  - `int`: First integer.
  - `int`: Second integer.
- **Returns**: `int` - The sum of the two integers.

#### `Nebula_CreateWindow`
- **Description**: Creates a new window.
- **Arguments**: 
  - `int`: Width of the window.
  - `int`: Height of the window.
- **Returns**: `c_void_p` - A pointer to the created window.

## Objects Module (`objects.py`)

The `objects.py` module is a Python wrapper for the `objects.dll` C library. It primarily deals with geometric objects and their operations.

### Classes

#### `Vector2`
- **Fields**:
  - `x` (`c_float`): The x-coordinate.
  - `y` (`c_float`): The y-coordinate.
- **Methods**:
  - `getMagnitude`
    - **Description**: Calculates the magnitude of the vector.
    - **Arguments**: None.
    - **Returns**: `c_float` - The magnitude of the vector.
