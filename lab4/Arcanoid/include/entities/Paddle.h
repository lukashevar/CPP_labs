#pragma once

#include <SFML/Graphics.hpp>

class Paddle {
public:
	Paddle();

	void update(float dt);
	void render(sf::RenderWindow& window);

	void setPosition(float x, float y);
	sf::Vector2f getPosition() const;

	sf::FloatRect getBounds() const;

private:
	void handleInput(float dt);

	sf::RectangleShape shape;

	float speed;
	sf::Vector2f velocity;

};