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

/// @file PrintSplashScreen.cpp
///
/// @brief Functions for displaying the initial splash screen.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license

#include <iostream>

#include "Constants.h"

using namespace std;

/// This function centers a string given in input, given a certain fixed width located inside Constants.cpp.
///
/// @param[in] ToCenter    The string to center. If empty or being a blank space, prints only a border and nothing else.
/// @param[in] PrintBorder Prints a border around it by default or if set to **true**, none if set to **false**.
///
/// @return If *ToCenter* is not blank or a space, *ToCenter*, but centered. Otherwise prints only a border.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
string _CenterString(string ToCenter = "", bool PrintBorder = true) {
    string retSTRING = "";

    if (ToCenter == "" || ToCenter.size() > SplashScreenWidth) {
        for (unsigned int i=0;i<SplashScreenSpacingLeft;i++)
            retSTRING += ' ';

        for (unsigned int i=0;i<SplashScreenWidth;i++)
            if (i == 0 || (i + 1) == SplashScreenWidth)
                retSTRING += '+';
            else
                retSTRING += '-';
    } else {
        unsigned int TotalSpacing = (SplashScreenWidth - ToCenter.size()) / 2;

        for (unsigned int i=0;i<TotalSpacing + SplashScreenSpacingLeft;i++)
            if (i == SplashScreenSpacingLeft && PrintBorder)
                retSTRING += '|';
            else
                retSTRING += ' ';

        retSTRING += ToCenter;

        for (unsigned int i=0;(i + 1)<TotalSpacing + (ToCenter.size() % 2);i++)
            retSTRING +=  ' ';

        if (PrintBorder)
            retSTRING += '|';
    }

    retSTRING += '\n';

    return retSTRING;
}

/// This method prints the splash screen at the very beginning of the program's execution.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
void _PrintSplashScreen() {
    cout << _CenterString();

    cout << _CenterString(ProgramName);

    cout << _CenterString();

    cout << _CenterString("Version " + ProgramVersion);

    cout << _CenterString(" ");

    cout << _CenterString("Copyright (C) 2022-present WaluigiBSOD (waluigibsod.github.io)");

    cout << _CenterString();

    cout << endl;
}
