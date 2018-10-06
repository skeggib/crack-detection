# Crack detection

First project of the image processing course in the Polytech Paris-Sud engineer school.

The main goal of this project is to get familiar with features detection in grayscale images. For 
this, we develop a toolchain that aims to detect cracks in road images. The algorithms are 
implemented in C++ using the OpenCV library.

## Requirements

- CMake
- OpenCV

## Building the project

### Linux

Create the 'build' folder and move into it:

```bash
mkdir build
cd build
```

Generate the project using cmake:

```bash
cmake ..
```
Build the project:

```bash
make
```

### Windows

Create the 'build' folder and move into it:

```bash
mkdir build
cd build
```

Generate the project using cmake (use `cmake --help` to get the list of generators). For example:

```bash
cmake .. -G "Visual Studio 15 2017 Win64"
```

Build the project:

```bash
msbuild ALL_BUILD.vcxproj [/property:Configuration=Release]
```

Copy the needed OpenCV DLLs into the `build/Debug` and `build/Release` folders.

## Usage

### `seuilGris`

Applies a binary filter on an input image and saves the results in an output image:

```bash
./seuilGris <threshold> <input> <output>
```

The threshold must be between 0 and 1 (1 is the maximum value of the image).

### `sobel`

Applies a sobel filter and a binary filter on an input image and saves the result in an output image:

```bash
./sobel <input> <output>
```

### `evaluation`

Compares a binary image with a truth image and displays the precision and the recall.

```bash
./evaluation <truth> <binary_image>
```

### `laplacien`

Applies a gaussian filter, a laplacian filter then a binary filter on an input image and saves the result in an output image:

```bash
./laplacien <input> <output>
```