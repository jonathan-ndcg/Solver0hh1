#include "solver.hpp"

#include "grid.hpp"

Solver::Solver(Grid &grid) : grid(grid), size(grid.size()) {}

// Solve the grid with backtracking algorithm
bool Solver::solve()
{
    for (unsigned int row = 0; row < size; row++)
    {
        for (unsigned int col = 0; col < size; col++)
        {
            // Look for first empty cell
            if (grid.cellAt(row, col) != empty)
            {
                continue;
            }

            // Solve recursively if cell is valid
            grid.cellAt(row, col, primary);
            if (valid(row, col) && solve())
            {
                return true;
            }

            grid.cellAt(row, col, secondary);
            if (valid(row, col) && solve())
            {
                return true;
            }

            grid.cellAt(row, col, empty);
            return false;
        }
    }

    return true;
}

// Validates condition of same amount of each color in row and col
bool Solver::equalColors(int row, int col)
{
    unsigned int half = size / 2;

    if (grid.countsInRow(row, primary) > half || grid.countsInRow(row, secondary) > half)
    {
        return false;
    }

    if (grid.countsInCol(col, primary) > half || grid.countsInCol(col, secondary) > half)
    {
        return false;
    }

    return true;
}

// Validates condition of three of the same color next to each other
bool Solver::threeInSequence(int row, int col)
{
    // Check for sequence in row
    if (row - 2 >= 0 &&
        grid.cellAt(row - 2, col) == grid.cellAt(row - 1, col) &&
        grid.cellAt(row - 1, col) == grid.cellAt(row, col))
    {
        return false;
    }

    if (row - 1 >= 0 && row + 1 < size &&
        grid.cellAt(row - 1, col) == grid.cellAt(row, col) &&
        grid.cellAt(row, col) == grid.cellAt(row + 1, col))
    {
        return false;
    }

    if (row + 2 < size &&
        grid.cellAt(row, col) == grid.cellAt(row + 1, col) &&
        grid.cellAt(row + 1, col) == grid.cellAt(row + 2, col))
    {
        return false;
    }

    // Check for sequence in column
    if (col - 2 >= 0 &&
        grid.cellAt(row, col - 2) == grid.cellAt(row, col - 1) &&
        grid.cellAt(row, col - 1) == grid.cellAt(row, col))
    {
        return false;
    }

    if (col - 1 >= 0 && col + 1 < size &&
        grid.cellAt(row, col - 1) == grid.cellAt(row, col) &&
        grid.cellAt(row, col) == grid.cellAt(row, col + 1))
    {
        return false;
    }

    if (col + 2 < size &&
        grid.cellAt(row, col) == grid.cellAt(row, col + 1) &&
        grid.cellAt(row, col + 1) == grid.cellAt(row, col + 2))
    {
        return false;
    }

    return true;
}

// Validates condition of no two rows and no two columns being the same
bool Solver::uniqueVector(int row, int col)
{
    if (grid.countsInRow(row, empty) == 0) // Compare only complete rows
    {
        for (unsigned int r = 0; r < size; r++)
        {
            if (row == r || grid.countsInRow(r, empty) > 0)
            {
                continue;
            }

            if (grid.rowAt(row) == grid.rowAt(r))
            {
                return false;
            }
        }
    }
    
    if (grid.countsInCol(col, empty) == 0) // Compare only complete columns
    {
        for (unsigned int c = 0; c < size; c++)
        {
            if (col == c || grid.countsInCol(c, empty) > 0)
            {
                continue;
            }

            bool diffFoundIncol = false;
            for (unsigned int r = 0; r < size; r++)
            {
                if (grid.cellAt(r, col) != grid.cellAt(r, c))
                {
                    diffFoundIncol = true;
                    break;
                }
            }

            if (!diffFoundIncol)
            {
                return false;
            }
        }
    }

    return true;
}

// Validates all conditions
bool Solver::valid(int row, int col)
{
    return equalColors(row, col) && threeInSequence(row, col) && uniqueVector(row, col);
}