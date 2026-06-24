#pragma once

#include "bonuses/Bonus.h"

class RandomDirectionBonus : public Bonus {
public:
    RandomDirectionBonus(const sf::Vector2f& position);
    BonusEffect getEffect() const override { return BonusEffect::RandomDirection; }
};
