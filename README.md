# Image-Processing-App

This command-line application in C++ offers a variety of essential image processing functionalities, including export, delete, inversion, histogram equalization, mirroring, grayscale conversion, scaling, and rotation.

## Features

- **Robust Error Handling:**
  - The application provides robust error handling for file conflicts and permission issues, ensuring a smooth user experience.

- **Supported Image Formats:**
  - Supports PGM for grayscale images and PPM for color images, providing flexibility in processing different types of images.

- **Efficient Memory Management:**
  - The program incorporates efficient memory management techniques to optimize resource usage during image processing operations.

- **Optimized Algorithms:**
  - Utilizes optimized algorithms for various image processing tasks, ensuring fast and efficient execution.

## Getting Started

### Prerequisites

Make sure you have a C++ compiler installed on your system. If not, you can install one based on your operating system.

### Compiling the Program

In the `src` folder, you can find all the necessary source code files. Use the provided Makefile to compile the program. Open a terminal in the `src` directory and run:

```
make all
./imageProcessingApp
```
### Usage

To use the program, follow these steps:

1. Run the executable file.
2. Enter the corresponding commands as follows:

- `e <$token> as <filename>`: Export the image with the specified token to a file.
- `d <$token>`: Delete the image with the specified token.
- `n <$token>`: Invert the colors of the image with the specified token.
- `z <$token>`: Equalize the histogram of the image with the specified token.
- `m <$token>`: Mirror the image vertically.
- `g <$token>`: Convert the image to grayscale.
- `s <$token> by <factor>`: Scale the image by the given factor.
- `r <$token> clockwise <X> times`: Rotate the image clockwise or counterclockwise by the specified number of times.
- `q`: Quit the program.

### Error Handling

The program provides error messages in the following situations:

- **If the exported file already exists:** `[ERROR] File exists`
- **If the user doesn't have permission to create or write to the file:** `[ERROR] Unable to create file`
- **If the image is already grayscale:** `[NOP] Already grayscale $token`
