#include "BonusSystem.h"

#include <random>
#include <vector>

void BonusSystem::trySpawnBonus(
    Board& board,
    int row,
    int col,
    GemColor sourceColor
)
{
    
    int chance = rand() % 100;

    if (chance > 20)
        return;

    int bonusType = rand() % 2;

    if (bonusType == 0)
    {
        applyRecolorBonus(
            board,
            row,
            col,
            sourceColor
        );
    }
    else
    {
        applyBombBonus(
            board,
            row,
            col
        );
    }
}


void BonusSystem::applyRecolorBonus(
    Board& board,
    int centerRow,
    int centerCol,
    GemColor color
)
{
    std::vector<std::pair<int, int>> candidates;

    for (int row = 0; row < board.getRows(); ++row)
    {
        for (int col = 0; col < board.getCols(); ++col)
        {
            int dr = abs(row - centerRow);
            int dc = abs(col - centerCol);

            
            if (dr <= 3 && dc <= 3)
            {
                
                if (dr + dc > 1)
                {
                    candidates.push_back({ row, col });
                }
            }
        }
    }

    if (candidates.empty())
        return;

    
    board.getCell(centerRow, centerCol).color = color;

    
    for (int i = 0; i < 2; ++i)
    {
        int idx = rand() % candidates.size();

        int row = candidates[idx].first;
        int col = candidates[idx].second;

        board.getCell(row, col).color = color;
    }
}


void BonusSystem::applyBombBonus(
    Board& board,
    int centerRow,
    int centerCol
)
{
   
    board.getCell(centerRow, centerCol)
        .markedForDestroy = true;

    for (int i = 0; i < 4; ++i)
    {
        int row = rand() % board.getRows();
        int col = rand() % board.getCols();

        board.getCell(row, col)
            .markedForDestroy = true;
    }
}