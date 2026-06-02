#pragma once

#include <SFML/Graphics.hpp>

class Ball;

class Block {
public:
	Block(const sf::Vector2f& position,
		const sf::Vector2f& size,
		const sf::Color& color);

	virtual ~Block() = default;

	virtual void onHit(Ball& ball) = 0;

	virtual bool isDestroyed() const;

	virtual void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

protected:
	sf::RectangleShape shape;
	bool destroyed;

	void destroy();
};
