#include "bonuses/BottomBarrierBonus.h"

BottomBarrierBonus::BottomBarrierBonus(const sf::Vector2f& position)
	: Bonus(position) 
{
	shape.setFillColor(sf::Color::Cyan);
}
