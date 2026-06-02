#pragma once

#include "blocks/Block.h"

class SpeedBoostBlock : public Block {
public:
	SpeedBoostBlock(
		const sf::Vector2f& position,
		const sf::Vector2f& size
	);

	void onHit(Ball& ball) override;
};