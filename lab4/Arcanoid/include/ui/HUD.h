#pragma once

#include <SFML/Graphics.hpp>

class HUD {
public:
	HUD();

	void updateLives(int lives);
	void updateScore(int score);

	void render(sf::RenderWindow& window);

	void showGameOver(bool show);
	void showWin(bool show);

private:
	sf::Font font;

	sf::Text livesText;
	sf::Text scoreText;

	sf::Text gameOverText;
	sf::Text restartText;
	sf::Text winText;

	bool gameOverVisible;
	bool winVisible;
};
