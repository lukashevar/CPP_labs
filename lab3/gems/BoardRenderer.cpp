#include "BoardRenderer.h"
#include "Cell.h"
#include "Constants.h"
#include "Animation.h"


sf::Color BoardRenderer::toSFMLColor(GemColor color) {
	switch (color) {
	case GemColor::Red:
		return sf::Color::Red;

	case GemColor::Green:
		return sf::Color::Green;

	case GemColor::Blue:
		return sf::Color::Blue;

	case GemColor::Yellow:
		return sf::Color::Yellow;

	case GemColor::Black:
	default:
		return sf::Color::Black;
	}
}


void BoardRenderer::draw(
	sf::RenderWindow& window, 
	const Board& board,
	const AnimationManager& animations
) {
	sf::RectangleShape rect(
		sf::Vector2f(
			static_cast<float>(Constants::CELL_SIZE),
			static_cast<float>(Constants::CELL_SIZE)
		)
	);

	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(sf::Color::Black);

	for (int row = 0; row < board.getRows(); ++row) {
		for (int col = 0; col < board.getCols(); ++col) {
			const Cell& cell = board.getCell(row, col);

			rect.setPosition(
				static_cast<float>(col * Constants::CELL_SIZE),
				static_cast<float>(row * Constants::CELL_SIZE)
			);

			rect.setFillColor(toSFMLColor(cell.color));

			if (cell.markedForDestroy)
				continue;

			bool hidden = false;

			for (const Animation& animation : animations.getAnimations())
			{
				if (animation.getRow() == row &&
					animation.getCol() == col)
				{
					hidden = true;
					break;
				}
			}

			if (hidden)
				continue;

			window.draw(rect);
		}
	}
}


bool BoardRenderer::pixelToCell(
	const Board& board,
	int x,
	int y,
	int& row,
	int& col
) {
	col = x / Constants::CELL_SIZE;
	row = y / Constants::CELL_SIZE;

	return board.isValidPosition(row, col);
}


sf::Vector2f BoardRenderer::celltoPixel(int row, int col) {
	return {
		static_cast<float>(col * Constants::CELL_SIZE),
		static_cast<float>(row * Constants::CELL_SIZE)
	};
}


void BoardRenderer::drawGem(
	sf::RenderWindow& window,
	GemColor color,
	const sf::Vector2f& position,
	float scale
) {
	sf::RectangleShape rect(
		sf::Vector2f(
			static_cast<float>(Constants::CELL_SIZE),
			static_cast<float>(Constants::CELL_SIZE)
		)
	);

	rect.setFillColor(toSFMLColor(color));

	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(sf::Color::Black);

	
	rect.setOrigin(
		Constants::CELL_SIZE / 2.f,
		Constants::CELL_SIZE / 2.f
	);

	
	rect.setPosition(
		position.x + Constants::CELL_SIZE / 2.f,
		position.y + Constants::CELL_SIZE / 2.f
	);

	
	rect.setScale(scale, scale);

	window.draw(rect);
}