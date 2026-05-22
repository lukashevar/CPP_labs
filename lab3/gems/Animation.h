#pragma once

#include <SFML/Graphics.hpp>
#include "Cell.h"

class Animation {
public:
	Animation(
		GemColor color,
		const sf::Vector2f& from,
		const sf::Vector2f& to,
		float duration
	);

	void update(float dt);

	bool isFinished() const;

	sf::Vector2f getCurrentPosition() const;
	GemColor getColor() const;

private:
	GemColor m_color;

	sf::Vector2f m_from;
	sf::Vector2f m_to;

	float m_duration;
	float m_elapsed;
};