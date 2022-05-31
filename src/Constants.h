// Alien Storm (Genesis) Credits Select Cheat Tool
// Copyright (C) 2022-present WaluigiBSOD (waluigibsod.github.io)
//
// This file is part of Alien Storm (Genesis) Credits Select Cheat Tool.
//
// Alien Storm (Genesis) Credits Select Cheat Tool is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Alien Storm (Genesis) Credits Select Cheat Tool is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

/// @file Constants.h
///
/// @brief Constants.cpp's header file. It's used to import the program's constants inside every source file.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license

#include <iostream>

using namespace std;

#pragma once

// Program

extern const string ProgramName;

extern const string ProgramVersion;

// Splash Screen

extern const unsigned int SplashScreenSpacingLeft;

extern const unsigned int SplashScreenWidth;

// Rainbow Tables

extern unsigned short** RainbowTable;

extern unsigned short* MinimumSolutionLength;

// Buttons

extern const unsigned short ButtonCodes[7];

extern const string ButtonNames[7];

// Internal State

extern const unsigned short InternalStateInitialValue;
extern const unsigned short InternalStateTargetValue;

// Compute Solutions

extern const string FileNameAllSolutionsCSV;
extern const string FileNameSafeSolutionsCSV;

// Prune Tables

extern const string FileNameAllSolutionsPruneTablesCSV;
extern const string FileNameSafeSolutionsPruneTablesCSV;
