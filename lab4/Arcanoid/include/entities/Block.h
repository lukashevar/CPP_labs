#pragma once

#include <SFML/Graphics.hpp>

class Block {
public:
	Block();
	Block(sf::Vector2f position, sf::Vector2f size, sf::Color color = sf::Color::Blue);

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

	bool isDestroyed() const;
	void destroy();

private:
	sf::RectangleShape shape;
	bool destroyed;
};
