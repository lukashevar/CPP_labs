#include "bonuses/StickyBonus.h"

StickyBonus::StickyBonus(
    const sf::Vector2f& position)
    : Bonus(position)
{
    shape.setFillColor(sf::Color::Blue);
}
