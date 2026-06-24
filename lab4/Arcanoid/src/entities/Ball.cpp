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
	state = BallState::OnPaddle;

	speedBoostActive = false;
	speedBoostTimer = 0.f;
}


void Ball::update(float dt)
{
	if (randomDirectionActive) {
		randomDirectionTimer -= dt;
		if (randomDirectionTimer <= 0) {
			randomDirectionActive = false;
			float angle = (rand() % 120 - 60) * 3.1415926f / 180.f;
			velocity.x = std::sin(angle);
			velocity.y = (velocity.y > 0.f) ? std::cos(angle) : -std::abs(std::cos(angle));
		}
	}

	if (speedBoostActive) {
		speedBoostTimer -= dt;
		if (speedBoostTimer <= 0.f) {
			speedBoostActive = false;
			currentSpeed = baseSpeed;
		}
	}

	if (stickyBonusActive) {
		stickyBonusTimer -= dt;

		if (stickyBonusTimer <= 0.f)
		{
			stickyBonusActive = false;
		}
	}

	if (state == BallState::OnPaddle ||
		state == BallState::StickyOnPaddle) 
	{
		return;
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

void Ball::reset()
{
	shape.setPosition(Config::BallStartX, Config::BallStartY);

	velocity = { 0.f, 0.f };

	state = BallState::OnPaddle;
}

bool Ball::isOutOfBounds() const {
	return shape.getPosition().y > 600.f;
}

void Ball::launch()
{
	if (state == BallState::OnPaddle ||
		state == BallState::StickyOnPaddle)
	{
		state = BallState::Launched;
		velocity = { 0.f, -1.f };
	}
}

void Ball::applySpeedBoost(float factor, float duration) {
	currentSpeed = baseSpeed * factor;
	speedBoostTimer = duration;
	speedBoostActive = true;
}

void Ball::enableSticky()
{
	stickyBonusActive = true;
	stickyBonusTimer = 5.f;
}

bool Ball::isSticky() const
{
	return stickyBonusActive;
}

void Ball::snapToPaddle(float paddleCenterX, float paddleTopY) 
{
	shape.setPosition(paddleCenterX, paddleTopY - getRadius());
	velocity = { 0.f, 0.f };
}

BallState Ball::getState() const {
	return state;
}

void Ball::setState(BallState s) {
	state = s;
}

void Ball::enableRandomDirection() {
	randomDirectionActive = true;
	randomDirectionTimer = (rand() % 3 + 2) * 1.f;
}
