#include "core/Game.h"
#include "physics/CollisionSystem.h"
#include "Config.h"

#include <memory>

Game::Game()
	: window(
		sf::VideoMode(
			Config::windowWidth,
			Config::windowHeight),
		"Arkanoid"),
	isRunning(true),
	lives(3),
	gameOver(false),
	gameWon(false)
{
	window.setFramerateLimit(60);

	levelManager.loadLevel(3);

	score = 0;

	hud.updateLives(lives);
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


void Game::handleInput(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return;

	if (gameOver || gameWon)
	{
		if (event.key.code == sf::Keyboard::R)
		{
			restartGame();
		}

		return;
	}

	if (event.key.code == sf::Keyboard::Space)
	{
		ball.launch();
	}

	if (event.key.code == sf::Keyboard::R)
	{
		restartGame();
	}
}


void Game::update(float dt) {
	if (gameOver || gameWon)
		return;

	paddle.update(dt);
	ball.update(dt);

	CollisionSystem::checkBallWalls(ball, Config::windowWidth, Config::windowHeight);
	CollisionSystem::checkBallPaddle(ball, paddle);
	if (CollisionSystem::checkBallBlocks(ball, levelManager.getBlocks())){
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

	if (levelManager.isLevelCompleted())
	{
		int next = levelManager.getCurrentLevel() + 1;

		if (next < 3)
		{
			levelManager.loadLevel(next);

			ball.reset();
			paddle.reset();
		}
		else
		{
			gameWon = true;
		}
	}
}


void Game::render() {
	window.clear(sf::Color::Black);

	paddle.render(window);
	ball.render(window);
	for (auto& block : levelManager.getBlocks())
	{
		block->render(window);
	}
	hud.render(window);

	window.display();
}



void Game::restartGame() {
	lives = 3;
	score = 0;
	gameOver = false;
	gameWon = false;

	levelManager.loadLevel(0);

	ball.reset();
	paddle.reset();

	hud.showGameOver(false);
	hud.showWin(false);
	hud.updateLives(lives);
	hud.updateScore(score);
}
