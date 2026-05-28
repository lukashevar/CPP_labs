#pragma once

#include <optional>
#include <utility>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Board.h"
#include "AnimationManager.h"
#include "ScoreManager.h"

class Game {
public:
	Game();
	void run();

private:
	void processEvents();
	void handleMouseClick(int mouseX, int mouseY);
	void render();
	void update();
	void startDestroyAnimations();
	void startFallAnimations();
	void startBombAnimation(int row, int col);
	void startRecolorAnimation(
		int row,
		int col,
		GemColor color
	);
	
	sf::RenderWindow m_window;
	Board m_board;
	sf::Clock m_clock;
	AnimationManager m_animationManager;
	ScoreManager m_scoreManager;

	std::optional<std::pair<int, int>> m_selectedCell;
	bool m_pendingMove = false;
	bool m_pendingDestroy = false;
	bool m_pendingFall = false;
	int m_moveRow1 = 0;
	int m_moveCol1 = 0;
	int m_moveRow2 = 0;
	int m_moveCol2 = 0;

	sf::Font m_font;
	sf::Text m_scoreText;
};