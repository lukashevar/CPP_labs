#include "bonuses/RandomDirectionBonus.h"

RandomDirectionBonus::RandomDirectionBonus(const sf::Vector2f& position)
    : Bonus(position)
{
    shape.setFillColor(sf::Color::Yellow);
}
