#include "blocks/SimpleBlock.h"

SimpleBlock::SimpleBlock(
	const sf::Vector2f& position,
	const sf::Vector2f& size)
	: Block(
		position,
		size,
		sf::Color::Blue) {}

void SimpleBlock::onHit(Ball& ball) {
	destroy();
}