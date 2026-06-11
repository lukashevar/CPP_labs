#include "BoardProcessor.h"
#include "MatchFinder.h"
#include "BonusSystem.h"
#include "GemFactory.h"
#include "Gem.h"



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

            if (cell.isMarkedForDestroy() && !cell.isEmpty())
            {
                Gem* gem = cell.getGem();
                
                if (gem->isBonus())
                {
                    gem->activate(board, animations, row, col);
                }
                else
                {
                    BonusSystem::trySpawnBonus(
                        board, animations, row, col, gem->getColor()
                    );
                }

                cell.setGem(nullptr);
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
                    board.getCell(writeRow, col).setGem(
                        std::move(current.takeGem())
                    );
                }

                --writeRow;
            }
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
                GemColor color = board.generateRandomColor();

                

                cell.setGem(GemFactory::createRandom(color));
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
                        cell.getGem()->getColor()
                    });
                }

                --writeRow;
            }
        }
    }

    return moves;
}
