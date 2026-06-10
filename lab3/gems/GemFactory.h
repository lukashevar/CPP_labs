#pragma once

#include <memory>

#include "Gem.h"
#include "StandartGem.h"
#include "BombBonusGem.h"
#include "RecolorBonusGem.h"

class GemFactory {
public:
	static std::unique_ptr<Gem> createRandom(
		GemColor color
	);

	static std::unique_ptr<Gem> createBonus(
		GemColor color
	);
};
