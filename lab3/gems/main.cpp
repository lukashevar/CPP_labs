#include <SFML/Graphics.hpp>
#include "Board.h"

int main() {
	const int rows = 8;
	const int cols = 8;
	const float cellSize = 64.f;

	sf::RenderWindow window(
		sf::VideoMode(cols * cellSize, rows * cellSize),
		"GEMS"
	);

	Board board(rows, cols);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		board.draw(window);
		window.display();
	}

	return 0;
}