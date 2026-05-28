#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "AnimationManager.h"

class BoardRenderer {
public:
	static void draw(
		sf::RenderWindow& window, 
		const Board& board,
		const AnimationManager& animations
	);

	static bool pixelToCell(
		const Board& board,
		int x,
		int y,
		int& row,
		int& col
	);

	static sf::Vector2f celltoPixel(int row, int col);

	static void drawGem(sf::RenderWindow& window, 
		GemColor color, 
		const sf::Vector2f& position,
		float scale = 1.f,
		float alpha = 255.f
	);

private:
	static sf::Color toSFMLColor(GemColor color);
};