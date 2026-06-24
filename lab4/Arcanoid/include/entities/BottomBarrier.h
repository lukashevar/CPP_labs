#pragma once

#include <SFML/Graphics.hpp>

class BottomBarrier {
public:
	BottomBarrier();
	void render(sf::RenderWindow& window);
	sf::FloatRect getBounds() const;
	bool isActive() const;
	void deactivate();
private:
	sf::RectangleShape shape;
	bool active = true;
};
