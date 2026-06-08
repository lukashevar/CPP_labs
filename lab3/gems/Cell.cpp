#include "Cell.h"

Cell::Cell()
	: color(GemColor::Black),
	markedForDestroy(false)
{
}

bool Cell::isEmpty() const {
	return color == GemColor::Black;
}

bool Cell::isMarkedForDestroy() const {
	return markedForDestroy;
}

GemColor Cell::getColor() const {
	return color;
}

BonusType Cell::getBonus() const {
	return bonus;
}

void Cell::setColor(GemColor new_color) {
	color = new_color;
}

void Cell::markForDestroy() {
	markedForDestroy = true;
}

void Cell::dismarkForDestroy() {
	markedForDestroy = false;
}