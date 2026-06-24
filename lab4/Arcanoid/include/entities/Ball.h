#pragma once

#include <SFML/Graphics.hpp>

enum class BallState {
	OnPaddle,
	Launched,
	StickyOnPaddle
};

class Ball {
public:
	Ball();

	void update(float dt);
	void render(sf::RenderWindow& window);
	void reset();
	void launch();

	void setPosition(float x, float y);

	bool isOutOfBounds() const;

	void enableSticky();
	bool isSticky() const;
	
	void snapToPaddle(float paddleCenterX, float paddleTopY);

	void enableRandomDirection();

	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;
	sf::FloatRect getBounds() const;
	BallState getState() const;
	float getRadius() const;

	void setVelocity(const sf::Vector2f& v);
	void applySpeedBoost(float factor, float duration);

	void setState(BallState s);

private:
	sf::CircleShape shape;

	sf::Vector2f velocity;
	float baseSpeed;
	float currentSpeed;

	bool speedBoostActive = false;
	float speedBoostTimer = 0.f;

	BallState state = BallState::OnPaddle;

	bool stickyBonusActive = false;
	float stickyBonusTimer = 0.f;

	bool randomDirectionActive = false;
	float randomDirectionTimer = 0.f;
};
