#include "states/PlayingState.h"
#include "states/MainMenuState.h"
#include "physics/CollisionSystem.h"
#include "Config.h"
#include "bonuses/ExpandPaddleBonus.h"
#include "bonuses/BallSpeedBonus.h"
#include "bonuses/StickyBonus.h"
#include "bonuses/BottomBarrierBonus.h"
#include "bonuses/RandomDirectionBonus.h"
#include <memory>
#include <cstdlib>

PlayingState::PlayingState(StateManager& stateManager, sf::RenderWindow& window, int level)
	: stateManager(stateManager),
	window(window),
	lives(3),
	score(0),
	startLevel(level),
	gameOver(false),
	gameWon(false) 
{
	levelManager.loadLevel(level);
	hud.updateLives(lives);
	hud.updateScore(score);
	paddle.reset();
	ball.reset();
}

void PlayingState::handleInput(const sf::Event& event) {
	if (event.type != sf::Event::KeyPressed)
		return;

	if (gameOver || gameWon) {
		if (event.key.code == sf::Keyboard::R)
			restartGame();
		if (event.key.code == sf::Keyboard::Escape)
			stateManager.change(std::make_unique<MainMenuState>(stateManager, window));
		return;
	}

	if (event.key.code == sf::Keyboard::Space)
		ball.launch();

	if (event.key.code == sf::Keyboard::R)
		restartGame();

	if (event.key.code == sf::Keyboard::Escape)
		stateManager.change(std::make_unique<MainMenuState>(stateManager, window));
}

void PlayingState::update(float dt) {
	if (gameOver || gameWon)
		return;

	dt = std::min(dt, 1.f / 60.f);

	paddle.update(dt);

	if (ball.getState() == BallState::OnPaddle ||
		ball.getState() == BallState::StickyOnPaddle)
	{
		sf::FloatRect pb = paddle.getBounds();
		float centerX = pb.left + pb.width / 2.f;
		float topY = pb.top;
		ball.snapToPaddle(centerX, topY);
	}

	ball.update(dt);

	for (auto& bonus : bonuses) {
		bonus->update(dt);
		if (bonus->isCollected())
			continue;
		if (bonus->getBounds().intersects(paddle.getBounds())) {
			bonus->collect();
			switch (bonus->getEffect()) {
			case BonusEffect::Sticky:
				ball.enableSticky();
				break;
			case BonusEffect::SpeedBoost:
				ball.applySpeedBoost(1.5f, 5.f);
				break;
			case BonusEffect::ExpandPaddle:
				paddle.activateWidthBonus(10.f);
				break;
			case BonusEffect::RandomDirection:
				ball.enableRandomDirection();
				break;
			case BonusEffect::BottomBarrier:
				barrier = std::make_unique<BottomBarrier>();
				break;
			default:
				break;
			}
		}
	}

	bonuses.erase(
		std::remove_if(
			bonuses.begin(),
			bonuses.end(),
			[](const auto& bonus) {
				return bonus->isCollected() || bonus->isOutOfBounds();
			}),
		bonuses.end()
	);

	CollisionSystem::checkBallWalls(ball, Config::windowWidth, Config::windowHeight);
	CollisionSystem::checkBallPaddle(ball, paddle);

	if (barrier && barrier->isActive())
		CollisionSystem::checkBallBarrier(ball, *barrier);

	auto destroyed = CollisionSystem::checkBallBlocks(ball, levelManager.getBlocks());
	for (auto* block : destroyed) {
		score += 10;
		hud.updateScore(score);
		if (block->containsBonus())
			spawnBonus(block->getCenter());
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

	if (levelManager.isLevelCompleted()) {
		size_t next = levelManager.getCurrentLevel() + 1;
		if (next < levelManager.getLevelCount()) {
			levelManager.loadLevel(next);
			ball.reset();
			paddle.reset();
		}
		else {
			gameWon = true;
			hud.showWin(true);
		}
	}
}

void PlayingState::render(sf::RenderWindow& window) {
	paddle.render(window);
	ball.render(window);

	for (auto& block : levelManager.getBlocks())
		block->render(window);

	for (auto& bonus : bonuses)
		bonus->render(window);

	if (barrier && barrier->isActive())
		barrier->render(window);

	hud.render(window);
}

void PlayingState::restartGame() {
	lives = 3;
	score = 0;
	gameOver = false;
	gameWon = false;
	bonuses.clear();
	barrier.reset();
	levelManager.loadLevel(startLevel);
	ball.reset();
	paddle.reset();
	hud.showGameOver(false);
	hud.showWin(false);
	hud.updateLives(lives);
	hud.updateScore(score);
}

void PlayingState::spawnBonus(sf::Vector2f pos) {
	int r = rand() % 5;
	if (r == 0)
		bonuses.push_back(std::make_unique<ExpandPaddleBonus>(pos));
	else if (r == 1)
		bonuses.push_back(std::make_unique<BallSpeedBonus>(pos));
	else if (r == 2)
		bonuses.push_back(std::make_unique<StickyBonus>(pos));
	else if (r == 3)
		bonuses.push_back(std::make_unique<BottomBarrierBonus>(pos));
	else
		bonuses.push_back(std::make_unique<RandomDirectionBonus>(pos));
}
