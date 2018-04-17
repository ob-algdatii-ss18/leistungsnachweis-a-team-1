cmake_minimum_required(VERSION 3.6)

project(Editor)

# The editor version
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)

# Find all qt packages
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

set(Editor_src ${PROJECT_SOURCE_DIR}/mainwindow.cpp)
set(Editor_hdr ${PROJECT_SOURCE_DIR}/mainwindow.h)
set(Editor_ui ${PROJECT_SOURCE_DIR}/mainwindow.ui)
set(EditorBin_src ${PROJECT_SOURCE_DIR}/main.cpp)

#qt5_wrap_cpp(Editor_hdr_moc ${Editor_hdr})
#qt_wrap_ui(Editor_ui_moc ${Editor_ui})
include_directories(../Engine/engine)

add_library(mainwindow mainwindow.cpp)
target_link_libraries(mainwindow Qt5::Widgets)

add_executable(editor main.cpp mainwindow)
target_link_libraries(editor mainwindow engine)