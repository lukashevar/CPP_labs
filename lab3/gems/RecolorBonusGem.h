#pragma once

#include "Gem.h"

class RecolorBonusGem : public Gem {
public:
	RecolorBonusGem(GemColor color)
		: Gem(color) {}

	bool isBonus() const override { return true; }

	void activate(
		Board& board,
		AnimationManager& animations,
		int row,
		int col
	) override;
};