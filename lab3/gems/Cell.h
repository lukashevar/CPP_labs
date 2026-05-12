#pragma once

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

	bool isEmpty() const;
};