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

/// @file ComputePruneTables.cpp
///
/// @brief Functions for for computing prune tables.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license

#include <fstream>
#include <iomanip>

#include "Constants.h"

using namespace std;

unsigned short* PruneTableSolutionBuffer;

fstream PruneTablesFileCSV;

/// The method that handles writing the header of all the prune tables used inside ComputeSolutions.cpp, inside a CSV file.
///
/// I/O errors are silently ignored, for now.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
void _WritePruneTablesHeader() {
    // CSV File (header)
    //
    // Any I/O problem will be just ignored, for now.

    if (PruneTablesFileCSV.good())
        PruneTablesFileCSV << "Initial State" << SeparatorCSV << "Button Pressed" << SeparatorCSV << "Resulting State" << SeparatorCSV << "Cached Remaining Depth" << SeparatorCSV << "Actual Remaining Depth" << SeparatorCSV << "Decision" << endl;
}

/// The method that handles writing all the content of all the prune tables used inside ComputeSolutions.cpp, inside a CSV file.
///
/// I/O errors are silently ignored, for now.
///
/// @param[in] OnlySafeSolutions     If **true**, solutions with left/right button presses are discarded, if **false** nothing happens.
/// @param[in] InternalState         The starting internal state.
/// @param[in] CurrentRecursiveDepth The current recursive depth.
/// @param[in] MaximumRecursiveDepth The maximum recursive depth allowed to be reached. It's equal to the minimum solution length considered by _ComputeSolutions().
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
void _WritePruneTablesContent(bool OnlySafeSolutions, unsigned short InternalState, short CurrentRecursiveDepth, short MaximumRecursiveDepth) {
    unsigned short TestSolution;

    int i;

    for (i=0;i<7;i++) {
        // Skips all unsafe solutions (ones with Left/Right), if specified.

        if (OnlySafeSolutions && (ButtonCodes[i] == 0x04 || ButtonCodes[i] == 0x08))
            continue;

        if (MinimumSolutionLength[RainbowTable[i][InternalState]] + CurrentRecursiveDepth + 1 > MaximumRecursiveDepth && PruneTablesFileCSV.good()) {
            for (i=0;i<7;i++) {
                // Skips all unsafe solutions (ones with Left/Right), if specified.

                if (OnlySafeSolutions && (ButtonCodes[i] == 0x04 || ButtonCodes[i] == 0x08))
                    continue;

                TestSolution = RainbowTable[i][InternalState];

                // CSV File (content)
                //
                // Any I/O problem will be just ignored, for now.

                if (PruneTablesFileCSV.good()) {
                    PruneTablesFileCSV << hex << uppercase;

                    PruneTablesFileCSV << "0x" << setw(4) << setfill('0') << InternalState;

                    PruneTablesFileCSV << SeparatorCSV;

                    PruneTablesFileCSV << ButtonNames[i];

                    PruneTablesFileCSV << SeparatorCSV;

                    PruneTablesFileCSV << "0x" << setw(4) << setfill('0') << TestSolution;

                    PruneTablesFileCSV << dec;

                    PruneTablesFileCSV << SeparatorCSV;

                    PruneTablesFileCSV << MinimumSolutionLength[TestSolution];

                    PruneTablesFileCSV << SeparatorCSV;

                    PruneTablesFileCSV << (MaximumRecursiveDepth - CurrentRecursiveDepth - 1);

                    PruneTablesFileCSV << SeparatorCSV;

                    if (MinimumSolutionLength[TestSolution] + CurrentRecursiveDepth + 1 > MaximumRecursiveDepth)
                        PruneTablesFileCSV << "PRUNED";
                    else
                        PruneTablesFileCSV << "OK";

                    PruneTablesFileCSV << endl;
                }
            }

            break;
        }
    }
}

/// The main logic behing computing all the all the prune tables used inside ComputeSolutions.cpp.
///
/// Search is still pruned using the result of ComputeMinimumSolutionLengths.cpp.
/// Tables are saved inside a CSV file, I/O errors are silently ignored, for now.
///
/// @param[in] OnlySafeSolutions     If **true**, solutions with left/right button presses are discarded, if **false** nothing happens.
/// @param[in] InternalState         The starting internal state.
/// @param[in] MaximumRecursiveDepth The maximum recursive depth allowed to be reached. It's equal to the minimum solution length considered by _ComputeSolutions().
/// @param[in] CurrentRecursiveDepth The current recursive depth. It's automatically set to zero in the function's declaration.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
void _FindPruneTables(bool OnlySafeSolutions, unsigned short InternalState, unsigned short MaximumRecursiveDepth, unsigned short CurrentRecursiveDepth = 0) {
    if (CurrentRecursiveDepth < MaximumRecursiveDepth) {
        unsigned short RecursiveInternalState;

        _WritePruneTablesContent(OnlySafeSolutions,InternalState,CurrentRecursiveDepth,MaximumRecursiveDepth);

        for (unsigned int i=0;i<7;i++) {
            // Skips all unsafe solutions (ones with Left/Right), if specified.

            if (OnlySafeSolutions && (ButtonCodes[i] == 0x04 || ButtonCodes[i] == 0x08))
                continue;

            RecursiveInternalState = RainbowTable[i][InternalState];

            PruneTableSolutionBuffer[CurrentRecursiveDepth] = i;

            // Pruning

            if (RecursiveInternalState == InternalStateTargetValue || MinimumSolutionLength[RecursiveInternalState] + CurrentRecursiveDepth + 1 > MaximumRecursiveDepth)
                continue;

            _FindPruneTables(OnlySafeSolutions,RecursiveInternalState,MaximumRecursiveDepth,CurrentRecursiveDepth + 1);
        }
    }
}

/// This method computes all the prune tables used inside ComputeSolutions.cpp to prune their recursive search.
///
/// Are only saved inside a CSV file, I/O errors are silently ignored, for now.
///
/// @param[in] OnlySafeSolutions If **true**, solutions with left/right button presses are discarded, if **false** nothing happens. main() invokes this function twice, once with this parameter as **false**, once as **true**.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
void _ComputePruneTables(bool OnlySafeSolutions) {
    const unsigned short ConsideredMinimumSolutionLength = MinimumSolutionLength[InternalStateInitialValue];

    PruneTableSolutionBuffer = new unsigned short[ConsideredMinimumSolutionLength];

    if (OnlySafeSolutions)
        PruneTablesFileCSV.open(FileNameSafeSolutionsPruneTablesCSV,ios::out | ios::trunc);
    else
        PruneTablesFileCSV.open(FileNameAllSolutionsPruneTablesCSV,ios::out | ios::trunc);

    _WritePruneTablesHeader();

    _FindPruneTables(OnlySafeSolutions,InternalStateInitialValue,ConsideredMinimumSolutionLength);

    delete[] PruneTableSolutionBuffer;

    PruneTablesFileCSV.close();
}
