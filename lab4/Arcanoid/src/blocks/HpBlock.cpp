#include "blocks/HpBlock.h"

HpBlock::HpBlock(
    const sf::Vector2f& position,
    const sf::Vector2f& size)
    : Block(position, size, sf::Color::Yellow),
    hp(3)
{
}

void HpBlock::onHit(Ball&)
{
    hp--;

    if (hp <= 0)
    {
        destroyed = true;
    }
}