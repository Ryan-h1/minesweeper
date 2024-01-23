# Minesweeper in Qt

Welcome to my Minesweeper game project, developed using Qt 6.6.1. This project uses Qt under the GNU Lesser General
Public License v3.0.

## Getting Started

### Prerequisites

To build and run this project, you will need:

- Qt 6.6.1
- CMake 3.26 or higher

Ensure that Qt is installed on your system. You can download the latest version of Qt from
the [Qt website](https://www.qt.io/).

### Configuration

This project uses CMake for its build process, instead of the traditional QMake used in many Qt projects. You will find
a `CMakeLists.txt` file at the root of the project, which handles the build configuration.

Before building the project, you need to set the prefix path to your Qt installation in the `CMakeLists.txt` file. This
can be done by modifying the line:

```cmake
set(CMAKE_PREFIX_PATH "path/to/your/Qt/installation")
```

Replace "path/to/your/Qt/installation" with the actual path to your Qt installation directory.

### Building the Project

To build the project, you can use any modern CMake-compatible IDE, such as CLion or Visual Studio. Alternatively,
navigate to the project directory in a terminal and run the following commands:

```shell
mkdir build
cd build
cmake ..
cmake --build .
```

### Running the Project

After a successful build, you can run the game from the build directory with the following command:

```shell
./Minesweeper
```

(On Windows, you may need to run `Minesweeper.exe` instead.)

## License

This project is licensed under the GNU General Public License v3.0. See the [LICENSE](LICENSE) file for details.

