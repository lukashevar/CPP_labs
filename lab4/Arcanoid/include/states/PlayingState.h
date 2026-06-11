#pragma once
#include "states/State.h"
#include "managers/StateManager.h"
#include "managers/LevelManager.h"
#include "entities/Ball.h"
#include "entities/Paddle.h"
#include "entities/BottomBarrier.h"
#include "bonuses/Bonus.h"
#include "ui/HUD.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class PlayingState : public State {
public:
	PlayingState(StateManager& stateManager, sf::RenderWindow& window, int level);
	void handleInput(const sf::Event& event) override;
	void update(float dt) override;
	void render(sf::RenderWindow& window) override;
private:
	void spawnBonus(sf::Vector2f pos);
	void restartGame();

	StateManager& stateManager;
	sf::RenderWindow& window;

	Paddle paddle;
	Ball ball;
	LevelManager levelManager;
	HUD hud;

	std::vector<std::unique_ptr<Bonus>> bonuses;
	std::unique_ptr<BottomBarrier> barrier;

	int lives;
	int score;
	int startLevel;
	bool gameOver;
	bool gameWon;
};
