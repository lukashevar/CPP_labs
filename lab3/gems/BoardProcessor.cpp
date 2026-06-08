#include "BoardProcessor.h"
#include "MatchFinder.h"
#include "BonusSystem.h"



int BoardProcessor::destroyMarkedCells(
    Board& board,
    AnimationManager& animations
)
{
    int destroyed = 0;

    for (int row = 0; row < board.getRows(); ++row)
    {
        for (int col = 0; col < board.getCols(); ++col)
        {
            Cell& cell = board.getCell(row, col);

            if (cell.isMarkedForDestroy())
            {
                BonusSystem::trySpawnBonus(
                    board,
                    animations,
                    row,
                    col,
                    cell.getColor()
                );

                cell.setColor(GemColor::Black);

                cell.markForDestroy();

                destroyed++;
            }
        }
    }

    return destroyed * 10;
}


void BoardProcessor::collapseColumns(Board& board)
{
    for (int col = 0; col < board.getCols(); ++col)
    {
        int writeRow = board.getRows() - 1;

        for (int row = board.getRows() - 1; row >= 0; --row)
        {
            Cell& current = board.getCell(row, col);

            if (!current.isEmpty())
            {
                if (row != writeRow)
                {
                    board.getCell(writeRow, col) = current;

                    current.setColor(GemColor::Black);
                    current.markForDestroy();
                }

                --writeRow;
            }
        }

        
        for (int row = writeRow; row >= 0; --row)
        {
            Cell& cell = board.getCell(row, col);
            cell.setColor(GemColor::Black);
            cell.markForDestroy();
        }
    }
}


void BoardProcessor::fillEmptyCells(Board& board)
{
    for (int row = 0; row < board.getRows(); ++row)
    {
        for (int col = 0; col < board.getCols(); ++col)
        {
            Cell& cell = board.getCell(row, col);

            if (cell.isEmpty())
            {
                cell.setColor(board.generateRandomColor());
                cell.dismarkForDestroy();
            }
        }
    }
}


void BoardProcessor::process(Board& board, AnimationManager& animations)
{
    
    while (MatchFinder::findMatches(board))
    {
        destroyMarkedCells(board, animations);
        collapseColumns(board);
        fillEmptyCells(board);
    }

    
    MatchFinder::findMatches(board);
}

std::vector<FallMove> BoardProcessor::collectFallMoves(Board& board) {
    std::vector<FallMove> moves;

    for (int col = 0; col < board.getCols(); ++col) {
        int writeRow = board.getRows() - 1;

        for (int row = board.getRows() - 1; row >= 0; --row) {
            Cell& cell = board.getCell(row, col);

            if (!cell.isEmpty()) {
                if (row != writeRow) {
                    moves.push_back({
                        row,
                        col,
                        writeRow,
                        col,
                        cell.getColor()
                    });
                }

                --writeRow;
            }
        }
    }

    return moves;
}
