#include "entities/BottomBarrier.h"
#include "Config.h"

BottomBarrier::BottomBarrier() {
	shape.setSize(sf::Vector2f(Config::windowWidth, 10.f));
	shape.setPosition(0.f, Config::windowHeight - 10.f);
	shape.setFillColor(sf::Color::Cyan);
}

void BottomBarrier::render(sf::RenderWindow& window) {
	if (active)
		window.draw(shape);
}

sf::FloatRect BottomBarrier::getBounds() const {
	return shape.getGlobalBounds();
}

bool BottomBarrier::isActive() const {
	return active;
}

void BottomBarrier::deactivate() {
	active = false;
}