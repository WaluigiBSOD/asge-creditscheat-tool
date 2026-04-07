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

/// @file      ComputePruneTables.cpp
///
/// @brief     Functions for for computing prune tables.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 License

#include <fstream>
#include <iomanip>

#include "Constants.h"

using namespace std;

unsigned short* PruneTableSolutionBuffer;

fstream PruneTablesFileCSV;

/// Writes the header of all the prune tables used inside ComputeSolutions.cpp, inside a CSV file.
///
/// @return    **True** if no file write error occurred, **false** otherwise.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 License

bool _WritePruneTablesHeader() {
    // CSV File (header)

    PruneTablesFileCSV << "Initial State" << SeparatorCSV << "Button Pressed" << SeparatorCSV << "Resulting State" << SeparatorCSV << "Cached Remaining Depth" << SeparatorCSV << "Actual Remaining Depth" << SeparatorCSV << "Decision" << endl;

    if (PruneTablesFileCSV.fail())
        return false;

    return true;
}

/// Writes all the content of all the prune tables used inside ComputeSolutions.cpp, inside a CSV file.
///
/// @param[in] OnlySafeSolutions     If **true**, solutions with left/right button presses are discarded, if **false** nothing happens.
/// @param[in] InternalState         The starting internal state.
/// @param[in] CurrentRecursiveDepth The current recursive depth.
/// @param[in] MaximumRecursiveDepth The maximum recursive depth allowed to be reached. It's equal to the minimum solution length considered by _ComputeSolutions().
///
/// @return    **True** if no file write error occurred, **false** otherwise.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 License

bool _WritePruneTablesContent(bool OnlySafeSolutions, unsigned short InternalState, short CurrentRecursiveDepth, short MaximumRecursiveDepth) {
    unsigned short TestSolution;

    for (unsigned char i=0;i<7;i++) {
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

                if (PruneTablesFileCSV.fail())
                    return false;
            }

            break;
        }
    }

    return true;
}

/// The main logic behind computing all the all the prune tables used inside ComputeSolutions.cpp.
///
/// Search is still pruned using the result of ComputeMinimumSolutionLengths.cpp.
/// Tables are saved inside a CSV file.
///
/// @param[in] OnlySafeSolutions     If **true**, solutions with left/right button presses are discarded, if **false** nothing happens.
/// @param[in] InternalState         The starting internal state.
/// @param[in] MaximumRecursiveDepth The maximum recursive depth allowed to be reached. It's equal to the minimum solution length considered by _ComputeSolutions().
/// @param[in] CurrentRecursiveDepth The current recursive depth. It's automatically set to zero in the function's declaration.
///
/// @return    **True** if no file write error occurred, **false** otherwise.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 License

bool _FindPruneTables(bool OnlySafeSolutions, unsigned short InternalState, unsigned short MaximumRecursiveDepth, unsigned short CurrentRecursiveDepth = 0) {
    if (CurrentRecursiveDepth < MaximumRecursiveDepth) {
        unsigned short RecursiveInternalState;

        if (!_WritePruneTablesContent(OnlySafeSolutions,InternalState,CurrentRecursiveDepth,MaximumRecursiveDepth))
            return false;

        for (unsigned char i=0;i<7;i++) {
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

    return true;
}

/// Computes all the prune tables used inside ComputeSolutions.cpp to prune their recursive search.
///
/// Are only saved inside a CSV file.
///
/// @param[in] OnlySafeSolutions If **true**, solutions with left/right button presses are discarded, if **false** nothing happens. main() invokes this function twice, once with this parameter as **false**, once as **true**.
///
/// @return    **True** if no file write and memory allocation errors occurred, **false** otherwise.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 License

bool _ComputePruneTables(bool OnlySafeSolutions) {
    const unsigned short ConsideredMinimumSolutionLength = MinimumSolutionLength[InternalStateInitialValue];

    PruneTableSolutionBuffer = new unsigned short[ConsideredMinimumSolutionLength];

    if (PruneTableSolutionBuffer == nullptr)
        return false;

    if (OnlySafeSolutions)
        PruneTablesFileCSV.open(FileNameSafeSolutionsPruneTablesCSV,ios::out | ios::trunc);
    else
        PruneTablesFileCSV.open(FileNameAllSolutionsPruneTablesCSV,ios::out | ios::trunc);

    if (PruneTablesFileCSV.is_open()) {
        if (_WritePruneTablesHeader())
            _FindPruneTables(OnlySafeSolutions,InternalStateInitialValue,ConsideredMinimumSolutionLength);

        PruneTablesFileCSV.close();
    } else {
        delete[] PruneTableSolutionBuffer;

        return false;
    }

    delete[] PruneTableSolutionBuffer;

    return true;
}
