#pragma once

#include "bonuses/Bonus.h"

class BottomBarrierBonus : public Bonus {
public:
	BottomBarrierBonus(const sf::Vector2f& position);

	BonusEffect getEffect() const override { return BonusEffect::BottomBarrier; }
};
