#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"

class BoardRenderer {
public:
	static void draw(sf::RenderWindow& window, const Board& board);

	static bool pixelToCell(
		const Board& board,
		int x,
		int y,
		int& row,
		int& col
	);

	static sf::Vector2f celltoPixel(int row, int col);

	static void drawGem(sf::RenderWindow& window, GemColor color, sf::Vector2f& position);

private:
	static sf::Color toSFMLColor(GemColor color);
};