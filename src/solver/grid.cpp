#include "grid.hpp"

#include <cmath>
#include <vector>

Grid::Grid(std::vector<std::vector<Cell>> &grid) : m_grid(grid), m_size(grid.size())
{
    m_countsInRow.resize(3, std::vector<unsigned int>(m_size));
    m_countsInCol.resize(3, std::vector<unsigned int>(m_size));

    // Count cell types in each row and column
    Cell cell;
    for (unsigned int row = 0; row < m_size; row++)
    {
        for (unsigned int col = 0; col < m_size; col++)
        {
            cell = m_grid[row][col];
            m_countsInRow[cell][row]++;
            m_countsInCol[cell][col]++;
        }
    }
}

const std::vector<Cell> &Grid::rowAt(int row) const
{
    return m_grid[row];
}

Cell Grid::cellAt(int row, int col) const
{
    return m_grid[row][col];
}

void Grid::cellAt(int row, int col, Cell newCell)
{
    // Decrement count of old value and increment count of new value
    Cell currCell = m_grid[row][col];
    m_countsInRow[currCell][row]--;
    m_countsInCol[currCell][col]--;

    m_grid[row][col] = newCell;
    m_countsInRow[newCell][row]++;
    m_countsInCol[newCell][col]++;
}

unsigned int Grid::size()
{
    return m_size;
}

unsigned int Grid::countsInRow(int row, Cell cell)
{
    return m_countsInRow[cell][row];
}

unsigned int Grid::countsInCol(int col, Cell cell)
{
    return m_countsInCol[cell][col];
}

// Helper function to create a grid vector from a string
std::vector<std::vector<Cell>> stringToVector(const std::string &strGrid, char chPrimary, char chSecondary)
{
    unsigned int size = std::sqrt(strGrid.length());
    std::vector<std::vector<Cell>> grid(size, std::vector<Cell>(size));

    Cell cell;
    char chCell;
    for (unsigned int row = 0; row < size; row++)
    {
        for (unsigned int col = 0; col < size; col++)
        {
            chCell = strGrid[row * size + col];

            if (chCell == chPrimary)
            {
                cell = primary;
            }
            else if (chCell == chSecondary)
            {
                cell = secondary;
            }
            else
            {
                cell = empty;
            }

            grid[row][col] = cell;
        }
    }

    return grid;
}

// Helper function to create a grid string from a vector
std::string vectorToString(const std::vector<std::vector<Cell>> &vGrid, char chPrimary, char chSecondary, char chEmpty)
{
    unsigned int size = vGrid.size();
    std::string strGrid(size * size, chEmpty);

    Cell cell;
    char chCell;
    for (unsigned int i = 0; i < size * size; i++)
    {
        cell = vGrid[i / size][i % size];

        if (cell == primary)
        {
            chCell = chPrimary;
        }
        else if (cell == secondary)
        {
            chCell = chSecondary;
        }
        else
        {
            chCell = chEmpty;
        }

        strGrid[i] = chCell;
    }

    return strGrid;
}