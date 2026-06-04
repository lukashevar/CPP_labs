#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "entities/Paddle.h"
#include "entities/Ball.h"
#include "blocks/Block.h"
#include "ui/HUD.h"
#include "managers/LevelManager.h"
#include "bonuses/Bonus.h"
#include "entities/BottomBarrier.h"

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

	void spawnBonus(sf::Vector2f pos);

	sf::RenderWindow window;
	sf::Clock clock;

	bool isRunning;

	Paddle paddle;
	Ball ball;
	
	LevelManager levelManager;
	std::vector<std::unique_ptr<Bonus>> bonuses;
	std::unique_ptr<BottomBarrier> barrier;

	HUD hud;

	int lives;
	int score;
	bool gameOver;
	bool gameWon;
};