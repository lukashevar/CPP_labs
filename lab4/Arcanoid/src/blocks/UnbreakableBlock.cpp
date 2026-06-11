#include "blocks/UnbreakableBlock.h"

UnbreakableBlock::UnbreakableBlock(
    const sf::Vector2f& position,
    const sf::Vector2f& size)
    : Block(position, size, sf::Color::Red)
{
}

void UnbreakableBlock::onHit(Ball&)
{
}
