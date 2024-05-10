## Introduction

Minimal cimgui demo made with CMake project format.

![Cimgui Example Screenshot](images/MinimalCimgui.png)

The project includes the following dependencies:

* [cimgui](https://github.com/cimgui/cimgui) - C bindings to ImGui.
* [glfw](https://github.com/glfw/glfw) - Windowing and Input.
* [glad](https://github.com/Dav1dde/glad) - OpenGL Function Loader.

## Using cimgui in a CMake Project 

The following files are used for using cimgui as CMake dependency:

* `3rdparty/cimgui` - directory with cimgui headers copied from the original repository. This is a git submodule in this repository.
* `cmake/cimgui.cmake` - CMake module that defines variables `CIMGUI_LIBRARY` and `CIMGUI_INCLUDE_DIRS`.

## Environment Setup

### Debian-based Systems

The following instructions apply to:

* Ubuntu 24.04, 22.04, 20.04
* Debian 12, 11

```
sudo apt-get install -y \
    build-essential \
    cmake \
    xorg-dev \
    libgl1-mesa-dev \
    libfreetype6-dev
```

### RedHat-based Systems

The following instructions apply to:

* Fedora 22 and higher

```
sudo dnf install -y \
    gcc gcc-c++ make \
    cmake \
    mesa-libGL-devel \
    libXrandr-devel \
    libXinerama-devel \
    libXcursor-devel \
    libXi-devel \
    freetype-devel
```

## Building

Check out sources with `--recursive` parameter for 3rd-party libraries:

```
git clone --recursive https://github.com/Postrediori/MinimalCimgui.git
```

Prepare build with CMake and build executables

```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
make install
```

## Running

Using `make install` will copy the executable to `bundle` directory:

```
./bundle/MinimalCimgui
```
