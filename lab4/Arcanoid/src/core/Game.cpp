#include "core/Game.h"

Game::Game()
	: window(sf::VideoMode(800, 600), "Arkanoid"),
	isRunning(true),
	lives(3),
	gameOver(false) {
	window.setFramerateLimit(60);
	
	createLevel();

	score = 0;
	hud.updateScore(score);

	paddle.reset();
	ball.reset();
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
		if (event.key.code == sf::Keyboard::Space) {
			ball.launch();
		}

		if (event.key.code == sf::Keyboard::R) {
			restartGame();
		}
	}
}


void Game::update(float dt) {
	paddle.update(dt);
	ball.update(dt);

	checkWallCollisions();
	checkCollision();
	checkBlockCollisions();

	if (ball.isOutOfBounds()) {
		lives--;

		hud.updateLives(lives);

		if (lives <= 0) {
			gameOver = true;
			hud.showGameOver(true);
			hud.updateLives(0);
		}

		else {
			ball.reset();
			paddle.reset();
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
	hud.render(window);

	window.display();
}


void Game::checkCollision() {
	sf::FloatRect ballBounds = ball.getBounds();
	sf::FloatRect paddleBounds = paddle.getBounds();

	if (ballBounds.intersects(paddleBounds)) {
		float paddleCenter = paddleBounds.left + paddleBounds.width / 2.f;
		float ballCenter = ballBounds.left + ballBounds.width / 2.f;

		float offset = (ballCenter - paddleCenter) / (paddleBounds.width / 2.f);

		
		if (offset < -1.f) offset = -1.f;
		if (offset > 1.f) offset = 1.f;

		float maxAngle = 60.f * 3.14159f / 180.f; 

		float angle = offset * maxAngle;

		float speed = ball.getSpeed();

		sf::Vector2f newDir;
		newDir.x = sin(angle);
		newDir.y = -cos(angle);

		ball.setVelocity(newDir);
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
	sf::Vector2f ballPos = ball.getPosition();
	sf::Vector2f vel = ball.getVelocity();

	for (auto& block : blocks)
	{
		if (block.isDestroyed())
			continue;

		sf::FloatRect blockBounds = block.getBounds();

		if (!ballBounds.intersects(blockBounds))
			continue;

		block.destroy();
		score += 10;
		hud.updateScore(score);
		
		float ballCenterX = ballBounds.left + ballBounds.width / 2.f;
		float ballCenterY = ballBounds.top + ballBounds.height / 2.f;

		float blockCenterX = blockBounds.left + blockBounds.width / 2.f;
		float blockCenterY = blockBounds.top + blockBounds.height / 2.f;

		float dx = ballCenterX - blockCenterX;
		float dy = ballCenterY - blockCenterY;

		float overlapX = (ballBounds.width + blockBounds.width) / 2.f - std::abs(dx);
		float overlapY = (ballBounds.height + blockBounds.height) / 2.f - std::abs(dy);

		if (overlapX < overlapY)
		{
			vel.x = -vel.x;

			if (dx > 0)
				ball.setPosition(blockBounds.left + blockBounds.width + ballBounds.width / 2.f, ballPos.y);
			else
				ball.setPosition(blockBounds.left - ballBounds.width / 2.f, ballPos.y);
		}
		else
		{
			vel.y = -vel.y;

			if (dy > 0)
				ball.setPosition(ballPos.x, blockBounds.top + blockBounds.height + ballBounds.height / 2.f);
			else
				ball.setPosition(ballPos.x, blockBounds.top - ballBounds.height / 2.f);
		}

		ball.setVelocity(vel);
		break; 
	}
}

void Game::checkWallCollisions() {
	sf::Vector2f pos = ball.getPosition();
	sf::Vector2f vel = ball.getVelocity();
	sf::FloatRect bounds = ball.getBounds();

	if (pos.x - bounds.width / 2.f <= 0) {
		vel.x = std::abs(vel.x);
		ball.setPosition(bounds.width / 2.f, pos.y);
	}

	if (pos.x + bounds.width / 2.f >= 800) {
		vel.x = -std::abs(vel.x);
		ball.setPosition(800.f - bounds.width / 2.f, pos.y);
	}

	if (pos.y - bounds.height / 2.f <= 0.f)
	{
		vel.y = std::abs(vel.y);
		ball.setPosition(pos.x, bounds.height / 2.f);
	}

	ball.setVelocity(vel);
}

void Game::restartGame() {
	lives = 3;
	score = 0;
	gameOver = false;

	blocks.clear();
	createLevel();

	ball.reset();
	paddle.reset();

	hud.showGameOver(false);
	hud.updateLives(lives);
	hud.updateScore(score);
}
