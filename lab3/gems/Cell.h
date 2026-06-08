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

private:
	GemColor color;
	bool markedForDestroy = false;
	BonusType bonus = BonusType::None;
};
