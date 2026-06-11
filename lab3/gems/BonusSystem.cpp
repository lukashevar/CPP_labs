#include "BonusSystem.h"
#include "BoardRenderer.h"
#include "GemFactory.h"


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
    if (rand() % 100 > 20)
        return;

    const int dr[] = { -1, 1, 0, 0 };
    const int dc[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; ++i)
    {
        int nr = row + dr[i];
        int nc = col + dc[i];

        if (!board.isValidPosition(nr, nc))
            continue;

        Cell& neighbor = board.getCell(nr, nc);

        if (!neighbor.isEmpty() && !neighbor.isMarkedForDestroy())
        {
            neighbor.setGem(GemFactory::createBonus(sourceColor));
            return;
        }
    }
}
