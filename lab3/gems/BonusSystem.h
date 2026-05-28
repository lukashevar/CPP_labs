#pragma once

#include "Board.h"
#include "AnimationManager.h"

class BonusSystem {
public:
	static void trySpawnBonus(
		Board& board,
		AnimationManager& animations,
		int row,
		int col,
		GemColor sourceColor
	);

private:
	static void applyRecolorBonus(
		Board& board,
		AnimationManager& animations,
		int centerRow,
		int centerCol,
		GemColor color
	);

	static void applyBombBonus(
		Board& board,
		AnimationManager& animations,
		int centerRow,
		int centerCol
	);
};
