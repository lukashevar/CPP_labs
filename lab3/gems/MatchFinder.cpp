#include "MatchFinder.h"

void MatchFinder::clearMarks(Board& board) {
	for (int r = 0; r < board.getRows(); ++r) {
		for (int c = 0; c < board.getCols(); ++c) {
			board.getCell(r, c).dismarkForDestroy();
		}
	}
}


bool MatchFinder::findMatches(Board& board) {
	clearMarks(board);

	bool foundHorizontal = findHorizontalMatches(board);
	bool foundVertical = findVerticalMatches(board);

	return foundHorizontal || foundVertical;
}


bool MatchFinder::findHorizontalMatches(Board& board) {
	bool found = false;

	for (int row = 0; row < board.getRows(); ++row) {
		int startCol = 0;

		while (startCol < board.getCols()) {
			const Cell& startCell = board.getCell(row, startCol);

			if (startCell.isEmpty()) {
				++startCol;
				continue;
			}

			GemColor color = startCell.getColor();
			int endCol = startCol;

			while (endCol < board.getCols() && board.getCell(row, endCol).getColor() == color) {
				++endCol;
			}

			int mlen = endCol - startCol;

			if (mlen >= 3) {
				found = true;

				for (int col = startCol; col < endCol; ++col) {
					board.getCell(row, col).markForDestroy();
				}
			}

			startCol = endCol;
		}
	}
	return found;
}


bool MatchFinder::findVerticalMatches(Board& board) {
	bool found = false;

	for (int col = 0; col < board.getCols(); ++col) {
		int startRow = 0;

		while (startRow < board.getRows()) {
			const Cell& startCell = board.getCell(startRow, col);

			if (startCell.isEmpty()) {
				++startRow;
				continue;
			}

			GemColor color = startCell.getColor();
			int endRow = startRow;

			while (endRow < board.getRows() && board.getCell(endRow, col).getColor() == color) {
				++endRow;
			}

			int mlen = endRow - startRow;

			if (mlen >= 3) {
				found = true;

				for (int row = startRow; row < endRow; ++row) {
					board.getCell(row, col).markForDestroy();
				}
			}

			startRow = endRow;
		}
	}
	return found;
}
