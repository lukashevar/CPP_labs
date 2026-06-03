#pragma once

#include "bonuses/Bonus.h"

class ExpandPaddleBonus : public Bonus {
public:
	ExpandPaddleBonus(const sf::Vector2f& position);

	void apply(Paddle& paddle, Ball& ball) override;
};
