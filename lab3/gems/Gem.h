#pragma once

#include "GemColor.h"
#include <cassert>

class Board;
class AnimationManager;

class Gem {
public:
	Gem(GemColor color)
		: m_color(color) {}

	virtual ~Gem() = default;

	virtual GemColor getColor() const { return m_color; }

	virtual bool isBonus() const { return false; }

	virtual void activate(
		Board& board,
		AnimationManager& animations,
		int row,
		int col
	) {}

protected:
	GemColor m_color;
};
