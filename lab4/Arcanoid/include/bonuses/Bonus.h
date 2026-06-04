#pragma once

#include <SFML/Graphics.hpp>

enum class BonusEffect {
	None,
	Sticky,
	SpeedBoost,
	ExpandPaddle,
	BottomBarrier
};

class Bonus {
public:
	Bonus(const sf::Vector2f& position);

	virtual ~Bonus() = default;

	virtual BonusEffect getEffect() const = 0;
	void update(float dt);
	void render(sf::RenderWindow& window);

	bool isCollected() const;
	void collect();

	sf::FloatRect getBounds() const;
	bool isOutOfBounds() const;

protected:
	sf::CircleShape shape;

	float fallSpeed = 180.f;

	bool collected = false;
};
