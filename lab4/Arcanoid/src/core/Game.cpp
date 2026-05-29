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
	ball.update(dt);

	checkCollision();
}


void Game::render() {
	window.clear(sf::Color::Black);

	paddle.render(window);
	ball.render(window);

	window.display();
}


void Game::checkCollision() {
	sf::FloatRect ballBounds = ball.getBounds();
	sf::FloatRect paddleBounds = paddle.getBounds();

	if (ballBounds.intersects(paddleBounds)) {
		float paddleCenter = paddleBounds.left + paddleBounds.width / 2.f;
		float ballCenter = ballBounds.left + ballBounds.width / 2.f;

		float distance = (ballCenter - paddleCenter) / (paddleBounds.width / 2.f);

		if (distance < -1.f) distance = -1.f;
		if (distance > 1.f) distance = 1.f;

		sf::Vector2f vel = ball.getVelocity();

		vel.x = distance;
		vel.y = -std::abs(vel.y);

		ball.setVelocity(vel);
	} 
}

