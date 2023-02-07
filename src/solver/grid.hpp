#ifndef GRID_HPP
#define GRID_HPP

#include <string>
#include <vector>

enum Cell
{
    empty,
    primary,
    secondary
};

class Grid
{
public:
    Grid(std::vector<std::vector<Cell>> &grid);
    const std::vector<Cell> &rowAt(int row) const;
    Cell cellAt(int row, int col) const;
    void cellAt(int row, int col, Cell newCell);
    unsigned int size();
    unsigned int countsInRow(int row, Cell cell);
    unsigned int countsInCol(int col, Cell cell);

private:
    std::vector<std::vector<Cell>> &m_grid;
    unsigned int m_size;
    std::vector<std::vector<unsigned int>> m_countsInRow;
    std::vector<std::vector<unsigned int>> m_countsInCol;
};

std::vector<std::vector<Cell>> stringToVector(const std::string &strGrid, char chPrimary, char chSecondary);

std::string vectorToString(const std::vector<std::vector<Cell>> &vGrid, char chPrimary, char chSecondary, char chEmpty);

#endif