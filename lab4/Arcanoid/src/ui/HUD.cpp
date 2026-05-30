#include "ui/HUD.h"
#include <stdexcept>
#include <iostream>

HUD::HUD()
	: gameOverVisible(false) {

	if (!font.loadFromFile("assets/arialmt.ttf")) {
		throw std::runtime_error("Failed to load font");
	}

	livesText.setFont(font);
	livesText.setCharacterSize(72);
	livesText.setPosition(10.f, 10.f);

	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setPosition(350.f, 10.f);

	gameOverText.setFont(font);
	gameOverText.setString("GAME OVER");
	gameOverText.setCharacterSize(48);
	gameOverText.setFillColor(sf::Color::Red);

	restartText.setFont(font);
	restartText.setString("Press R to restart game");
	restartText.setCharacterSize(24);

	gameOverText.setPosition(250.f, 250.f);
	restartText.setPosition(250.f, 320.f);

	updateLives(3);
	updateScore(0);
}

void HUD::updateLives(int lives) {
	livesText.setString(std::to_string(lives));
}

void HUD::updateScore(int score) {
	scoreText.setString("Score: " + std::to_string(score));
}

void HUD::showGameOver(bool show) {
	gameOverVisible = show;
}

void HUD::render(sf::RenderWindow& window) {
	window.draw(livesText);
	window.draw(scoreText);

	if (gameOverVisible) {
		window.draw(gameOverText);
		window.draw(restartText);
	}
}
