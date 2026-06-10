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
};
