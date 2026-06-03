#pragma once

#include <SFML/Graphics.hpp>

class Paddle {
public:
	Paddle();

	void update(float dt);
	void render(sf::RenderWindow& window);
	void reset();

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;
	float getWidth() const;

	void setPosition(float x, float y);
	void setWidth(float width);

	void activateWidthBonus(float duration);

private:
	void handleInput(float dt);

	sf::RectangleShape shape;

	float speed;
	sf::Vector2f velocity;

	float baseWidth = 120.f;

	bool widthBonusActive = false;
	float widthBonusTimer = 0.f;
};