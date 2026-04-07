# Alien Storm (Genesis) Credits Select Cheat Tool

A command-line tool that computes some stuff regarding [the Genesis Alien Storm game's credits select cheat](https://tcrf.net/Alien_Storm_(Genesis)#Credits_Select).

## Program

More documentation can be found [here](https://waluigibsod.github.io/asge-creditscheat-tool), generated with [Doxygen](https://github.com/doxygen/doxygen) from the source code and an additional file for the main page.

### How To Compile It

A handy [`CMakeLists.txt`](https://github.com/WaluigiBSOD/asge-creditscheat-tool/blob/master/src/CMakeLists.txt) file is provided inside the [`src`](https://github.com/WaluigiBSOD/asge-creditscheat-tool/tree/master/src) directory for easy compilation, overall the only particular requirement it needs is the ISO C++11 standard.

### Output

The program outputs four CSV files, located inside the [`output`](https://github.com/WaluigiBSOD/asge-creditscheat-tool/tree/master/output) directory:

* [`all_solutions.csv`](https://github.com/WaluigiBSOD/asge-creditscheat-tool/blob/master/output/all_solutions.csv), containing all the solutions of length 9
* [`all_solutions_prune.csv`](https://github.com/WaluigiBSOD/asge-creditscheat-tool/blob/master/output/all_solutions_prune.csv), containing all the algorithm's prune tables related to all the solutions of length 9
* [`safe_solutions.csv`](https://github.com/WaluigiBSOD/asge-creditscheat-tool/blob/master/output/safe_solutions.csv), containing all the *safe* solutions of length 9
* [`safe_solutions_prune.csv`](https://github.com/WaluigiBSOD/asge-creditscheat-tool/blob/master/output/safe_solutions_prune.csv), containing all the algorithm's prune tables related to all the *safe* solutions of length 9

Console output contains other information, like the number of solutions.

## License

This source code is released under the GNU General Public License v 3.0 (see [`LICENSE`](https://github.com/WaluigiBSOD/asge-creditscheat-tool/blob/master/LICENSE) in the root of the repository for a copy of the license and for more information).