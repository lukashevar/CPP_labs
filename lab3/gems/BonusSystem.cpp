#include "BonusSystem.h"
#include "BoardRenderer.h"


#include <random>
#include <vector>

void BonusSystem::trySpawnBonus(
    Board& board,
    AnimationManager& animations,
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
            animations,
            row,
            col,
            sourceColor
        );
    }
    else
    {
        applyBombBonus(
            board,
            animations,
            row,
            col
        );
    }
}


void BonusSystem::applyRecolorBonus(
    Board& board,
    AnimationManager& animations,
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

            if (dr <= 3 && dc <= 3 && (dr + dc > 1))
            {
                candidates.push_back({ row, col });
            }
        }
    }

    if (candidates.empty())
        return;

    Animation anim(
        AnimationType::RecolorBonus,
        color,
        BoardRenderer::celltoPixel(centerRow - 1, centerCol),
        BoardRenderer::celltoPixel(centerRow, centerCol),
        0.5f
    );

    anim.setRow(centerRow);
    anim.setCol(centerCol);

    animations.add(anim);

    for (int i = 0; i < 2 && !candidates.empty(); ++i)
    {
        int idx = rand() % candidates.size();

        int row = candidates[idx].first;
        int col = candidates[idx].second;

        board.getCell(row, col).setColor(color);
    }
}

void BonusSystem::applyBombBonus(
    Board& board,
    AnimationManager& animations,
    int centerRow,
    int centerCol
)
{
   
    board.getCell(centerRow, centerCol).markForDestroy();

    for (int i = 0; i < 4; ++i)
    {
        int row = rand() % board.getRows();
        int col = rand() % board.getCols();

        Animation anim(
            AnimationType::BombBonus,
            GemColor::Yellow,
            BoardRenderer::celltoPixel(row, col),
            BoardRenderer::celltoPixel(row, col),
            0.5f
        );

        anim.setRow(row);
        anim.setCol(col);

        animations.add(anim);
    }
}
