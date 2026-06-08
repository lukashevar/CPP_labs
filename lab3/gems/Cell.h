#pragma once
#include "BonusType.h"

enum class GemColor {
	Red,
	Green,
	Blue,
	Yellow,
	Black
};

class Cell {
public:
	Cell();

	bool isEmpty() const;
	bool isMarkedForDestroy() const;

	GemColor getColor() const;
	BonusType getBonus() const;

	void setColor(GemColor new_color);

	void markForDestroy();
	void dismarkForDestroy();

private:
	GemColor color;
	bool markedForDestroy = false;
	BonusType bonus = BonusType::None;
};
