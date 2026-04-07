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

/// @file      main.cpp
///
/// @brief     Main program file.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 License

#include <cmath>
#include <iostream>
#include <iomanip>

#include "Constants.h"

#include "PrintSplashScreen.h"

#include "ComputeRainbowTable.h"
#include "ComputePruneTables.h"
#include "ComputeMinimumSolutionLengths.h"
#include "ComputeSolutions.h"

/// Allocates all the arrays that are put inside the heap.
///
/// It's done to avoid memory allocation issues, as in total they weight 64 KB.
/// May sound exaggerate, but usually default stack sizes are limited to a few megabytes.
/// Also, this is approximately 420 times the RAM that is needed for the internal state of a MT19937 PRNG algorithm instance, as a comparison.
///
/// @return    **True** if all memory needed is allocated and initialized succesfully, **false** otherwise.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 License

bool _InitializeAllThatNeedsToBeInitialized() {
    int i;

    // Rainbow Table

    RainbowTable = new unsigned short*[7];

    if (RainbowTable == nullptr)
        return false;

    for (i=0;i<7;i++) {
        RainbowTable[i] = new unsigned short[0x10000];

        if (RainbowTable[i] == nullptr) {
            i--;

            while (i > -1) {
                delete[] RainbowTable[i];

                i--;
            }

            return false;
        }
    }

    // Minimum Solution Length

    MinimumSolutionLength = new unsigned short[0x10000];

    if (MinimumSolutionLength == nullptr)
        return false;

    for (i=0;i<0x10000;i++)
        MinimumSolutionLength[i] = 0;

    return true;
}

/// Deallocates all the arrays that are put inside the heap.
///
/// It's called at the end of the program, just before exiting.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 License

void _DeallocateAllThatNeedsToBeDeallocated() {
    // Rainbow Table

    for (unsigned char i=0;i<0x7;i++)
        delete[] RainbowTable[i];

    delete[] RainbowTable;

    // Minimum Solution Length

    delete[] MinimumSolutionLength;
}

/// The main program function.
///
/// Handles all the console output, calling functions and memory allocation/initializing/deallocation.
///
/// @return    The program's exit code (0 if everything was OK, different if otherwise).
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 License

int main() {
    // Splash Screen

    _PrintSplashScreen();

    // Memory allocation and initialization

    if (_InitializeAllThatNeedsToBeInitialized()) {
        long long NumberOfAllSolutions;
        long long NumberOfSafeSolutions;

        // Caching

        cout << " ### Caching ###" << endl << endl;

        // Rainbow Table computation

        cout << "Caching algorithm into a rainbow table ... ";

        _ComputeRainbowTable();

        cout << "Done!" << endl;

        // Minimum solution lengths computation

        cout << "Caching minimum solution lengths (may take a minute or two) ... ";

        _ComputeMinimumSolutionLengths();

        cout << "Done!" << endl << endl;

        // Prune tables computation

        cout << " ### Prune Tables ###" << endl << endl;

        cout << "Computing prune table (all solutions) ";

        if ((InternalStateInitialValue != 0x0000) || (InternalStateTargetValue != 0x3929))
            cout << "(may take a bit longer than usual for non-standard intial/target values) ";

        cout << "... ";

        if(_ComputePruneTables(false))
            cout << "Done!" << endl;
        else {
            cout << "Error! Program will be closed." << endl << endl;

            return FileErrorAllSolutionsCSV;
        }

        cout << "Computing prune table (safe solutions) ";

        if ((InternalStateInitialValue != 0x0000) || (InternalStateTargetValue != 0x3929))
            cout << "(may take a bit longer than usual for non-standard intial/target values) ";

        cout << "... ";

        if(_ComputePruneTables(true))
            cout << "Done!" << endl << endl;
        else {
            cout << "Error! Program will be closed." << endl << endl;

            return FileErrorSafeSolutionsCSV;
        }

        cout << "A listing of them has been saved inside \"" << FileNameAllSolutionsPruneTablesCSV << "\" and \"" << FileNameSafeSolutionsPruneTablesCSV << "\", respectively." << endl << endl;

        // Computation of all/safe minimum length solutions

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

        cout << "Computing solutions (all solutions) ... ";

        NumberOfAllSolutions = _ComputeSolutions(false);

        if(NumberOfAllSolutions > -1)
            cout << "Done!" << endl;
        else {
            cout << "Error! Program will be closed." << endl << endl;

            return FileErrorAllSolutionsCSV;
        }

        cout << "Computing solutions (safe solutions) ... ";

        NumberOfSafeSolutions = _ComputeSolutions(true);

        if(NumberOfSafeSolutions > -1)
            cout << "Done!" << endl << endl;
        else {
            cout << "Error! Program will be closed." << endl << endl;

            return FileErrorSafeSolutionsCSV;
        }

        cout << "Done!" << endl << endl;

        cout << "All:  " << setw(5) << setfill(' ') << NumberOfAllSolutions << " (" << (((double)(NumberOfSafeSolutions) / (double)(pow(7,MinimumSolutionLength[InternalStateInitialValue]))) * (double)(100)) << "% of all the possible button combinations of length " << MinimumSolutionLength[InternalStateInitialValue] << ")" << endl;

        cout << "Safe: " << setw(5) << setfill(' ') << NumberOfSafeSolutions << " (" << (((double)(NumberOfSafeSolutions) / (double)(NumberOfAllSolutions)) * (double)(100)) << "% of all the solutions of length " << MinimumSolutionLength[InternalStateInitialValue] << ")" << endl << endl;

        cout << "A listing of them has been saved inside \"" << FileNameAllSolutionsCSV << "\" and \"" << FileNameSafeSolutionsCSV << "\", respectively." << endl << endl;

        // Memory deallocation

        _DeallocateAllThatNeedsToBeDeallocated();
    } else {
        cout << "Memory allocation error! Program will be closed." << endl << endl;

        return RainbowTableMemoryAllocationError;
    }

    return 0;
}
