#include "RecolorBonusGem.h"
#include "Board.h"
#include "AnimationManager.h"
#include "BoardRenderer.h"
#include "GemFactory.h"
#include <vector>
#include <cstdlib>

void RecolorBonusGem::activate(
    Board& board,
    AnimationManager& animations,
    int centerRow,
    int centerCol
) {
    std::vector<std::pair<int, int>> candidates;

    for (int row = 0; row < board.getRows(); ++row) {
        for (int col = 0; col < board.getCols(); ++col) {
            int dr = abs(row - centerRow);
            int dc = abs(col - centerCol);

            if (dr <= 3 && dc <= 3 && (dr + dc > 1))
                candidates.push_back({ row, col });
        }
    }

    if (candidates.empty())
        return;

    int fromRow = std::max(0, centerRow - 1);

    Animation anim(
        AnimationType::RecolorBonus,
        m_color,
        BoardRenderer::celltoPixel(fromRow, centerCol),
        BoardRenderer::celltoPixel(centerRow, centerCol),
        0.5f
    );
    anim.setRow(centerRow);
    anim.setCol(centerCol);
    animations.add(anim);

    for (int i = 0; i < 2 && !candidates.empty(); ++i) {
        int idx = rand() % candidates.size();

        int row = candidates[idx].first;
        int col = candidates[idx].second;

        Cell& cell = board.getCell(row, col);

        if (!cell.isEmpty())
            cell.setGem(GemFactory::createRandom(m_color));

        candidates.erase(candidates.begin() + idx);
    }
}