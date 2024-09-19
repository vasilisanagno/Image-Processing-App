# Image Processing App

This C++ command-line application provides a comprehensive suite of image processing functionalities, including export, deletion, color inversion, histogram equalization, mirroring, grayscale conversion, scaling, and rotation. Designed with performance and user experience in mind, it offers robust error handling and optimized algorithms for efficient execution.

## Table of Contents

- [Features](#features)
  - [Robust Error Handling](#robust-error-handling)
  - [Supported Image Formats](#supported-image-formats)
  - [Efficient Memory Management](#efficient-memory-management)
  - [Optimized Algorithms](#optimized-algorithms)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compiling the Program](#compiling-the-program)
- [Usage](#usage)
- [Commands](#commands)
- [Error Handling](#error-handling)

## Features

### Robust Error Handling
The application ensures smooth operation by providing detailed error messages for file conflicts, permission issues, and other possible errors during execution.

### Supported Image Formats
- **PGM (Portable Gray Map):** Supports grayscale images.
- **PPM (Portable Pixmap):** Supports color images.

This flexibility allows users to work with both color and grayscale images.

### Efficient Memory Management
Optimized memory usage ensures that the application can handle large image files without unnecessary resource consumption, improving performance across different systems.

### Optimized Algorithms
The application utilizes optimized algorithms for all image processing tasks, ensuring fast execution and responsiveness even for large images or complex operations.

## Getting Started

### Prerequisites

Ensure that you have a C++ compiler installed on your system. Some popular options are:
- **GCC** (for Linux)
- **Clang** (for macOS)
- **MinGW** (for Windows)

### Compiling the Program

In the `src` folder, you can find all the necessary source code files. Use the provided Makefile to compile the program. Open a terminal in the `src` directory and run:

```
make all
./imageProcessingApp
```
## Usage

Once the program is compiled, you can run it using the following steps:

1. Open a terminal in the directory containing the compiled executable.
2. Run the program by typing ```./imageProcessingApp```.
3. Enter the desired commands from the list below to perform different image processing tasks.

## Commands

- `e <$token> as <filename>`: Export the image with the specified token to a file.
- `d <$token>`: Delete the image with the specified token.
- `n <$token>`: Invert the colors of the image with the specified token.
- `z <$token>`: Equalize the histogram of the image with the specified token.
- `m <$token>`: Mirror the image vertically.
- `g <$token>`: Convert the image to grayscale.
- `s <$token> by <factor>`: Scale the image by the given factor.
- `r <$token> clockwise <X> times`: Rotate the image clockwise or counterclockwise by the specified number of times.
- `q`: Quit the program.

## Error Handling

The program provides error messages in the following situations:

- **If the exported file already exists:** `[ERROR] File exists`
- **If the user doesn't have permission to create or write to the file:** `[ERROR] Unable to create file`
- **If the image is already grayscale:** `[NOP] Already grayscale $token`
