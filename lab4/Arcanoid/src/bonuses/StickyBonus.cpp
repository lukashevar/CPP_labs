#include "bonuses/StickyBonus.h"

#include "entities/Ball.h"

StickyBonus::StickyBonus(
    const sf::Vector2f& position)
    : Bonus(position)
{
    shape.setFillColor(sf::Color::Magenta);
}

void StickyBonus::apply(
    Paddle&,
    Ball& ball)
{
    ball.enableStickyMode();
}