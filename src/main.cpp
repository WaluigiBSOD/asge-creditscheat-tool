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

/// @file main.cpp
///
/// @brief Main program file.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license

#include <cmath>
#include <iomanip>

#include "Constants.h"

#include "PrintSplashScreen.h"

#include "ComputeRainbowTable.h"
#include "ComputePruneTables.h"
#include "ComputeMinimumSolutionLengths.h"
#include "ComputeSolutions.h"

/// This method allocates all the arrays that are put inside the heap.
///
/// It's done to avoid memory allocation issues, as in total they weight 64 KB.
/// May sound exaggerate, but usually default stack sizes are limited to a few megabytes.
/// Also, this is approximately 420.1025641 times the RAM that is needed for the internal state of a MT19937 PRNG algorithm instance, as a comparison.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
void _InitializeAllThatNeedsToBeInitialized() {
    unsigned int i;

    // Rainbow Table

    RainbowTable = new unsigned short*[7];

    for (i=0;i<7;i++)
        RainbowTable[i] = new unsigned short[0x10000];

    // Minimum Solution Length

    MinimumSolutionLength = new unsigned short[0x10000];

    for (i=0;i<0x10000;i++)
        MinimumSolutionLength[i] = 0;
}

/// This method deallocates all the arrays that are put inside the heap.
///
/// It's called at the end of the program, just before exiting.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
void _DeallocateAllThatNeedsToBeDeallocated() {
    // Rainbow Table

    for (unsigned int i=0;i<0x7;i++)
        delete[] RainbowTable[i];

    delete[] RainbowTable;

    // Minimum Solution Length

    delete[] MinimumSolutionLength;
}

/// The main program function.
///
/// Handles all the console output, calling functions and memory allocation/initializing/deallocation.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
int main() {
    // Splash Screen

    _PrintSplashScreen();

    // Memory allocation and initialization.

    _InitializeAllThatNeedsToBeInitialized();

    unsigned long long NumberOfAllSolutions;
    unsigned long long NumberOfSafeSolutions;

    // Caching

    cout << " ### Caching ###" << endl << endl;

    // Rainbow Table computation.

    cout << "Caching algorithm into a rainbow table ... ";

    _ComputeRainbowTable();

    cout << "Done!" << endl;

    // Minimum solution lengths computation.

    cout << "Caching minimum solution lengths (may take a minute or two) ... ";

    _ComputeMinimumSolutionLengths();

    cout << "Done!" << endl << endl;

    // Prune tables computation.

    cout << " ### Prune Tables ###" << endl << endl;

    cout << "Computing prune tables ";

    if ((InternalStateInitialValue != 0x0000) || (InternalStateTargetValue != 0x3929))
        cout << "(may take a bit longer than usual for non-standard intial/target values) ";

    cout << "... ";

    _ComputePruneTables(false);
    _ComputePruneTables(true);

    cout << "Done!" << endl << endl;

    cout << "A listing of them has been saved inside \"" << FileNameAllSolutionsPruneTablesCSV << "\" and \"" << FileNameSafeSolutionsPruneTablesCSV << "\", respectively." << endl << endl;

    // Computation of all/safe minimum length solutions.

    cout << " ### Minimum Length Solutions ###" << endl << endl;

    cout << hex;

    cout << uppercase;

    cout << "Chosen starting point is 0x" << setw(4) << setfill('0') << InternalStateInitialValue;

    if (InternalStateInitialValue != 0x0000)
        cout << " (game default is 0x0000)";

    cout << endl;

    cout << "Chosen target point is   0x" << setw(4) << setfill('0') << InternalStateTargetValue;

    if (InternalStateTargetValue != 0x3929)
        cout << " (game default is 0x3929)";

    cout << endl << endl;

    cout << dec;

    if (MinimumSolutionLength[InternalStateInitialValue] == 1)
        cout << "A solution of minimum length is " << MinimumSolutionLength[InternalStateInitialValue] << " input long, computing all the solutions of this length." << endl << endl;
    else
        cout << "A solution of minimum length is " << MinimumSolutionLength[InternalStateInitialValue] << " inputs long, computing all the solutions of this length." << endl << endl;

    cout << "Computing solutions ... ";

    NumberOfAllSolutions = _ComputeSolutions(false);
    NumberOfSafeSolutions = _ComputeSolutions(true);

    cout << "Done!" << endl << endl;

    cout << "All:  " << setw(5) << setfill(' ') << NumberOfAllSolutions << " (" << (((double)(NumberOfSafeSolutions) / (double)(pow(7,MinimumSolutionLength[InternalStateInitialValue]))) * (double)(100)) << "% of all the possible button combinations of length " << MinimumSolutionLength[InternalStateInitialValue] << ")" << endl;

    cout << "Safe: " << setw(5) << setfill(' ') << NumberOfSafeSolutions << " (" << (((double)(NumberOfSafeSolutions) / (double)(NumberOfAllSolutions)) * (double)(100)) << "% of all the solutions of length " << MinimumSolutionLength[InternalStateInitialValue] << ")" << endl << endl;

    cout << "A listing of them has been saved inside \"" << FileNameAllSolutionsCSV << "\" and \"" << FileNameSafeSolutionsCSV << "\", respectively." << endl;

    // Memory deallocation.

    _DeallocateAllThatNeedsToBeDeallocated();

    return 0;
}
