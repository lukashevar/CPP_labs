#pragma once

#include "blocks/Block.h"

class HpBlock : public Block
{
public:
    HpBlock(
        const sf::Vector2f& position,
        const sf::Vector2f& size);

    void onHit(Ball& ball) override;

private:
    int hp;
};
