#pragma once

#include <optional>
#include <utility>

#include <SFML/Graphics.hpp>

#include "Board.h"

class Game {
public:
	Game();
	void run();

private:
	void processEvents();
	void handleMouseClick(int mouseX, int mouseY);
	void render();
	
	sf::RenderWindow m_window;
	Board m_board;

	std::optional<std::pair<int, int>> m_selectedCell;
};