#pragma once

class Board;

class MatchFinder {
public:
	static bool findMatches(Board& board);

private:
	static void clearMarks(Board& board);
	static bool findHorizontalMatches(Board& board);
	static bool findVerticalMatches(Board& board);
};