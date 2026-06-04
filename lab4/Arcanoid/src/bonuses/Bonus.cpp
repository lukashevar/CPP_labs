#include "bonuses/Bonus.h"
#include "entities/Paddle.h"
#include "entities/Ball.h"
#include "Config.h"

Bonus::Bonus(const sf::Vector2f& position) {
	shape.setRadius(10.f);
	shape.setOrigin(10.f, 10.f);
	shape.setPosition(position);
	shape.setFillColor(sf::Color::White);
}

void Bonus::update(float dt) {
	shape.move(0.f, fallSpeed * dt);
}

void Bonus::render(sf::RenderWindow& window) {
	if (!collected)
		window.draw(shape);
}

sf::FloatRect Bonus::getBounds() const {
	return shape.getGlobalBounds();
}

bool Bonus::isCollected() const {
	return collected;
}

void Bonus::collect() {
	collected = true;
}

bool Bonus::isOutOfBounds() const
{
	return shape.getPosition().y > Config::windowHeight;
}
