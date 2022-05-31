# WaluigiBSOD
#
# waluigibsod.github.io

# Minimum required CMake version.

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

# Program version.

set(RELEASE_SERVICE_VERSION_MAJOR "1")
set(RELEASE_SERVICE_VERSION_MINOR "0")
set(RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}")

# Project name.

project(asge-creditscheat-tool VERSION ${RELEASE_SERVICE_VERSION})

# Project requires at least the C++11 standard.

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adding source files to build the main executable.

add_executable(asge-creditscheat-tool ComputeMinimumSolutionLengths.cpp ComputeMinimumSolutionLengths.h ComputePruneTables.cpp ComputePruneTables.h ComputeRainbowTable.cpp ComputeRainbowTable.h ComputeSolutions.cpp ComputeSolutions.h Constants.cpp Constants.h main.cpp PrintSplashScreen.cpp PrintSplashScreen.h)