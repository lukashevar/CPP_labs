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
	sf::Vector2f getCenter() const;

	bool containsBonus() const;

	void setBonus(bool value);

	virtual bool isBreakable() const { return true; }
protected:
	sf::RectangleShape shape;
	bool destroyed;
	bool hasBonus = false;

	void destroy();
};
