#include "blocks/SpeedBoostBlock.h"
#include "entities/Ball.h"

SpeedBoostBlock::SpeedBoostBlock(
	const sf::Vector2f& position,
	const sf::Vector2f& size)
	: Block(position, size, sf::Color::Magenta) {}

void SpeedBoostBlock::onHit(Ball& ball) {
	ball.applySpeedBoost(1.5f, 3.0f);
	destroy();
}
