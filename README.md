# Alien Storm (Genesis) Credits Select Cheat Tool

A command-line tool that computes some stuff regarding [the Genesis Alien Storm game's credits select cheat](https://tcrf.net/Alien_Storm_(Genesis)#Credits_Select).
## License
This source code is released under the GNU General Public License v 3.0 (see LICENSE in the root of the repository for a copy of the license and for more information).

## How to compile

A handy `CMakeLists.txt` file is provided inside the `src` directory for easy compilation.
The only particular requirement it needs is the ISO C++11 standard.

## Outputs

The program itself outputs four CSV files, located inside the `output` directory:
* `all_solutions_prune.csv`, containing all the algorithm's prune tables related to all the soltions of length 9
* `safe_solutions_prune.csv`, containing all the algorithm's prune tables related to all the *safe* soltions of length 9
* `all_solutions.csv`, containing all the solutions of length 9
* `safe_solutions.csv`, containing all the *safe* solutions of length 9

Console output contains other informations, like the number of solutions.

## Other Documentation

Other documentation can be found [here](https://waluigibsod.github.io/asge-creditscheat-tool), generated with Doxygen from the source code and an additional file for the main page.