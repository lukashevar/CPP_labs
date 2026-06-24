#include "bonuses/ExpandPAddleBonus.h"

ExpandPaddleBonus::ExpandPaddleBonus(const sf::Vector2f& position)
	: Bonus(position) {
	shape.setFillColor(sf::Color::Green);
}
