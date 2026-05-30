#include "core/Game.h"

Game::Game()
	: window(sf::VideoMode(800, 600), "Arkanoid"),
	isRunning(true),
	lives(3),
	gameOver(false) {
	window.setFramerateLimit(60);
	
	createLevel();
}


Game::~Game() {}


void Game::run() {
	while (isRunning && window.isOpen()) {
		float dt = clock.restart().asSeconds();

		proccessEvents();
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

		handleInput(event);
	}
}


void Game::handleInput(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::R) {
			restartGame();
		}
	}
}


void Game::update(float dt) {
	paddle.update(dt);
	ball.update(dt);

	checkCollision();
	checkBlockCollisions();

	if (ball.isOutOfBounds()) {
		lives--;

		if (lives <= 0) {
			gameOver = true;
		}
		else {
			ball.reset();

			paddle.setPosition(300.f, 550.f);
		}
	}
}


void Game::render() {
	window.clear(sf::Color::Black);

	paddle.render(window);
	ball.render(window);
	for (auto& block : blocks) {
		block.render(window);
	}

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

void Game::createLevel() {
	blocks.clear();

	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			blocks.emplace_back(
				sf::Vector2f(60.f + x * 65.f, 50.f + y * 30.f),
				sf::Vector2f(60.f, 20.f),
				sf::Color::Blue
			);
		}
	}
}

void Game::checkBlockCollisions() {
	sf::FloatRect ballBounds = ball.getBounds();

	for (auto& block : blocks) {
		if (block.isDestroyed())
			continue;

		if (ballBounds.intersects(block.getBounds())) {
			block.destroy();

			sf::Vector2f vel = ball.getVelocity();
			vel.y = -vel.y;
			ball.setVelocity(vel);

			break;
		}
	}
}

void Game::restartGame() {
	lives = 3;
	gameOver = false;

	blocks.clear();
	createLevel();

	ball.reset();
	paddle.setPosition(300.f, 550.f);
}
