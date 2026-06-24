#pragma once

#include "bonuses/Bonus.h"

class StickyBonus : public Bonus
{
public:
    StickyBonus(const sf::Vector2f& position);

    BonusEffect getEffect() const override { return BonusEffect::Sticky; }
};
