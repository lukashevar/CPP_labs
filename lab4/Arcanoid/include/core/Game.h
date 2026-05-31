#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "entities/Paddle.h"
#include "entities/Ball.h"
#include "entities/Block.h"
#include "ui/HUD.h"


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

	void createLevel();
	void restartGame();

	bool isLevelCompleted() const;


	sf::RenderWindow window;
	sf::Clock clock;

	bool isRunning;

	Paddle paddle;
	Ball ball;
	std::vector<Block> blocks;

	HUD hud;

	int lives;
	int score;
	bool gameOver;
	bool gameWon;
};