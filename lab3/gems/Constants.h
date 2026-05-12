#pragma once

namespace Constants {
	constexpr int ROWS = 8;
	constexpr int COLS = 8;

	constexpr int CELL_SIZE = 64;

	constexpr int WINDOW_WIDTH = COLS * CELL_SIZE;
	constexpr int WINDOW_HEIGHT = ROWS * CELL_SIZE;

	constexpr int GEM_COLOR_COUNT = 5;
}