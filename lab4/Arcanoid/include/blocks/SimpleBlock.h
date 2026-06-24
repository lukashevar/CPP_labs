#pragma once

#include "blocks/Block.h"

class SimpleBlock : public Block {
public:
	SimpleBlock(
		const sf::Vector2f& position,
		const sf::Vector2f& size
	);

	void onHit(Ball& ball) override;
};
