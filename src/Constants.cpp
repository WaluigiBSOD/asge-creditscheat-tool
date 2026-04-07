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

/// @file      Constants.cpp
///
/// @brief     Constants file. All the program's constant are defined in this file.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 License

#include <string>

using namespace std;

// Program

extern const string ProgramName =                           "Alien Storm (Genesis) Credits Select Cheat Tool";

extern const string ProgramVersion =                        "1.2";

// Splash Screen

extern const unsigned char SplashScreenSpacingLeft =        1;

extern const unsigned char SplashScreenWidth =              64;

// Rainbow Tables

unsigned short** RainbowTable;

unsigned short* MinimumSolutionLength;

// Buttons

extern const unsigned short ButtonCodes[7] = {
    0x01,       // Up
    0x02,       // Down
    0x04,       // Left
    0x08,       // Right
    0x10,       // C
    0x20,       // A
    0x40        // B
};

extern const string ButtonNames[7] = {
    "Up",       // 0x01
    "Down",     // 0x02
    "Left",     // 0x04
    "Right",    // 0x08
    "C",        // 0x10
    "A",        // 0x20
    "B"         // 0x40
};

// Internal State

extern const unsigned short InternalStateInitialValue =     0x0000; // Game default is 0x0000.
extern const unsigned short InternalStateTargetValue =      0x3929; // Game default is 0x3929.

// Prune Tables

extern const string FileNameAllSolutionsPruneTablesCSV =    "all_solutions_prune.csv";
extern const string FileNameSafeSolutionsPruneTablesCSV =   "safe_solutions_prune.csv";

// Compute Solutions

extern const string FileNameAllSolutionsCSV =               "all_solutions.csv";
extern const string FileNameSafeSolutionsCSV =              "safe_solutions.csv";

// CSV Separator

extern const char SeparatorCSV =                            ',';

// Exit Codes

extern const char RainbowTableMemoryAllocationError =       1;

extern const char FileErrorAllSolutionsPruneTablesCSV =     2;
extern const char FileErrorSafeSolutionsPruneTablesCSV =    3;

extern const char FileErrorAllSolutionsCSV =                4;
extern const char FileErrorSafeSolutionsCSV =               5;
