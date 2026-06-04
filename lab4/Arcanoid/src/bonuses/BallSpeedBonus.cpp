#include "bonuses/BallSpeedBonus.h"

#include "entities/Ball.h"

BallSpeedBonus::BallSpeedBonus(
    const sf::Vector2f& position)
    : Bonus(position)
{
    shape.setFillColor(sf::Color::Red);
}

