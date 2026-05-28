#pragma once
#include "FallMove.h"
#include <vector>
#include "AnimationManager.h"

class Board;


class BoardProcessor {
public:
	static void destroyMarkedCells(Board& board, AnimationManager& animations);
	static void collapseColumns(Board& board);
	static void fillEmptyCells(Board& board);
	static void process(Board& board, AnimationManager& animations);
	static std::vector<FallMove> collectFallMoves(Board& board);
};