#include "core/Game.h"
#include "physics/CollisionSystem.h"
#include "Config.h"

Game::Game()
	: window(sf::VideoMode(800, 600), "Arkanoid"),
	isRunning(true),
	lives(3),
	gameOver(false),
	gameWon(false) {
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

		if (gameOver || gameWon) {
			if (event.key.code == sf::Keyboard::R) {
				restartGame();
			}

			return;
		}
	}
}


void Game::update(float dt) {
	if (gameOver || gameWon)
		return;

	paddle.update(dt);
	ball.update(dt);

	CollisionSystem::checkBallWalls(ball, Config::windowWidth, Config::windowHeight);
	CollisionSystem::checkBallPaddle(ball, paddle);
	if (CollisionSystem::checkBallBlocks(ball, blocks)) {
		score += 10; 
		hud.updateScore(score);
	}
	
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

	if (isLevelCompleted()) {
		gameWon = true;
		hud.showWin(true);
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

void Game::restartGame() {
	lives = 3;
	score = 0;
	gameOver = false;
	gameWon = false;

	blocks.clear();
	createLevel();

	ball.reset();
	paddle.reset();

	hud.showGameOver(false);
	hud.showWin(false);
	hud.updateLives(lives);
	hud.updateScore(score);
}

bool Game::isLevelCompleted() const {
	for (const auto& block : blocks) {
		if (!block.isDestroyed())
			return false;
	}
	return true;
}

