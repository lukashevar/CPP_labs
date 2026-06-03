#include "bonuses/BallSpeedBonus.h"

#include "entities/Ball.h"

BallSpeedBonus::BallSpeedBonus(
    const sf::Vector2f& position)
    : Bonus(position)
{
    shape.setFillColor(sf::Color::Red);
}

void BallSpeedBonus::apply(
    Paddle&,
    Ball& ball)
{
    ball.applySpeedBoost(1.5f, 5.f);
}