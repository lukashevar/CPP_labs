#pragma once

#include "Board.h"

class BonusSystem {
public:
	static void trySpawnBonus(
		Board& board,
		int row,
		int col,
		GemColor sourceColor
	);

private:
	static void applyRecolorBonus(
		Board& board,
		int centerRow,
		int centerCol,
		GemColor color
	);

	static void applyBombBonus(
		Board& board,
		int centerRow,
		int centerCol
	);
};
