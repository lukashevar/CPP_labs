#include "Cell.h"

Cell::Cell()
	: color(GemColor::Black),
	markedForDestroy(false)
{
}

bool Cell::isEmpty() const {
	return color == GemColor::Black;
}
