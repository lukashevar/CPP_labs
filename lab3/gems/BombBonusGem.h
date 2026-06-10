#pragma once

#include "Gem.h"

class BombBonusGem : public Gem {
public:
	BombBonusGem(GemColor color)
		: Gem(color) {}

	bool isBonus() const override { return true; }

	void activate(
		Board& board,
		AnimationManager& animations,
		int row,
		int col
	) override;
};
