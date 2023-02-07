#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "grid.hpp"

class Solver
{
public:
    Solver(Grid &grid);
    bool solve();

private:
    bool equalColors(int row, int col);
    bool threeInSequence(int row, int col);
    bool uniqueVector(int row, int col);
    bool valid(int row, int col);
    Grid &grid;
    unsigned int size;
};

#endif