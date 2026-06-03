#pragma once

#include "bonuses/Bonus.h"

class BallSpeedBonus : public Bonus
{
public:
    BallSpeedBonus(const sf::Vector2f& position);

    void apply(Paddle& paddle, Ball& ball) override;
};