#include "bonuses/BallSpeedBonus.h"


BallSpeedBonus::BallSpeedBonus(
    const sf::Vector2f& position)
    : Bonus(position)
{
    shape.setFillColor(sf::Color::Magenta);
}
