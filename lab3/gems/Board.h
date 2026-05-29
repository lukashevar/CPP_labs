#pragma once
#include <SFML/Graphics.hpp>

#include <vector>
#include "Cell.h"

class Board {
public:
	Board(int rows, int cols);

	void initialize();

	bool isValidPosition(int row, int col) const;
	bool areAdjacent(int row1, int col1, int row2, int col2) const;
	void swapCells(int row1, int col1, int row2, int col2);

	void draw(sf::RenderWindow& window) const;

	Cell& getCell(int row, int col);
	const Cell& getCell(int row, int col) const;

	int getRows() const;
	int getCols() const;

	GemColor generateRandomColor() const;

private:
	GemColor getRandomColor() const;
	int m_rows;
	int m_cols;
	std::vector<std::vector<Cell>> m_cells;
};
