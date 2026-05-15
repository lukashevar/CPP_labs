#pragma once

class Board;


class BoardProcessor {
public:
	static void destroyMarkedCells(Board& board);
	static void collapseColumns(Board& board);
	static void fillEmptyCells(Board& board);
	static void process(Board& board);
};