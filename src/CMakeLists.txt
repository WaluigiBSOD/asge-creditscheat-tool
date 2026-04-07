# Alien Storm (Genesis) Credits Select Cheat Tool
# Copyright (C) 2022-present WaluigiBSOD (waluigibsod.github.io)
#
# This file is part of Alien Storm (Genesis) Credits Select Cheat Tool.
#
# Alien Storm (Genesis) Credits Select Cheat Tool is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Alien Storm (Genesis) Credits Select Cheat Tool is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.

# Minimum required CMake version

cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

# Program version

set(RELEASE_SERVICE_VERSION_MAJOR "1")
set(RELEASE_SERVICE_VERSION_MINOR "2")
set(RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}")

# Project name

project(asge-creditscheat-tool VERSION ${RELEASE_SERVICE_VERSION})

# Project requires at least the C++11 standard

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adding source files to build the main executable

add_executable(asge-creditscheat-tool ComputeMinimumSolutionLengths.cpp ComputeMinimumSolutionLengths.h ComputePruneTables.cpp ComputePruneTables.h ComputeRainbowTable.cpp ComputeRainbowTable.h ComputeSolutions.cpp ComputeSolutions.h Constants.cpp Constants.h main.cpp PrintSplashScreen.cpp PrintSplashScreen.h)