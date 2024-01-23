cmake_minimum_required(VERSION 3.26)
project(qt_minesweeper)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Change this to your Qt installation path
set(CMAKE_PREFIX_PATH "path/to/your/Qt/installation")

# For example:
#set(CMAKE_PREFIX_PATH "/Users/ryanhecht/Qt/6.6.1/macos")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(qt_minesweeper app/main.cpp
        app/appplication.qrc
        app/mainwindow.cpp
        app/mainwindow.h
        app/tile.cpp
        app/tile.h
        app/constants.h
        app/gamelogichandler.cpp
        app/gamelogichandler.h)
target_link_libraries(qt_minesweeper
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

