#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "entities/Paddle.h"
#include "entities/Ball.h"
#include "blocks/Block.h"
#include "ui/HUD.h"
#include "managers/LevelManager.h"

#include <memory>


class Game {
public:
	Game();
	~Game();

	void run();

private:
	void proccessEvents();
	void update(float dt);
	void render();

	void handleInput(const sf::Event& event);

	void restartGame();

	sf::RenderWindow window;
	sf::Clock clock;

	bool isRunning;

	Paddle paddle;
	Ball ball;
	
	LevelManager levelManager;

	HUD hud;

	int lives;
	int score;
	bool gameOver;
	bool gameWon;
};