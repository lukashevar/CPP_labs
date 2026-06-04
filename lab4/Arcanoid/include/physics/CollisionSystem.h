#pragma once

#include "entities/Ball.h"
#include "blocks/Block.h"
#include "entities/Paddle.h"
#include "entities/BottomBarrier.h"

#include <vector>
#include <memory>

class CollisionSystem {
public:
	static void checkBallWalls(
		Ball& ball,
		float windowWidth,
		float windowHeight
	);

	static void checkBallPaddle(
		Ball& ball,
		Paddle& paddle
	);

	static std::vector<Block*> checkBallBlocks(
		Ball& ball,
		std::vector<std::unique_ptr<Block>>& blocks
	);

	static void checkBallBarrier(Ball& ball, BottomBarrier& barrier);
};
