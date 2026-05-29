#pragma once

#include <SFML/Graphics.hpp>

#include "entities/Paddle.h"
#include "entities/Ball.h"


class Game {
public:
	Game();
	~Game();

	void run();

private:
	void proccessEvents();
	void update(float dt);
	void render();

	void handleInput();

	void checkCollision();


	sf::RenderWindow window;
	sf::Clock clock;

	bool isRunning;

	Paddle paddle;
	Ball ball;
};