#include "MatchFinder.h"
#include "Gem.h"

void MatchFinder::clearMarks(Board& board) {
    for (int r = 0; r < board.getRows(); ++r)
        for (int c = 0; c < board.getCols(); ++c)
            board.getCell(r, c).dismarkForDestroy();
}

bool MatchFinder::findMatches(Board& board) {
    clearMarks(board);
    bool h = findHorizontalMatches(board);
    bool v = findVerticalMatches(board);
    return h || v;
}

bool MatchFinder::findHorizontalMatches(Board& board) {
    bool found = false;
    for (int row = 0; row < board.getRows(); ++row) {
        int startCol = 0;
        while (startCol < board.getCols()) {
            const Cell& startCell = board.getCell(row, startCol);
            if (startCell.isEmpty()) { ++startCol; continue; }

            GemColor color = startCell.getGem()->getColor();
            int endCol = startCol;

            while (endCol < board.getCols()) {
                const Cell& c = board.getCell(row, endCol);
                if (c.isEmpty() || c.getGem()->getColor() != color) break;
                ++endCol;
            }

            if (endCol - startCol >= 3) {
                found = true;
                for (int col = startCol; col < endCol; ++col)
                    board.getCell(row, col).markForDestroy();
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
            if (startCell.isEmpty()) { ++startRow; continue; }

            GemColor color = startCell.getGem()->getColor();
            int endRow = startRow;

            while (endRow < board.getRows()) {
                const Cell& c = board.getCell(endRow, col);
                if (c.isEmpty() || c.getGem()->getColor() != color) break;
                ++endRow;
            }

            if (endRow - startRow >= 3) {
                found = true;
                for (int row = startRow; row < endRow; ++row)
                    board.getCell(row, col).markForDestroy();
            }
            startRow = endRow;
        }
    }
    return found;
}