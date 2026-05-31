#pragma once

#include "blocks/Block.h"

class UnbreakableBlock : public Block
{
public:
    UnbreakableBlock(
        const sf::Vector2f& position,
        const sf::Vector2f& size);

    void onHit(Ball& ball) override;
};
