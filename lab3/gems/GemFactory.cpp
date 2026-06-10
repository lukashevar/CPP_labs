#include "GemFactory.h"

std::unique_ptr<Gem> GemFactory::createRandom(GemColor color) {
	return std::make_unique<StandartGem>(color);
}

std::unique_ptr<Gem> GemFactory::createBonus(GemColor color) {
	int type = rand() % 2;

	if (type == 0)
		return std::make_unique<RecolorBonusGem>(color);

	return std::make_unique<BombBonusGem>(color);
}