#include "Board.h"
#include "GemFactory.h"
#include <stdexcept>
#include <random>

Board::Board(int rows, int cols)
    : m_rows(rows), m_cols(cols)
{
    m_cells.resize(m_rows);
    for (auto& row : m_cells)
        row.resize(m_cols); 
    initialize();
}

GemColor Board::getRandomColor() const {
    static std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 3); 
    GemColor color = static_cast<GemColor>(dist(engine));
    return color;
}

void Board::initialize() {
    for (int r = 0; r < m_rows; ++r) {
        for (int c = 0; c < m_cols; ++c) {
            GemColor color = getRandomColor();
            m_cells[r][c].setGem(GemFactory::createRandom(color));
            m_cells[r][c].dismarkForDestroy();
        }
    }
}

bool Board::isValidPosition(int row, int col) const {
    return row >= 0 && row < m_rows &&
        col >= 0 && col < m_cols;
}

bool Board::areAdjacent(int row1, int col1, int row2, int col2) const {
    int dr = std::abs(row1 - row2);
    int dc = std::abs(col1 - col2);
    return (dr + dc == 1);
}

void Board::swapCells(int row1, int col1, int row2, int col2) {
    if (!isValidPosition(row1, col1) || !isValidPosition(row2, col2))
        return;
    std::swap(m_cells[row1][col1], m_cells[row2][col2]);
}

Cell& Board::getCell(int row, int col) {
    if (!isValidPosition(row, col))
        throw std::out_of_range("Invalid cell position");
    return m_cells[row][col];
}

const Cell& Board::getCell(int row, int col) const {
    if (!isValidPosition(row, col))
        throw std::out_of_range("Invalid cell position");
    return m_cells[row][col];
}

int Board::getRows() const { return m_rows; }
int Board::getCols() const { return m_cols; }

GemColor Board::generateRandomColor() const {
    return getRandomColor();
}
