#include "entities/Paddle.h"

Paddle::Paddle() {
	shape.setSize(sf::Vector2f(120.f, 20.f));
	shape.setFillColor(sf::Color::White);

	speed = 500.f;
	velocity = { 0.f, 0.f };

	shape.setPosition(300.f, 550.f);
}


void Paddle::update(float dt) {
	handleInput(dt);

	shape.move(velocity * dt);

	if (shape.getPosition().x < 0)
		shape.setPosition(0, shape.getPosition().y);

	if (shape.getPosition().x + shape.getSize().x > 800)
		shape.setPosition(800 - shape.getSize().x, shape.getPosition().y);

}


void Paddle::handleInput(float dt) {
	velocity.x = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velocity.x = -speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity.x = speed;
	}
}


void Paddle::render(sf::RenderWindow& window) {
	window.draw(shape);
}


void Paddle::setPosition(float x, float y) {
	shape.setPosition(x, y);
}


sf::Vector2f Paddle::getPosition() const {
	return shape.getPosition();
}


sf::FloatRect Paddle::getBounds() const {
	return shape.getGlobalBounds();
}
