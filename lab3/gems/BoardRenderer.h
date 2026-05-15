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

private:
	static sf::Color toSFMLColor(GemColor color);
};