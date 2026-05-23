#pragma once

#include <SFML/Graphics.hpp>
#include "Cell.h"

enum class AnimationType {
	Swap,
	Destroy,
	Fall
};

class Animation {
public:
	Animation(
		AnimationType type,
		GemColor color,
		const sf::Vector2f& from,
		const sf::Vector2f& to,
		float duration
	);

	void update(float dt);

	bool isFinished() const;

	sf::Vector2f getCurrentPosition() const;
	GemColor getColor() const;
	float getScale() const;
	AnimationType getType() const;

private:
	AnimationType m_type;

	GemColor m_color;

	sf::Vector2f m_from;
	sf::Vector2f m_to;

	float m_duration;
	float m_elapsed;
};