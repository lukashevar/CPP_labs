#pragma once

#include <optional>
#include <utility>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Board.h"
#include "AnimationManager.h"

class Game {
public:
	Game();
	void run();

private:
	void processEvents();
	void handleMouseClick(int mouseX, int mouseY);
	void render();
	void update();
	
	sf::RenderWindow m_window;
	Board m_board;
	sf::Clock m_clock;
	AnimationManager m_animationManager;

	std::optional<std::pair<int, int>> m_selectedCell;
	bool m_pendingMove = false;
	int m_moveRow1 = 0;
	int m_moveCol1 = 0;
	int m_moveRow2 = 0;
	int m_moveCol2 = 0;
};