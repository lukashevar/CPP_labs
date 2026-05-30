#include "entities/Block.h"

Block::Block() {
	shape.setSize({ 60.f, 60.f });
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(0.f, 0.f);

	destroyed = false;
}

Block::Block(sf::Vector2f position, sf::Vector2f size, sf::Color color) {
	shape.setSize(size);
	shape.setFillColor(color);
	shape.setPosition(position);

	destroyed = false;
}

void Block::render(sf::RenderWindow& window) {
	if (!destroyed)
		window.draw(shape);
}

sf::FloatRect Block::getBounds() const {
	return shape.getGlobalBounds();
}

bool Block::isDestroyed() const {
	return destroyed;
}

void Block::destroy() {
	destroyed = true;
}
