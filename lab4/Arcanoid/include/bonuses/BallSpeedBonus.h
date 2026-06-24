#pragma once

#include "bonuses/Bonus.h"

class BallSpeedBonus : public Bonus
{
public:
    BallSpeedBonus(const sf::Vector2f& position);

    BonusEffect getEffect() const override { return BonusEffect::SpeedBoost; }
};
