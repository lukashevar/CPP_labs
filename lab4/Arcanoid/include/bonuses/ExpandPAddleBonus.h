#pragma once

#include "bonuses/Bonus.h"

class ExpandPaddleBonus : public Bonus {
public:
	ExpandPaddleBonus(const sf::Vector2f& position);

	BonusEffect getEffect() const override { return BonusEffect::ExpandPaddle; }
};
