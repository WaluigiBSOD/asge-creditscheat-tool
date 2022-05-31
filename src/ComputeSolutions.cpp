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

/// @file ComputeSolutions.cpp
///
/// @brief Functions for computing all the solutions of a certain minimum length, for a certain initial internal state.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license

#include <fstream>

#include "Constants.h"

unsigned short* SolutionBuffer;

fstream SolutionsFileCSV;

/// The main logic behing computing all the solutions of a certain minimum length.
///
/// Search is pruned using the result of ComputeMinimumSolutionLengths.cpp.
/// Solutions found are also saved inside a CSV file, I/O errors are silently ignored.
///
/// @param[in] OnlySafeSolutions     If **true**, solutions with left/right button presses are discarded, if **false** nothing happens.
/// @param[in] InternalState         The starting internal state.
/// @param[in] MaximumRecursiveDepth The maximum recursive depth allowed to be reached. It's equal to the minimum solution length considered by _ComputeSolutions().
/// @param[in] CurrentRecursiveDepth The current recursive depth. It's automatically set to zero in the function's declaration.
///
/// @return The number of solutions found.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
unsigned long long _FindSolutions(bool OnlySafeSolutions, unsigned short InternalState, unsigned short MaximumRecursiveDepth, unsigned short CurrentRecursiveDepth = 0) {
    unsigned long long retNUMBER = 0;

    if (CurrentRecursiveDepth < MaximumRecursiveDepth) {
        unsigned short RecursiveInternalState;

        for (unsigned int i=0;i<7;i++) {
            // Skips all the unsafe solutions (ones with Left/Right), if specified.

            if (OnlySafeSolutions && (ButtonCodes[i] == 0x04 || ButtonCodes[i] == 0x08))
                continue;

            RecursiveInternalState = RainbowTable[i][InternalState];

            SolutionBuffer[CurrentRecursiveDepth] = i;

            // CSV File
            //
            // Any I/O problem will be just ignored.

            if (RecursiveInternalState == InternalStateTargetValue && SolutionsFileCSV.good()) {
                for (unsigned int j=0;j<MinimumSolutionLength[InternalStateInitialValue];j++) {
                    SolutionsFileCSV << ButtonNames[SolutionBuffer[j]];

                    if (j + 1 < MinimumSolutionLength[InternalStateInitialValue])
                        SolutionsFileCSV << ';';
                }

                SolutionsFileCSV << endl;
            }


            // Pruning
            //
            // As it's referred to the minimum solution length*after an input*, the value of MinimumSolutionLength[RecursiveInternalState] has to be incremented by one.

            if (RecursiveInternalState == InternalStateTargetValue)
                retNUMBER++;
            else if (MinimumSolutionLength[RecursiveInternalState] + CurrentRecursiveDepth + 1 > MaximumRecursiveDepth)
                continue;

            retNUMBER += _FindSolutions(OnlySafeSolutions,RecursiveInternalState,MaximumRecursiveDepth,CurrentRecursiveDepth + 1);
        }
    }

    return retNUMBER;
}

/// This function computes all the solution of a certain minimum length.
///
/// Solutions found are also saved inside a CSV file, I/O errors are silently ignored.
///
/// @param[in] OnlySafeSolutions If **true**, solutions with left/right button presses are discarded, if **false** nothing happens. main() invokes this function twice, once with this parameter as **false**, once as **true**.
///
/// @return The number of solutions found.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
unsigned long long _ComputeSolutions(bool OnlySafeSolutions) {
    const unsigned short ConsideredMinimumSolutionLength = MinimumSolutionLength[InternalStateInitialValue];

    SolutionBuffer = new unsigned short[ConsideredMinimumSolutionLength];

    // Any file opening problem makes only the function that computes ignore it, the program will not be halted.

    if (OnlySafeSolutions)
        SolutionsFileCSV.open(FileNameSafeSolutionsCSV,ios::out | ios::trunc);
    else
        SolutionsFileCSV.open(FileNameAllSolutionsCSV,ios::out | ios::trunc);

    unsigned long long retNUMBER = _FindSolutions(OnlySafeSolutions,InternalStateInitialValue,ConsideredMinimumSolutionLength);

    delete[] SolutionBuffer;

    SolutionsFileCSV.close();

    return retNUMBER;
}
