#include "blocks/Block.h"

Block::Block(
    const sf::Vector2f& position,
    const sf::Vector2f& size,
    const sf::Color& color)
    : destroyed(false)
{
    shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(color);
}

void Block::onHit(Ball& ball)
{
    destroyed = true;
}

bool Block::isDestroyed() const
{
    return destroyed;
}

void Block::render(sf::RenderWindow& window)
{
    if (!destroyed)
        window.draw(shape);
}

sf::FloatRect Block::getBounds() const
{
    return shape.getGlobalBounds();
}