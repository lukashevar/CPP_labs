#include "entities/Ball.h"
#include "Config.h"

Ball::Ball() {
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(10.f, 10.f);

	shape.setPosition(400.f, 300.f);

	speed = 400.f;
	velocity = { -1.f, -1.f };
}


void Ball::update(float dt) {
	if (!isLaunched)
		return;

	shape.move(velocity * speed * dt);

	sf::Vector2f pos = shape.getPosition();

	if (pos.x <= 0.f || pos.x >= 800.f)
		velocity.x = -velocity.x;

	if (pos.y <= 0.f)
		velocity.y = -velocity.y;

	
}


void Ball::render(sf::RenderWindow& window) {
	window.draw(shape);
}


void Ball::setPosition(float x, float y) {
	shape.setPosition(x, y);
}


sf::Vector2f Ball::getPosition() const {
	return shape.getPosition();
}


sf::Vector2f Ball::getVelocity() const {
	return velocity;
}


void Ball::setVelocity(const sf::Vector2f& v) {
	velocity = v;
}


sf::FloatRect Ball::getBounds() const {
	return shape.getGlobalBounds();
}

void Ball::reset() {
	shape.setPosition(Config::BallStartX, Config::BallStartY);

	velocity = { 0.f, 0.f };

	isLaunched = false;
}

bool Ball::isOutOfBounds() const {
	return shape.getPosition().y > 600.f;
}

void Ball::launch() {
	if (!isLaunched) {
		isLaunched = true;
		velocity = { -1.f, -1.f };
	}
}