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

	GemColor color;
	bool markedForDestroy = false;
	BonusType bonus = BonusType::None;

	bool isEmpty() const;
};