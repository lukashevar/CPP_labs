#include "bonuses/ExpandPAddleBonus.h"

#include "entities/Paddle.h"

ExpandPaddleBonus::ExpandPaddleBonus(const sf::Vector2f& position)
	: Bonus(position) {
	shape.setFillColor(sf::Color::Green);
}