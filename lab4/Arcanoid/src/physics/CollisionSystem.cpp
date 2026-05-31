#include "physics/CollisionSystem.h"

void CollisionSystem::checkBallWalls(
	Ball& ball,
	float windowWidth,
	float windowHeight
) {
	sf::Vector2f pos = ball.getPosition();
	sf::Vector2f vel = ball.getVelocity();

	float radius = ball.getBounds().width / 2.f;

	if (pos.x - radius <= 0.f) {
		vel.x = std::abs(vel.x);
		ball.setPosition(radius, pos.y);
	}

	if (pos.x + radius >= windowWidth) {
		vel.x = -std::abs(vel.x);
		ball.setPosition(windowWidth - radius, pos.y);
	}

	if (pos.y - radius <= 0.f) {
		vel.y = std::abs(vel.y);
		ball.setPosition(pos.x, radius);
	}

	ball.setVelocity(vel);
}

void CollisionSystem::checkBallPaddle(
	Ball& ball,
	Paddle& paddle
) {
	sf::FloatRect ballBounds = ball.getBounds();
	sf::FloatRect paddleBounds = paddle.getBounds();

	if (!ballBounds.intersects(paddleBounds))
		return;

	float paddleCenter = paddleBounds.left + paddleBounds.width / 2.f;
	float ballCenter = ballBounds.left + ballBounds.width / 2.f;

	float offset = (ballCenter - paddleCenter) / (paddleBounds.width / 2.f);

	offset = std::clamp(offset, -1.f, 1.f);

	float angle = offset * 60.f * 3.1415926f / 180.f;

	sf::Vector2f vel;

	vel.x = std::sin(angle);
	vel.y = -std::abs(std::cos(angle));

	ball.setVelocity(vel);
}

bool CollisionSystem::checkBallBlocks(
    Ball& ball,
    std::vector<std::unique_ptr<Block>>& blocks)
{
    sf::FloatRect ballBounds = ball.getBounds();
    float radius = ball.getRadius();

    for (auto& block : blocks)
    {
        if (block->isDestroyed())
            continue;

        sf::FloatRect blockBounds = block->getBounds();

        if (!ballBounds.intersects(blockBounds))
            continue;

        block->onHit(ball);

        float ballCenterX =
            ballBounds.left + ballBounds.width / 2.f;

        float ballCenterY =
            ballBounds.top + ballBounds.height / 2.f;

        float blockCenterX =
            blockBounds.left + blockBounds.width / 2.f;

        float blockCenterY =
            blockBounds.top + blockBounds.height / 2.f;

        float dx = ballCenterX - blockCenterX;
        float dy = ballCenterY - blockCenterY;

        float overlapX =
            (ballBounds.width + blockBounds.width) / 2.f
            - std::abs(dx);

        float overlapY =
            (ballBounds.height + blockBounds.height) / 2.f
            - std::abs(dy);

        sf::Vector2f vel = ball.getVelocity();
        sf::Vector2f pos = ball.getPosition();

        if (overlapX < overlapY)
        {
            vel.x = -vel.x;

            if (dx > 0.f)
            {
                ball.setPosition(
                    blockBounds.left +
                    blockBounds.width +
                    radius,
                    pos.y);
            }
            else
            {
                ball.setPosition(
                    blockBounds.left -
                    radius,
                    pos.y);
            }
        }
        else
        {
            vel.y = -vel.y;

            if (dy > 0.f)
            {
                ball.setPosition(
                    pos.x,
                    blockBounds.top +
                    blockBounds.height +
                    radius);
            }
            else
            {
                ball.setPosition(
                    pos.x,
                    blockBounds.top -
                    radius);
            }
        }

        ball.setVelocity(vel);

        return true;
    }

    return false;
}