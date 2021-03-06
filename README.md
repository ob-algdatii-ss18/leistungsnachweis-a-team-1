# Visualizing the A Star Algorithm
[![Build Status](https://travis-ci.org/ob-algdatii-ss18/leistungsnachweis-a-team-1.svg?branch=master)](https://travis-ci.org/ob-algdatii-ss18/leistungsnachweis-a-team-1)
[![Coverage Status](https://coveralls.io/repos/github/ob-algdatii-ss18/leistungsnachweis-a-team-1/badge.svg?branch=testing)](https://coveralls.io/github/ob-algdatii-ss18/leistungsnachweis-a-team-1?branch=testing)

![Der A Stern Editor](https://github.com/ob-algdatii-ss18/leistungsnachweis-a-team-1/blob/master/editor.PNG "Der A Star Editor")
## Description
This program implements the [A* Algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm) for an undirected Graph in C++. In order to visualize the operation there is a GUI where you can alter the graph. You can change the size and the costs of the edges for example. In order to compare the algorithm with alternatives, you can execute Dijkstra and BFS, too.

## Build
First you have to download and install [Qt](https://www.qt.io/download) on your computer. At least version 5.10.1 is required. Then you have to adjust the Qt-Path in the file "CMakeLists.txt" (e.g. set(CMAKE_PREFIX_PATH "F:\\LIBRARIES\\Qt\\5.10.1\\mingw53_32;")).
After that you have to copy following files from the Qt-Path to $Projectfolder$\cmake-build-debug\src\Editor:
* Qt5Widgetsd.dll
* Qt5Guid.dll
* Qt5Cored.dll

## [Documentation](https://ob-algdatii-ss18.github.io/leistungsnachweis-a-team-1/doxygen/html/)
