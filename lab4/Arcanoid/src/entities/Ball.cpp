#include "entities/Ball.h"
#include "Config.h"

Ball::Ball() {
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(10.f, 10.f);

	shape.setPosition(Config::BallStartX, Config::BallStartY);

	baseSpeed = 400.f;
	currentSpeed = baseSpeed;

	velocity = { 0.f, 0.f };
	isLaunched = false;

	speedBoostActive = false;
	speedBoostTimer = 0.f;
}


void Ball::update(float dt) {
	if (!isLaunched)
		return;

	if (speedBoostActive)
	{
		speedBoostTimer -= dt;

		if (speedBoostTimer <= 0.f)
		{
			speedBoostActive = false;
			currentSpeed = baseSpeed;
		}
	}

	shape.move(velocity * currentSpeed * dt);
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

float Ball::getRadius() const {
	return shape.getRadius();
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
		velocity = { 0.f, -1.f };
	}
}

void Ball::applySpeedBoost(float factor, float duration) {
	currentSpeed = baseSpeed * factor;
	speedBoostTimer = duration;
	speedBoostActive = true;
}