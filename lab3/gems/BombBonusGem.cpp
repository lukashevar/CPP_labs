#include "BombBonusGem.h"

#include "Board.h"
#include "AnimationManager.h"
#include "BoardRenderer.h"

void BombBonusGem::activate(
    Board& board,
    AnimationManager& animations,
    int row,
    int col
)
{
    for (int i = 0; i < 4; ++i)
    {
        int randomRow = rand() % board.getRows();
        int randomCol = rand() % board.getCols();

        Cell& cell = board.getCell(randomRow, randomCol);

        if (cell.isEmpty())
            continue;

        GemColor color = cell.getGem()->getColor();
        cell.setGem(nullptr);

        Animation anim(
            AnimationType::BombBonus,
            color,
            BoardRenderer::celltoPixel(randomRow, randomCol),
            BoardRenderer::celltoPixel(randomRow, randomCol),
            0.5f
        );
        anim.setRow(randomRow);
        anim.setCol(randomCol);
        animations.add(anim);
    }
}
