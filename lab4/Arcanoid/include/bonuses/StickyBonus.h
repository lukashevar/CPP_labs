#pragma once

#include "bonuses/Bonus.h"

class StickyBonus : public Bonus
{
public:
    StickyBonus(const sf::Vector2f& position);

    void apply(Paddle& paddle, Ball& ball) override;
};