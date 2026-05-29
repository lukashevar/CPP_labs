#pragma once


#include "Cell.h"

struct FallMove {
	int fromRow;
	int fromCol;

	int toRow;
	int toCol;

	GemColor color;
};
