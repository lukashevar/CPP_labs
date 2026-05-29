#include "core/Game.h"

Game::Game()
	: window(sf::VideoMode(800, 600), "Arkanoid"),
	isRunning(true) {
	window.setFramerateLimit(60);
}


Game::~Game() {}


void Game::run() {
	while (isRunning && window.isOpen()) {
		float dt = clock.restart().asSeconds();

		proccessEvents();
		handleInput();
		update(dt);
		render();
	}
}


void Game::proccessEvents() {
	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
			isRunning = false;
		}
	}
}


void Game::handleInput() {}


void Game::update(float dt) {
	paddle.update(dt);
}


void Game::render() {
	window.clear(sf::Color::Black);

	paddle.render(window);

	window.display();
}


