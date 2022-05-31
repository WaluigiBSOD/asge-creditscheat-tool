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

/// @file ComputeMinimumSolutionLengths.cpp
///
/// @brief Functions for computing minimum solution lengths, regardless of the initial internal state.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license

#include "Constants.h"

/// This is the main logic behind the method that computes all the minimum solution lenghts.
///
/// @param[in] InternalState       The starting internal state.
/// @param[in] TargetInternalState The internal state to obtain by altering the *InternalState* variable, through button presses.
///
/// @return **True** if a button out of all the possible seven yields *TargetInternalState* by having *InternalState* as an input, **false** otherwise.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
bool _FindMinimumSolutionLength(unsigned short InternalState, unsigned short TargetInternalState) {
    unsigned short TestInternalState;

    for (unsigned int i=0;i<7;i++) {
        TestInternalState = RainbowTable[i][InternalState];

        if (TestInternalState == TargetInternalState)
            return true;
    }

    return false;
}

/// This method computes all the minimum solution lenghts.
///
/// It's done in various steps, iteratively with no lengthy recursive searches.
///
/// @author    WaluigiBSOD
/// @copyright GPL-3.0 license
void _ComputeMinimumSolutionLengths() {
    unsigned short SolutionSize = 0;

    bool AtLeastSomethingWasComputed;

    unsigned int i,j;

    do {
        // Step #1 - Computing all the solutions of a certain size at the same time, to maximize caching effectiveness.

        AtLeastSomethingWasComputed = false;

        for (i=0;i<0x10000;i++)
            if (MinimumSolutionLength[i] == 0) {
                AtLeastSomethingWasComputed = true;

                // Step #2 - Checks if yields a solution of the given length.

                if (SolutionSize == 0) {
                    // Step #3a - Solutions of length = 1.
                    //
                    // At first, trivial solutions have to be computed.
                    // Are the base case of what is done regarding ones of length > 1.

                    if (_FindMinimumSolutionLength(i,InternalStateTargetValue))
                        MinimumSolutionLength[i] = 1;
                } else {
                    // Step #3b - Solutions of length > 1.
                    //
                    // Solutions of length > 1 are computed by finding solutions of length n - 1 and extending them by 1.
                    // Simple as that.
                    // If a solution requires n steps, there always exist solutions of length n - 1, n - 2 and so on derived from it.

                    for (j=0;j<0x10000;j++)
                        if (MinimumSolutionLength[j] == SolutionSize && _FindMinimumSolutionLength(i,j)) {
                            MinimumSolutionLength[i] = MinimumSolutionLength[j] + 1;

                            break;
                        }
                }
            }

        SolutionSize++;
    } while (AtLeastSomethingWasComputed);
}
