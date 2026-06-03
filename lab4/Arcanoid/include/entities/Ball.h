#pragma once

#include <SFML/Graphics.hpp>

enum class BallState {
	OnPaddle,
	Launched
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

	void enableStickyMode();
	bool isStickyMode() const;
	void disableStickyMode();

	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;
	sf::FloatRect getBounds() const;
	float getSpeed() const;
	float getRadius() const;

	void setVelocity(const sf::Vector2f& v);
	void applySpeedBoost(float factor, float duration);

private:
	sf::CircleShape shape;

	sf::Vector2f velocity;
	float baseSpeed;
	float currentSpeed;

	bool speedBoostActive = false;
	float speedBoostTimer = 0.f;

	BallState state = BallState::OnPaddle;
	
	bool isLaunched;

	bool stickyMode = false;
};
