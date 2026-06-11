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
    GemColor color = m_color; 

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
        color,                                        
        BoardRenderer::celltoPixel(fromRow, centerCol),
        BoardRenderer::celltoPixel(centerRow, centerCol),
        0.5f
    );
    anim.setRow(centerRow);
    anim.setCol(centerCol);
    animations.add(anim);

    Cell& center = board.getCell(centerRow, centerCol);
    center.setGem(GemFactory::createRandom(color));   
    center.dismarkForDestroy();                        

    for (int i = 0; i < 2 && !candidates.empty(); ++i) {
        int idx = rand() % candidates.size();
        int row = candidates[idx].first;
        int col = candidates[idx].second;
        Cell& cell = board.getCell(row, col);
        cell.setGem(GemFactory::createRandom(color)); 
        cell.dismarkForDestroy();
        candidates.erase(candidates.begin() + idx);
    }
}
