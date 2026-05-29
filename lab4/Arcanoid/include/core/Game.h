#pragma once

#include "entities/Paddle.h"
#include <SFML/Graphics.hpp>


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


	sf::RenderWindow window;
	sf::Clock clock;

	bool isRunning;

	Paddle paddle;
};