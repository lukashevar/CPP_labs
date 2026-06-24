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

void Block::destroy() {
    destroyed = true;
}

bool Block::containsBonus() const {
    return hasBonus;
}

void Block::setBonus(bool value) {
    hasBonus = value;
}

sf::Vector2f Block::getCenter() const {
    sf::FloatRect bounds = shape.getGlobalBounds();

    return sf::Vector2f(
        bounds.left + bounds.width * 0.5f,
        bounds.top + bounds.height * 0.5f
    );
}
