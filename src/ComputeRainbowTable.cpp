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

/// @file ComputeRainbowTable.cpp
///
/// @brief Functions for computing the algorithm's rainbow table.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license

#include "Constants.h"

/// This is the main logic behind the method for computing the algorithm's rainbow table.
///
/// @param[in] ButtonID              The Sega Genesis/Mega Drive button ID. Values are defined inside the *ButtonCodes* array, used also inside it, names inside *ButtonNames* instead.
/// @param[in] StartingInternalState The algorithm's internal state to alter using *ButtonID*'s value.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
void _FillRainbowTable(unsigned short ButtonID, unsigned short StartingInternalState) {
    RainbowTable[ButtonID][StartingInternalState] = StartingInternalState ^ ButtonCodes[ButtonID];

    if (RainbowTable[ButtonID][StartingInternalState] & 0x1) {
        RainbowTable[ButtonID][StartingInternalState] >>= 1;

        RainbowTable[ButtonID][StartingInternalState] ^= 0x8810;
    } else
        RainbowTable[ButtonID][StartingInternalState] >>= 1;
}

/// This is the method for computing the algorithm's rainbow table.
///
/// It's done to avoid computing the same things over and over, and to speed up operations in general by caching them in RAM.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
void _ComputeRainbowTable() {
    unsigned int i;
    unsigned int j;

    for (i=0;i<7;i++)
        for (j=0;j<0x10000;j++)
            _FillRainbowTable(i & 0xFF,j & 0xFFFF);
}
