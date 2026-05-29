#pragma once

#include <SFML/Graphics.hpp>

class Ball {
public:
	Ball();

	void update(float dt);
	void render(sf::RenderWindow& window);

	void setPosition(float x, float y);

	sf::Vector2f getPosition() const;
	sf::Vector2f getVelocity() const;
	sf::FloatRect getBounds() const;

	void setVelocity(const sf::Vector2f& v);

private:
	sf::CircleShape shape;
	sf::Vector2f velocity;

	float speed;
};
